
CFLAGS=-O -g -lX11 -Wall -Werror

all: cmdtree

cmdtree: cmdtree.c
	$(CC) $(CFLAGS) $< -o $@
