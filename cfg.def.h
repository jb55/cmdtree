/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

enum position {
	POSITION_TOP,
	POSITION_LEFT,
	POSITION_RIGHT,
	POSITION_BOTTOM
};

static int xpad = 6;
static int ypad = 2;

static enum position position = POSITION_TOP;


static const char *separator = " → ";

/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"monospace:size=14"
};

#define scheme_bg "#222222"

static struct scheme schemes[SchemeLast] = {
	[SchemeNorm]  = { .bg = scheme_bg,
			  .bind = "#D19A66",
			  .arrow = "#888",
			  .prefix = "",
			  .name = "#bbbbbb"
	                },

	[SchemePrefix] = { .bg = scheme_bg,
			   .bind = "#eeeeee",
			   .arrow = "#888",
			   .prefix = "",
			   .name = "#c678dd"
	                 },
};

static struct command test_commands[] = {
	DEFCMD("t", "test command", "echo ok")
};


static struct command browser_commands[] = {
	DEFCMD("s", "chrome scaled", "chromium --force-device-scale-factor=1.25")
	DEFCMD("c", "chromium", "chromium")
	DEFCMD("f", "firefox", "firefox")
	DEFCMD("k", "kill chrome", "pkill --oldest chromium")
	DEFPREFIX("t", "test nested prefix", test_commands)
};

static struct command commands[] = {
	DEFPREFIX("b", "browsers", browser_commands)
	DEFCMD("e", "emacs", "emacs")
};
