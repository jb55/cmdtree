
CFLAGS=-Os -g -Wall -Werror -I. -Wno-unused-function
LDFLAGS=-lXft -lfontconfig -lX11
PREFIX ?= /home/jb55

BIN=cmdtree

OBJS += drw.o
OBJS += util.o
OBJS += cmdtree.o
OBJS += command.o

OBJS += $(DEPS:.c=.o)

SRCS=$(OBJS:.o=.c)

all: $(SHLIB) $(STATICLIB) $(BIN)

include $(OBJS:.o=.d)

%.d: %.c
	$(CC) -MM $(CFLAGS) $< > $@

cmdtree.c: cfg.h

cfg.h: cfg.def.h
	cp cfg.def.h $@

all: cmdtree

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean: fake
	rm -f $(OBJS) $(BIN) *.d

install: $(BIN)
	mkdir -p $(PREFIX)/bin
	cp $(BIN) $(PREFIX)/bin

TAGS: fake
	etags *.c

.PHONY: fake
