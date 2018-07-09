
#ifndef CMDTREE_COMMAND_H
#define CMDTREE_COMMAND_H

#include <ccan/tal/tal.h>

struct command {
	char *name;
	char *bind;
	char *exec;
	struct command *children;
};


void
command_init(struct command *cmd);

int
command_is_prefix(struct command *cmd);


struct command *
test_root_commands(tal_t *ctx);

#endif /* CMDTREE_COMMAND_H */
