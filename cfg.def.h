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

static struct command browser_commands[] = {
	{ .bind = "s", .name = "chrome", .nchildren = 0, .children = NULL },
	{ .bind = "c", .name = "chromium", .nchildren = 0, .children = NULL },
	{ .bind = "f", .name = "firefox", .nchildren = 0, .children = NULL },
};

static const struct command commands[] = {
	{ .bind = "b",
	  .name = "browsers",
	  .nchildren = LENGTH(browser_commands),
	  .children = browser_commands
	},

	{ .bind = "e",
	  .name = "emacs-dev",
	  .children = NULL,
	  .nchildren = 0
	},
};
