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
	DEFCMD("c", "qutebrowser", "qutebrowser")
	DEFCMD("f", "firefox", "firefox")
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
	DEFCMD("=", "volume up", "phonectl music:up")
	DEFCMD("-", "volume down", "phonectl music:down")
};

static struct command phone_clipboard[] = {
	DEFCMD("f", "from phone", "phone-clipboard | xclip && xclip -o | xargs notify-send")
	DEFCMD("t", "to phone", "xclip -o | xargs phone-clipboard")
};

static struct command phone_commands[] = {
	DEFCMD("b", "battery", "n phone-batt")
	DEFPREFIX("c", "clipboard", phone_clipboard)
	DEFCMD("r", "ring", "n phonectl ring:100")
	DEFCMD("s", "stop ring", "n phonectl ring:stop")
	DEFPREFIX("m", "music", phone_music_commands)
};

static struct command email_notifications[] = {
	DEFCMD("1", "on", "nostat +h && n echo email notifications on")
	DEFCMD("0", "off", "nostat -h && n echo email notifications off")
	DEFCMD("n", "status", "n nostat")
};

static struct command email_commands[] = {
	DEFCMD("f", "fetch", "systemctl --user restart home-email-notifier")
	DEFCMD("s", "status", "n email-status-once")
	DEFPREFIX("n", "notifications", email_notifications)
};

static struct command vm_commands[] = {
	DEFCMD("p", "pause/resume", "vmtoggle")
	DEFCMD("c", "close", "vmclose")
	DEFCMD("v", "virtualbox", "VirtualBox")
};


static struct command sync_commands[] = {
	DEFCMD("t", "quiver -> monad", "n sync-todo quiver monad")
	DEFCMD("f", "monad -> quiver", "n sync-todo monad quiver")
};

static struct command theme_commands[] = {
	DEFCMD("d", "dark", "themeswitch dark")
	DEFCMD("l", "light", "themeswitch light")
};

static struct command window_commands[] = {
	DEFCMD("b", "bright", "bright")
	DEFCMD("c", "colorpick", "colorpick")
	DEFCMD("S", "snap", "snap")
	DEFCMD("s", "snap selection", "sleep 0.2; snap -s")
	DEFPREFIX("t", "theme", theme_commands)
};

static struct command system_commands[] = {
	DEFPREFIX("c", "copy/sync", sync_commands)
	DEFCMD("S", "suspend", "suspend")
	DEFCMD("s", "my suspend", "my-suspend")
	DEFCMD("r", "reboot", "reboot")
	DEFCMD("k", "kill session", "killsession")
	DEFCMD("i", "init user session", "initx")
};

static struct command dev_commands[] = {
	DEFCMD("l", "lightning issue", "xclip -o | head -n1 | xargs lissue")
};

static struct command app_commands[] = {
	DEFPREFIX("c", "browser", browser_commands)
	DEFCMD("C", "calendar", "qutebrowser --target window https://calendar.google.com")
	DEFCMD("e", "edit", "edit")
	DEFCMD("s", "signal", "signal-desktop")
	DEFCMD("S", "skype", "skypeforlinux")
	DEFCMD("t", "tweet", "dmenup tweet tweet")
	DEFCMD("l", "lastpass", "dmenu-lpass")
	DEFCMD("q", "qalc", "dmenupn calc qalc -t")
};

static struct command spotify_commands[] = {
	DEFCMD("n", "next", "spotify-next")
	DEFCMD("p", "prev", "spotify-prev")
	DEFCMD(" ", "play/pause", "spotify-playpause")
};


static struct command media_commands[] = {
	DEFPREFIX("c", "chromecast", chromecast_commands)
	DEFCMD("b", "connect-bose", "connect-bose")
	DEFCMD("n", "next", "xdotool key XF86AudioNext")
	DEFCMD("p", "prev", "xdotool key XF86AudioPrev")
	DEFCMD(" ", "play/pause", "xdotool key XF86AudioPlay")
	DEFPREFIX("s", "spotify", spotify_commands)
	DEFCMD("=", "vol+", "amixer sset Master 10%+")
	DEFCMD("-", "vol-", "amixer sset Master 10%-")
};


static struct command commands[] = {
	DEFPREFIX("B", "bitcoin", bitcoin_commands)
	DEFPREFIX("a", "apps", app_commands)
	DEFPREFIX("e", "email", email_commands)
	DEFPREFIX("g", "dev", dev_commands)
	DEFPREFIX("m", "media", media_commands)
	DEFPREFIX("p", "phone", phone_commands)
	DEFPREFIX("s", "system", system_commands)
	DEFPREFIX("v", "vm", vm_commands)
	DEFPREFIX("w", "window", window_commands)
	DEFCMD("b", "battery", "n acpi")
	DEFCMD("d", "date", "n mydate")
	DEFCMD("l", "lock", "slock")
	DEFCMD("u", "clip", "dclip")
};
