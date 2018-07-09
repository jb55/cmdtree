#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <X11/Xft/Xft.h>

#include <unistd.h>
#include <assert.h>

#include "drw.h"
#include "util.h"

enum {
	SchemeNorm,
	SchemeSel,
	SchemeOut,
	SchemeLast,
}; /* color schemes */

static Window root, parentwin, win;
static int screen;
static Display *display;
static int mw, mh;
static XIC xic;
static Clr *scheme[SchemeLast];

#include "config.h"


static void
grabkeyboard(void)
{
	struct timespec ts = { .tv_sec = 0, .tv_nsec = 1000000  };
	int i;

	// XXXembed
	/* if (embed) */
	/* 	return; */
	/* try to grab keyboard, we may have to wait for another process to ungrab */
	for (i = 0; i < 1000; i++) {
		if (XGrabKeyboard(display, DefaultRootWindow(display), True,
				  GrabModeAsync, GrabModeAsync, CurrentTime)
		    == GrabSuccess)
			return;
		nanosleep(&ts, NULL);
	}
	die("cannot grab keyboard");
}

static void
setup(Drw *drw)
{
	int x, y, j;
	XSetWindowAttributes swa;
	XWindowAttributes wa;
	XIM xim;
	XClassHint ch = {"cmdtree", "cmdtree"};

	/* init appearance */
	for (j = 0; j < SchemeLast; j++)
		scheme[j] = drw_scm_create(drw, colors[j], 2);

	if (!XGetWindowAttributes(display, parentwin, &wa))
		die("could not get embedding window attributes: 0x%lx",
		    parentwin);
	x = 0;
	y = topbar ? 0 : wa.height - mh;
	mw = wa.width;
	lines = MAX(lines, 0);
	/* mh = (lines + 1) * bh; */
	mh = 100;

	swa.override_redirect = True;
	swa.background_pixel = scheme[SchemeNorm][ColBg].pixel;
	swa.event_mask = ExposureMask | KeyPressMask | VisibilityChangeMask;

	win = XCreateWindow(display, parentwin, x, y, mw, mh, 0,
	                    CopyFromParent, CopyFromParent, CopyFromParent,
	                    CWOverrideRedirect | CWBackPixel | CWEventMask, &swa);

	XSetClassHint(display, win, &ch);

	// what do?
	XMapRaised(display, win);
	XSetInputFocus(display, win, RevertToParent, CurrentTime);

	xim = XOpenIM(display, NULL, NULL, NULL);
	xic = XCreateIC(xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
			XNClientWindow, win, XNFocusWindow, win, NULL);
	XSelectInput(display, win, ExposureMask | KeyPressMask);
	XMapWindow(display, win);


	XSetInputFocus(display, win, RevertToParent, CurrentTime);

	// XXXembed
	/* if (embed) { */
	/* 	XSelectInput(dpy, parentwin, FocusChangeMask); */
	/* 	if (XQueryTree(dpy, parentwin, &dw, &w, &dws, &du) && dws) { */
	/* 		for (i = 0; i < du && dws[i] != win; ++i) */
	/* 			XSelectInput(dpy, dws[i], FocusChangeMask); */
	/* 		XFree(dws); */
	/* 	} */
	/* 	grabfocus(); */
	/* } */

	/* drw_resize(drw, mw, mh); */
	/* drawmenu(); */
}

static void
draw_command(Drw *drw, const char *name, const char *binding) {

	int x = 50;
	int y = 10;
	int lpad = 0;
	unsigned int w = 100;
	unsigned int h = 100;
	int invert = 0;
	int res = 1;

	/* XFillRectangle(display, win, DefaultGC(display, screen), x, y, 10, 10); */

	drw_setscheme(drw, scheme[SchemeNorm]);
	drw_rect(drw, 0, 0, mw, mh, 1, 1);
	drw_setscheme(drw, scheme[SchemeSel]);
	res = drw_text(drw, x, y, w, h, lpad, name, invert);
	(void)res;
	assert(res != 0);

	/* XDrawString(drw->dpy, win, DefaultGC(display, screen), 10, 50, name, */
	/* 	    strlen(name)); */

	/* XDrawString(drw->dpy, win, DefaultGC(display, screen), 10, 50, name, */
	/* 	    strlen(name)); */
}

static void
draw_tree(Drw *drw, int x, int y, int w, int h) {
	draw_command(drw, "apps", "a");

	if (!drw)
		return;

	XCopyArea(drw->dpy, drw->drawable, win, drw->gc, x, y, w, h, x, y);
	XSync(drw->dpy, False);
}


static void
cleanup(Drw *drw, int code) {
	int i;

	for (i = 0; i < SchemeLast; i++)
		free(scheme[i]);

	drw_free(drw);
	exit(0);
}

static void
run(Drw *drw) {
	XEvent e;
	int done = 0;
	char buf[32];
	KeySym ksym = NoSymbol;
	Status status;
	int code = 0;

	while (!done) {
		XNextEvent(display, &e);
		switch (e.type) {
		case Expose:
			draw_tree(drw, 0, 0, mw, mh);
			break;
		case KeyPress:
			XmbLookupString(xic, (XKeyEvent*)&e, buf, sizeof buf,
					&ksym, &status);
			if (ksym == XK_q || ksym == XK_Escape) {
				code = 1;
				done = 1;
			}
			break;
		}
	}

	cleanup(drw, code);
}


int main(void) {
	XWindowAttributes wa;
	Drw *drw;

	display = XOpenDisplay(NULL);
	if (display == NULL) {
		fprintf(stderr, "Cannot open display\n");
		exit(1);
	}

	screen = DefaultScreen(display);
	root = RootWindow(display, screen);

	// XXXembed
	/* if (!embed || !(parentwin = strtol(embed, NULL, 0))) */
	/* 	parentwin = root; */

	parentwin = root;

	if (!XGetWindowAttributes(display, parentwin, &wa))
		die("could not get embedding window attributes: 0x%lx",
		    parentwin);

	drw = drw_create(display, screen, root, wa.width, wa.height);

	if (!drw_fontset_create(drw, fonts, LENGTH(fonts)))
		die("no fonts could be loaded.");

	grabkeyboard();
	setup(drw);
	run(drw);

	XCloseDisplay(display);
	return 0;
}
