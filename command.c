
#include "command.h"

#include "ccan/tal/tal.h"
#include "ccan/tal/str/str.h"
#include "ccan/str/str.h"
#include <err.h>
#include <unistd.h>

#include "util.h"

void
command_init(struct command *cmd) {
	cmd->children = NULL;
}

int
command_is_prefix(struct command *cmd) {
	size_t count = tal_count(cmd->children);
	return count > 0;
}

void
command_exec(struct command *cmd) {
	execlp(cmd->name, cmd->name, (char *)NULL);
	err(1, "executing command %s", cmd->name);
}

struct command *
command_lookup(struct command *cmd, const char *binding) {
	size_t len = tal_count(cmd);
	for (size_t i = 0; i < len; ++i) {
		if (streq(binding, cmd[i].bind))
			return &cmd[i];
	}

	return NULL;
}

static const struct command examples[] = {
  { .bind = "f", .name = "firefox" },
  { .bind = "m", .name = "misc" },
  { .bind = "e", .name = "emacs" },
  { .bind = "N", .name = "networking" },
};

struct command *
test_root_commands(tal_t *ctx) {
	unsigned long i, j;
	struct command *cmds = NULL;
	struct command *child = NULL;

	cmds = tal_arr(ctx, struct command, 10);

	const unsigned long c = 'a';
	for (i = 0; i < tal_count(cmds); i++) {
		if (i < LENGTH(examples)) {
			cmds[i].name = examples[i].name;
			cmds[i].bind = examples[i].bind;
		}
		else {
			cmds[i].name = tal_fmt(cmds, "example-%d", (int)i);
			cmds[i].bind = tal_fmt(cmds, "%c", (int)(c+i));
		}
		child = cmds[i].children = tal_arr(cmds, struct command, i % 2);
		for (j = 0; j < tal_count(child); j++) {
			child[j].name = "sayhi";
			child[j].bind = tal_fmt(child, "%c", (int)(c+j));
			child[j].children = NULL;
		}
	}

	return cmds;
}
