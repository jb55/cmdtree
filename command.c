
#include "command.h"

#include <err.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "util.h"

int
command_is_prefix(struct command *cmd) {
	return cmd->nchildren > 0;
}

void
command_exec(struct command *cmd) {
	const char *cmdname = cmd->command == NULL ? cmd->name : cmd->command;
	execlp("/bin/sh", "sh", "-c", cmdname, (char *) 0);
	err(1, "executing command %s", cmd->name);
}

int
command_num_children(struct command *cmd) {
	return cmd->nchildren;
}

struct command *
command_lookup(struct command *cmd, int ncmds, const char *binding) {
	for (int i = 0; i < ncmds; ++i) {
		if (strcmp(binding, cmd[i].bind) == 0)
			return &cmd[i];
	}

	return NULL;
}

/* static struct command emacs_commands[] = { */
/*   { .bind = "d", .name = "emacs-dev", .nchildren = 0, .children = NULL }, */
/* }; */

