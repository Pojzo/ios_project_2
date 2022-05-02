# Makefile

CROSS_COMPILE=
CC=$(CROSS_COMPILE)gcc

SRCDIR=.
SRCEXT=c
BUILDDIR=build
BINDIR=bin
BINNAME=proj2

BIN=$(BINDIR)/$(BINNAME)
SOURCES=$(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS=$(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))

CFLAGS=-std=gnu99 -Wall -Werror -Wextra -pedantic -pthread -lrt
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
	./bin/proj2 3 5 100 100
