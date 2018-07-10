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
#include "command.h"

enum {
	SchemeNorm,
	SchemePrefix,
	SchemeLast,
}; /* color schemes */


struct cmdstack {
	struct command *children;
	int nchildren;
};

#define CMDSTACK_SIZE 32
static struct cmdstack cmdstack[CMDSTACK_SIZE];
static int cmdstack_ptr = 0;

static Window root, parentwin, win;
static int screen;
static Display *display;
static int sep_width;
static int bh, mw, mh;
static XIC xic;

#include "cfg.h"

static int
cmdstack_push_(struct command *children, int nchildren) {
	if (cmdstack_ptr + 1 >= CMDSTACK_SIZE)
		return 0;
	cmdstack[cmdstack_ptr].children = children;
	cmdstack[cmdstack_ptr].nchildren = nchildren;
	cmdstack_ptr++;
	return 1;
}

static int
cmdstack_push(struct command *cmd) {
	return cmdstack_push_(cmd->children, cmd->nchildren);
}

struct cmdstack *
cmdstack_top() {
	assert(cmdstack_ptr >= 1);
	return &cmdstack[cmdstack_ptr-1];
}

struct cmdstack *
cmdstack_pop() {
	if (cmdstack_ptr == 1)
		return 0;

	return &cmdstack[cmdstack_ptr--];
}

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
	int x, y;
	XSetWindowAttributes swa;
	XWindowAttributes wa;
	XIM xim;
	XClassHint ch = {"cmdtree", "cmdtree"};

	bh = drw->fonts->h + 2;
	/* init appearance */
	drw_scm_create(drw, schemes, LENGTH(schemes));

	if (!XGetWindowAttributes(display, parentwin, &wa))
		die("could not get embedding window attributes: 0x%lx",
		    parentwin);
	int vertwidth = 200;
	mw = wa.width;
	mh = 1 * bh;
	switch (position) {
	case POSITION_BOTTOM:
		y = wa.height - mh;
		x = 0;
		break;
	case POSITION_TOP:
		x = 0;
		y = 0;
		break;
	case POSITION_LEFT:
		x = 0;
		y = 0;
		// TODO: calc vertwidth = max(textwidth(nodes)))
		mw = vertwidth;
		mh = wa.height;
		break;
	case POSITION_RIGHT:
		x = wa.width - vertwidth;
		y = 0;
		mw = vertwidth;
		mh = wa.height;
	}
	sep_width = drw_fontset_getwidth(drw, separator);

	swa.override_redirect = True;
	swa.background_pixel = schemes[SchemeNorm].bg_clr.pixel;
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
	/* draw_tree(drw); */
}

static int
draw_command(Drw *drw, int x, int y, struct command *cmd) {
	char buf[256];
	int lpad = 0;
	int pad = 0;
	unsigned int w = 50;
	int invert = 0;
	int isprefix = 0;
	char *name = cmd->name;
	struct scheme *scheme = NULL;

	//drw_fontset_getwidth(drw, binding) + 1;

	drw_setscheme(drw, &schemes[SchemeNorm].bind_clr,
		      &schemes[SchemeNorm].bg_clr);

	w = drw_fontset_getwidth(drw, cmd->bind);
	x = drw_text(drw, x+pad, y, w, bh, lpad, cmd->bind, invert);

	w = sep_width;
	drw_setscheme(drw, &schemes[SchemeNorm].arrow_clr,
		      &schemes[SchemeNorm].bg_clr);
	x = drw_text(drw, x+pad, y, w, bh, lpad, separator, invert);

	isprefix = command_is_prefix(cmd);

	if (isprefix)
		scheme = &schemes[SchemePrefix];
	else
		scheme = &schemes[SchemeNorm];

	drw_setscheme(drw, &scheme->name_clr, &scheme->bg_clr);

	if (scheme->prefix && strlen(scheme->prefix) != 0) {
		snprintf(buf, 256, "%s%s", scheme->prefix, cmd->name);
		name = buf;
	}

	w = drw_fontset_getwidth(drw, name);
	x = drw_text(drw, x+pad, y, w, bh, lpad, name, invert);

	return x;
}


