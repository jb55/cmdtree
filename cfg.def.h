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
	DEFCMD("c", "chrome", "chrome")
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
	DEFCMD("r", "ring", "n phonectl ring:100")
	DEFCMD("s", "stop ring", "n phonectl ring:stop")
	DEFCMD("c", "copy clipboard", "phone-clipboard | xclip")
	DEFPREFIX("m", "music", phone_music_commands)
};

static struct command email_notifications[] = {
	DEFCMD("1", "on", "nostat +h && n echo email notifications on")
	DEFCMD("0", "off", "nostat -h && n echo email notifications off")
};

static struct command email_commands[] = {
	DEFCMD("f", "fetch", "systemctl --user restart home-email-notifier")
	DEFCMD("s", "status", "n email-status-once")
	DEFPREFIX("n", "notifications", email_notifications)
};

static struct command vm_commands[] = {
	DEFCMD("p", "pause/resume", "vmtoggle")
	DEFCMD("v", "virtualbox", "VirtualBox")
};


static struct command sync_commands[] = {
	DEFCMD("t", "quiver -> monad", "n sync-todo quiver monad")
	DEFCMD("f", "monad -> quiver", "n sync-todo monad quiver")
};

static struct command window_commands[] = {
	DEFCMD("c", "colorpick", "colorpick")
	DEFCMD("s", "snap", "snap")
	DEFCMD("S", "snap selection", "sleep 0.2; snap -s")
};

static struct command system_commands[] = {
	DEFCMD("b", "bright", "bright")
	DEFPREFIX("c", "copy/sync", sync_commands)
	DEFCMD("S", "suspend", "suspend")
	DEFCMD("s", "my suspend", "my-suspend")
	DEFCMD("r", "reboot", "reboot")
	DEFCMD("k", "kill session", "killsession")
	DEFCMD("i", "init user session", "initx")
	DEFPREFIX("w", "window", window_commands)
};

static struct command theme_commands[] = {
	DEFCMD("d", "dark", "themeswitch dark")
	DEFCMD("l", "light", "themeswitch light")
};

static struct command app_commands[] = {
	DEFCMD("c", "calendar", "chrome --app=https://calendar.google.com")
	DEFCMD("e", "emacs", "emacs-dev")
	DEFCMD("s", "signal", "signal-desktop")
	DEFCMD("S", "skype", "skypeforlinux")
};

static struct command spotify_commands[] = {
	DEFCMD("l", "next", "spotify-next")
	DEFCMD("h", "prev", "spotify-prev")
	DEFCMD("p", "play/pause", "spotify-playpause")
};


static struct command media_commands[] = {
	DEFCMD("l", "next", "xdotool key XF86AudioNext")
	DEFCMD("h", "prev", "xdotool key XF86AudioPrev")
	DEFCMD("p", "play/pause", "xdotool key XF86AudioPlay")
	DEFPREFIX("s", "spotify", spotify_commands)
	DEFCMD("=", "vol+", "amixer sset Master 10%+")
	DEFCMD("-", "vol-", "amixer sset Master 10%-")
};


static struct command commands[] = {
	DEFPREFIX("a", "apps", app_commands)
	DEFPREFIX("b", "browsers", browser_commands)
	DEFPREFIX("B", "bitcoin", bitcoin_commands)
	DEFPREFIX("c", "chromecast", chromecast_commands)
	DEFCMD("d", "date", "n mydate")
	DEFPREFIX("e", "email", email_commands)
	DEFPREFIX("m", "media", media_commands)
	DEFPREFIX("P", "phone", phone_commands)
	DEFCMD("p", "power", "n acpi")
	DEFCMD("l", "lock", "slock")
	DEFPREFIX("s", "system", system_commands)
	DEFPREFIX("t", "theme", theme_commands)
	DEFPREFIX("v", "vm", vm_commands)
};
