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

static enum position position = POSITION_RIGHT;                      /* -b  option; if 0, dmenu appears at bottom     */


static const char *separator = " → ";

/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"Monospace:size=14"
};
/* static const char *prompt      = NULL;      /\* -p  option; prompt to the left of input field *\/ */
static struct scheme schemes[SchemeLast] = {
	[SchemeNorm]  = { .bg = "#222222",
			  .bind = "#D19A66",
			  .arrow = "#888",
			  .name = "#bbbbbb"
	                },

	[SchemePrefix] = { .bg = "#005577",
		       	  .bind = "#eeeeee",
		       	  .arrow = "#666666",
		       	  .name = "#eeeeee"
	                 },
};

/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
