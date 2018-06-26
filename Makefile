
all: cmdtree

cmdtree: cmdtree.c
	$(CC) -O -g -lX11 $< -o $@
