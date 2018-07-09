
#include "command.h"

#include "ccan/tal/tal.h"
#include "ccan/tal/str/str.h"

void
command_init(struct command *cmd) {
	cmd->children = NULL;
}

int
command_is_prefix(struct command *cmd) {
	size_t count = tal_count(cmd->children);
	return count > 0;
}


struct command *
test_root_commands(tal_t *ctx) {
	unsigned long i, j;
	struct command *cmds = NULL;
	struct command *child = NULL;

	cmds = tal_arr(ctx, struct command, 5);

	const unsigned long c = 'a';
	for (i = 0; i < tal_count(cmds); i++) {
		cmds[i].name = tal_fmt(cmds, "hello-%d", (int)i);
		cmds[i].bind = tal_fmt(cmds, "%c", (int)(c+i));
		child = cmds[i].children = tal_arr(cmds, struct command, i % 2);
		for (j = 0; j < tal_count(child); j++) {
			child[j].name = tal_fmt(child, "child-%d-%d", (int)i, (int)j);
			child[j].bind = tal_fmt(child, "%c", (int)(c+j));
			child[j].children = NULL;
		}
	}

	return cmds;
}
