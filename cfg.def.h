/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"Monospace:size=12"
};
/* static const char *prompt      = NULL;      /\* -p  option; prompt to the left of input field *\/ */
static struct scheme schemes[SchemeLast] = {
	[SchemeNorm] = { .bg = "#222222", .bind = "#bbbbbb", .name = "#bbbbbb" },
	[SchemeSel]  = { .bg = "#005577", .bind = "#eeeeee", .name = "#eeeeee" },
	[SchemeOut]  = { .bg = "#00ffff", .bind = "#000000", .name = "#000000" },
};

/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
