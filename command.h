
#ifndef CMDTREE_COMMAND_H
#define CMDTREE_COMMAND_H

#include <ccan/tal/tal.h>

struct command {
	char *name;
	char *bind;
	struct command *children;
	int nchildren;
};


void
command_init(struct command *cmd);

void
command_exec(struct command *cmd);

int
command_is_prefix(struct command *cmd);

struct command *
command_lookup(struct command *cmd, int ncmds, const char *binding);

struct command *
test_root_commands(tal_t *ctx, const struct command *commands, int ncmds);

#endif /* CMDTREE_COMMAND_H */
