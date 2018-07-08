#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <unistd.h>

#include "util.h"

static Window root, parentwin, win;
static int screen;
static Display *display;
static int mw, mh;
static unsigned int lines = 0;
static XIC xic;

// config
static int topbar = 1;

static void
setup()
{
	int x, y;
	XSetWindowAttributes swa;
	XWindowAttributes wa;
	XIM xim;
	XClassHint ch = {"cmdtree", "cmdtree"};

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
	/* swa.background_pixel = scheme[SchemeNorm][ColBg].pixel; */
	swa.event_mask = ExposureMask | KeyPressMask | VisibilityChangeMask;

	win = XCreateWindow(display, parentwin, x, y, mw, mh, 0,
	                    CopyFromParent, CopyFromParent, CopyFromParent,
	                    CWOverrideRedirect | CWBackPixel | CWEventMask, &swa);

	XSetClassHint(display, win, &ch);

	// what do?
	/* XMapRaised(display, win); */


	xim = XOpenIM(display, NULL, NULL, NULL);
	xic = XCreateIC(xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
			XNClientWindow, win, XNFocusWindow, win, NULL);
	XSelectInput(display, win, ExposureMask | KeyPressMask);
	XMapWindow(display, win);


	XSetInputFocus(display, win, RevertToParent, CurrentTime);

	// XXX embed
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
draw_tree() {
	static const char *msg = "cmdtree is a tree of commands";

	XFillRectangle(display, win, DefaultGC(display, screen),
		       20, 20, 10, 10);

	XDrawString(display, win, DefaultGC(display, screen), 10,
		    50, msg, strlen(msg));
}


static void
run() {
	XEvent e;
	int done = 0;
	char buf[32];
	KeySym ksym = NoSymbol;
	Status status;

	while (!done) {
		XNextEvent(display, &e);
		if (e.type == Expose) {
			draw_tree();
		}

		if (e.type == KeyPress) {
			XmbLookupString(xic, (XKeyEvent*)&e, buf,
					sizeof buf, &ksym, &status);
			if (ksym == XK_q) done = 1;
			if (ksym == XK_Escape) done = 1;
		}

	}

}


int main(void) {

	display = XOpenDisplay(NULL);
	if (display == NULL) {
		fprintf(stderr, "Cannot open display\n");
		exit(1);
	}

	screen = DefaultScreen(display);
	root = RootWindow(display, screen);

	// XXX embed
	/* if (!embed || !(parentwin = strtol(embed, NULL, 0))) */
	/* 	parentwin = root; */

	parentwin = root;

	setup();
	run();

	XCloseDisplay(display);
	return 0;
}
