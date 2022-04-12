# Makefile

CROSS_COMPILE=
CC=$(CROSS_COMPILE)gcc

SRCDIR=src
SRCEXT=c
BUILDDIR=build
BINDIR=bin
BINNAME=main

BIN=$(BINDIR)/$(BINNAME)
SOURCES=$(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS=$(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))

CFLAGS=-g -Wall -Werror -Wextra -pedantic 
LIB=

$(BIN): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $^ -o $(BIN) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	$(RM) -r $(BUILDDIR) $(BINDIR)


run: 
	./bin/main
