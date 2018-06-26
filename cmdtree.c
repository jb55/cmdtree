#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	Display *d;
	XIC xic;
	Window w;
	XEvent e;
	char *msg = "cmdtree is a tree of commands";
	int s;
	char buf[32];
	int len, done = 0;
	KeySym ksym = NoSymbol;
	Status status;
	XIM xim;

	d = XOpenDisplay(NULL);
	if (d == NULL) {
		fprintf(stderr, "Cannot open display\n");
		exit(1);
	}

	s = DefaultScreen(d);
	w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 100, 100, 1,
				BlackPixel(d, s), WhitePixel(d, s));
	xim = XOpenIM(d, NULL, NULL, NULL);
	xic = XCreateIC(xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
			XNClientWindow, w, XNFocusWindow, w, NULL);
	XSelectInput(d, w, ExposureMask | KeyPressMask);
	XMapWindow(d, w);

	while (!done) {
		XNextEvent(d, &e);
		if (e.type == Expose) {
			XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
			XDrawString(d, w, DefaultGC(d, s), 10, 50, msg, strlen(msg));
		}

		if (e.type == KeyPress) {
			len = XmbLookupString(xic, (XKeyEvent*)&e, buf, sizeof buf, &ksym, &status);
			if (ksym == XK_q) break;
		}

	}

	XCloseDisplay(d);
	return 0;
}
