#
# Makefile
#
# hdump -- Hexadecimal dump


## Compiler and linker options ----------------------------------
CC      = gcc
CCFLAGS = -Wall -Werror
LDFLAGS = -s
# -s  Remove all symbol table and relocation information from
#     the executable.


SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .h .c .o


## Files --------------------------------------------------------
OBJS   = main.o dump.o
SOURCE = main.c
TARGET = hdump


## Compilation and linkage --------------------------------------
${TARGET}: ${OBJS}
	${CC} ${LDFLAGS} -o $@ $^

%.o: %.c
	${CC} ${CCFLAGS} -c -o $@ $<


## Options ------------------------------------------------------
.PHONY: clean

all:
	make ${TARGET}

clean:
	rm --force ${OBJS} ${TARGET}

help:
	@echo "Type:"
	@echo "   'make all' to compile and link."
	@echo "   'make clean' to remove object files and binaries."