/* static void */
/* calc_tree_exts(struct node *nodes, int num_nodes, int *rows, int *cols) { */
/* } */
static void
draw_tree_vertical(Drw *drw, struct command *cmds, int ncmds, int x, int y, int w, int h) {
	int i;
	int colw = 0;

	x += xpad;
	y += ypad;

	drw_setscheme(drw, &schemes[SchemeNorm].bg_clr,
		      &schemes[SchemeNorm].bg_clr);
	drw_rect(drw, 0, 0, w, h, 1, 1);

	int c = '0';

	for (i = 0; i < ncmds; ++i, ++c, y += bh) {
		struct command *cmd = &cmds[i];
		if (y >= mh) {
			x = colw;
			y = 0;
			colw = 0;
		}
		colw = MAX(draw_command(drw, x, y, cmd) + 20, colw);
	}
}

/* static void */
/* draw_tree_horizontal(Drw *drw, struct command *cmds, int x, int y, int w, int h) { */
/* 	int i, dx = x, dy = y; */

/* 	drw_setscheme(drw, &schemes[SchemeNorm].bg_clr, */
/* 		      &schemes[SchemeNorm].bg_clr); */
/* 	drw_rect(drw, 0, 0, w, h, 1, 1); */

/* 	int c = '0'; */
/* 	for (i = 0; i < 50; ++i, ++c) { */
/* 		if (i % 2 == 0) */
/* 			snprintf(buf, 512, "item-long-%d", i); */
/* 		else if (i % 6 == 0) */
/* 			snprintf(buf, 512, "herpderp-%d", i); */
/* 		else if (i % 7 == 0) */
/* 			snprintf(buf, 512, "ksdfsdjhfsdf-%d", i); */
/* 		else */
/* 			snprintf(buf, 512, "hi-%d", i); */
/* 		if (c > '~') c = '0'; */
/* 		sprintf(smallbuf, "%c", c); */
/* 		dx = draw_command(drw, dx, dy, cmd) + 20; */
/* 		if (dx >= mw) { */
/* 			dx = 0; */
/* 			dy += bh; */
/* 		} */
/* 	} */
/* } */

static void
draw_tree(Drw *drw, int x, int y, int w, int h) {
	if (!drw)
		return;

	struct cmdstack *cmdstack = cmdstack_top();

	/* draw_tree_horizontal(drw, x, y, w, h); */
	draw_tree_vertical(drw, cmdstack->children, cmdstack->nchildren, x, y,
			   w, h);

	XCopyArea(drw->dpy, drw->drawable, win, drw->gc, x, y, w, h, x, y);
	XSync(drw->dpy, False);
}


static void
cleanup(Drw *drw, int code) {
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
	struct cmdstack *cmdstack = NULL;
	struct command *cmd = NULL;

	while (!done) {
		cmd = NULL;
		XNextEvent(display, &e);
		switch (e.type) {
		case Expose:
			draw_tree(drw, 0, 0, mw, mh);
			break;
		case KeyPress:
			XmbLookupString(xic, (XKeyEvent*)&e, buf, sizeof buf,
					&ksym, &status);

			if (ksym == XK_Escape) {
				code = 1;
				done = 1;
				break;
			}
			else if (ksym == XK_BackSpace) {
				if (cmdstack_pop())
					draw_tree(drw, 0, 0, mw, mh);
			}

			cmdstack = cmdstack_top();
			cmd = command_lookup(cmdstack->children,
					     cmdstack->nchildren, buf);

			if (cmd) {
				if (command_is_prefix(cmd)) {
					cmdstack_push(cmd);
					draw_tree(drw, 0, 0, mw, mh);
				}
				else {
					command_exec(cmd);
				}
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
	/* struct command *cmds = */
	/* 	test_root_commands(NULL, commands, cmdstack->nchildren); */
	int res = cmdstack_push_(commands, LENGTH(commands));
	assert(res);

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
