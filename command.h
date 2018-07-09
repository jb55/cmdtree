
#ifndef CMDTREE_COMMAND_H
#define CMDTREE_COMMAND_H


struct node {
	char *name;
	struct node **children;
};

#endif /* CMDTREE_COMMAND_H */
