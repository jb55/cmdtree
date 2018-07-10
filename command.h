
#ifndef CMDTREE_COMMAND_H
#define CMDTREE_COMMAND_H

struct command {
	char *name;
	char *command;
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


#endif /* CMDTREE_COMMAND_H */
