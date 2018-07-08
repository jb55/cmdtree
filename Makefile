
CFLAGS=-O2 -g -lX11 -Wall -Werror
LDFLAGS=-lXft -lfontconfig

BIN=cmdtree

OBJS += drw.o
OBJS += util.o
OBJS += cmdtree.o

SRCS=$(OBJS:.o=.c)

all: $(SHLIB) $(STATICLIB) $(BIN)

include $(OBJS:.o=.d)

%.d: %.c
	$(CC) -MM $(CFLAGS) $< > $@

all: cmdtree

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean: fake
	rm -f $(OBJS) $(BIN)

.PHONY: fake
