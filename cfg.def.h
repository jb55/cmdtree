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
	"monospace:size=16"
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
	DEFCMD("s", "chrome scaled", "chrome")
	DEFCMD("c", "chromium", "chromium")
	DEFCMD("f", "firefox", "firefox")
	DEFCMD("k", "kill chrome", "pkill --oldest chromium")
};

static struct command bitcoin_commands[] = {
	DEFCMD("p", "price", "n btc")
};

static struct command chromecast_commands[] = {
	DEFCMD("s", "stop", "n chromecast s stopped")
	DEFCMD("m", "mute", "n chromecast m muted")
};

static struct command phone_music_commands[] = {
	DEFCMD("p", "play/pause", "phonectl music:playpause")
	DEFCMD("u", "volume up", "phonectl music:up")
	DEFCMD("d", "volume down", "phonectl music:down")
};

static struct command phone_commands[] = {
	DEFCMD("b", "battery", "n phone-batt")
	DEFCMD("c", "copy clipboard", "phone-clipboard | xclip")
	DEFPREFIX("m", "music", phone_music_commands)
};

static struct command email_commands[] = {
	DEFCMD("f", "fetch", "systemctl --user restart home-email-notifier")
	DEFCMD("s", "status", "n email-status-once")
};

static struct command vm_commands[] = {
	DEFCMD("p", "pause/resume", "vmtoggle")
	DEFCMD("v", "virtualbox", "VirtualBox")
};


static struct command sync_commands[] = {
	DEFCMD("t", "quiver -> monad", "n sync-todo quiver monad")
	DEFCMD("f", "monad -> quiver", "n sync-todo monad quiver")
};

static struct command system_commands[] = {
	DEFCMD("b", "bright", "bright")
	DEFCMD("S", "suspend", "suspend")
	DEFCMD("s", "my suspend", "my-suspend")
	DEFCMD("r", "reboot", "reboot")
	DEFCMD("k", "kill session", "killsession")
	DEFCMD("i", "init user session", "initx")
};

static struct command theme_commands[] = {
	DEFCMD("d", "dark", "themeswitch dark")
	DEFCMD("l", "light", "themeswitch light")
};

static struct command commands[] = {
	DEFPREFIX("b", "browsers", browser_commands)
	DEFPREFIX("B", "bitcoin", bitcoin_commands)
	DEFPREFIX("c", "chromecast", chromecast_commands)
	DEFCMD("d", "date", "n mydate")
	DEFCMD("e", "emacs", "emacs-dev")
	DEFPREFIX("n", "notmuch", email_commands)
	DEFPREFIX("P", "phone", phone_commands)
	DEFCMD("p", "power", "n acpi")
	DEFCMD("l", "lock", "slock")
	DEFPREFIX("S", "sync", sync_commands)
	DEFPREFIX("s", "system", system_commands)
	DEFPREFIX("t", "theme", theme_commands)
	DEFPREFIX("v", "vm", vm_commands)
};
