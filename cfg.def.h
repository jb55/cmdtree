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
	"terminus:pixelsize=16"
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

static struct command bitcoin_commands[] = {
	DEFCMD("p", "price", "n btc")
	DEFCMD("b", "bcalc", "dmenupn bcalc bcalc")
};

static struct command chromecast_commands[] = {
	DEFCMD(" ", "play/pause", "n chromecast space play-paused")
	DEFCMD("p", "prev", "n chromecast p prev")
	DEFCMD("n", "next", "n chromecast n next")
	DEFCMD("s", "stop", "n chromecast s stopped")
	DEFCMD("q", "quit", "n chromecast quit quit")
	DEFCMD("t", "subtitles", "n chromecast t subtitles")
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
	DEFCMD("f", "fetch", "email-fetch")
	DEFCMD("m", "sync monad", "n muchsync monad-local")
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

static struct command snap_commands[] = {
	DEFCMD("F", "full no upload", "snap -n")
	DEFCMD("f", "full", "snap")
	DEFCMD("S", "selection no upload", "sleep 0.2; snap -n -s")
	DEFCMD("s", "selection", "sleep 0.2; snap -s")
};

static struct command focus_commands[] = {
	DEFCMD("z", "zoom", "focus-zoom")
	DEFCMD("s", "signal", "wmctrl -a Signal")
	DEFCMD("b", "browser", "wmctrl -a qutebrowser")
	DEFCMD("p", "pdf", "wmctrl -a pdf")
};

static struct command notify_commands[] = {
	DEFCMD("c", "close all", "dunstctl close-all")
	DEFCMD("C", "close last", "dunstctl close")
	DEFCMD("n", "open last", "dunstctl history-pop")
};

static struct command window_commands[] = {
	DEFCMD("b", "bright", "bright")
	DEFCMD("c", "colorpick", "colorpick")
	DEFCMD("w", "switch", "dswitcher urxvt")
	DEFPREFIX("s", "snap", snap_commands)
	DEFPREFIX("t", "theme", theme_commands)
	DEFPREFIX("f", "focus", focus_commands)
};

static struct command system_commands[] = {
	DEFPREFIX("c", "copy/sync", sync_commands)
	DEFCMD("S", "suspend", "suspend")
	DEFCMD("s", "my suspend", "my-suspend")
	DEFCMD("r", "reboot", "reboot")
	DEFCMD("k", "kill session", "killsession")
	DEFCMD("i", "init user session", "initx")
	DEFCMD("x", "restart xbindkeys", "pkill xbindkeys && xbindkeys")
};

static struct command dev_commands[] = {
	DEFCMD("l", "lightning issue", "xclip -o | head -n1 | xargs ghissue ElementsProject lightning")
	DEFCMD("b", "bitcoin issue", "xclip -o | head -n1 | xargs ghissue bitcoin bitcoin")
};

static struct command calendar_commands[] = {
	DEFCMD("c", "viscal", "/home/jb55/src/c/viscal/open-my-cals")
	DEFCMD("s", "viscal-sync", "/home/jb55/src/c/viscal/sync")
	DEFCMD("m", "to-monad", "rsync -avzP /home/jb55/var/cal/ 172.24.242.111:/home/jb55/var/cal/")
	DEFCMD("M", "from-monad", "rsync -avzP 172.24.242.111:/home/jb55/var/cal/ /home/jb55/var/cal/ && n echo done || n echo failed")
};

static struct command auth_commands[] = {
	DEFCMD("p", "lastpass", "dmenu-lpass")
	DEFCMD("o", "otp", "otp")
};

static struct command kill_commands[] = {
	DEFCMD("z", "zoom", "pkill zoom")
};

static struct command app_commands[] = {
	DEFPREFIX("c", "calendar", calendar_commands)
	DEFPREFIX("a", "auth", auth_commands)
	DEFPREFIX("k", "kill", kill_commands)
	DEFPREFIX("d", "dev", dev_commands)
	DEFPREFIX("v", "vm", vm_commands)
	DEFCMD("b", "browser", "browser")
	DEFCMD("e", "edit", "edit")
	DEFCMD("s", "signal", "signal-desktop")
	DEFCMD("m", "spotify", "spotify")
	DEFCMD("S", "skype", "skypeforlinux")
	DEFCMD("q", "qalc", "dmenupn calc qalc -t")
	DEFCMD("z", "zoom", "zoom-us")
};

/* static struct command spotify_commands[] = { */
/* 	DEFCMD("n", "next", "spotify-next") */
/* 	DEFCMD("p", "prev", "spotify-prev") */
/* 	DEFCMD(" ", "play/pause", "spotify-playpause") */
/* }; */


static struct command media_commands[] = {
	DEFPREFIX("c", "chromecast", chromecast_commands)
	DEFCMD("b", "connect-bose", "connect-bose")
	DEFCMD("n", "next", "spotify-next")
	DEFCMD("p", "prev", "spotify-prev")
	DEFCMD(" ", "play/pause", "spotify-playpause")
	/* DEFPREFIX("s", "spotify", spotify_commands) */
	DEFCMD("k", "vol+", "amixer sset Master 10%+")
	DEFCMD("j", "vol-", "amixer sset Master 10%-")
};

static struct command date_commands[] = {
	DEFCMD("d", "local", "n mydate")
	DEFCMD("u", "utc", "n mydate -u")
};

static struct command open_commands[] = {
	DEFCMD("p", "downloads pdf", "open-dl /home/jb55/Downloads pdf")
	DEFCMD("P", "papers pdf", "open-dl /home/jb55/docs/papers pdf")
	DEFCMD("c", "edit clipboard", "edit-clipboard")
	DEFCMD("d", "docs pdf", "open-dl /home/jb55/docs pdf")
};

static struct command commands[] = {
	DEFPREFIX("B", "bitcoin", bitcoin_commands)
	DEFPREFIX("a", "apps", app_commands)
	DEFPREFIX("e", "email", email_commands)
	DEFPREFIX("m", "media", media_commands)
	DEFPREFIX("p", "phone", phone_commands)
	DEFPREFIX("s", "system", system_commands)
	DEFPREFIX("w", "window", window_commands)
	DEFPREFIX("d", "date", date_commands)
	DEFPREFIX("n", "notify", notify_commands)
	DEFPREFIX("o", "open", open_commands)
	DEFCMD("b", "battery", "n acpi")
	DEFCMD("l", "lock", "slock")
	DEFCMD("u", "clip", "dclip")
};
