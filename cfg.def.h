/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */

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

	[SchemeSel]   = { .bg = "#005577",
			  .bind = "#eeeeee",
			  .arrow = "#666666",
			  .name = "#eeeeee"
	                },

	[SchemeOut]   = { .bg = "#00ffff",
			  .bind = "#000000",
			  .arrow = "#666666",
			  .name = "#000000"
	                },
};

/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
