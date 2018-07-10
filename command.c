
#include "command.h"

#include "ccan/tal/tal.h"
#include "ccan/tal/str/str.h"
#include "ccan/str/str.h"
#include <err.h>
#include <unistd.h>
#include <stdio.h>

#include "util.h"

int
command_is_prefix(struct command *cmd) {
	return cmd->nchildren > 0;
}

void
command_exec(struct command *cmd) {
	execlp(cmd->name, cmd->name, (char *)NULL);
	err(1, "executing command %s", cmd->name);
}

int
command_num_children(struct command *cmd) {
	return tal_count(cmd) || cmd->nchildren;
}

struct command *
command_lookup(struct command *cmd, int ncmds, const char *binding) {
	for (int i = 0; i < ncmds; ++i) {
		if (streq(binding, cmd[i].bind))
			return &cmd[i];
	}

	return NULL;
}

static struct command emacs_commands[] = {
  { .bind = "d", .name = "emacs-dev", .nchildren = 0, .children = NULL },
};

static const struct command examples[] = {
  { .bind = "f", .name = "firefox", .nchildren = 0, .children = NULL },

  { .bind = "e",
    .name = "emacs",
    .children = emacs_commands,
    .nchildren = LENGTH(emacs_commands)
  },

  { .bind = "N", .name = "networking", .nchildren = 0, .children = NULL },
};

struct command *
test_root_commands(tal_t *ctx, int *ncmds) {
	unsigned long i;
	struct command *cmds = NULL;

	cmds = tal_arr(ctx, struct command, LENGTH(examples));
	*ncmds = LENGTH(examples);

	for (i = 0; i < LENGTH(examples); ++i) {
		cmds[i].children = examples[i].children;
		cmds[i].name = examples[i].name;
		cmds[i].bind = examples[i].bind;
		cmds[i].nchildren = examples[i].nchildren;
	}

	return cmds;
}
