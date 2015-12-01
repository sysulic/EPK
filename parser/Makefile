# Makefile

OBJS	= init.o lex.o parse.o

CC	= g++
CFLAGS	= -g -Wall
LEXER = flex
PARSER = bison

#DFL
DFL_HEADER = define.h reader.h

start:	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o start

init.o: init.cpp
		$(CC) $(CFLAGS) -c init.cpp -o init.o

lex.o:		lex.yy.c
		$(CC) $(CFLAGS) -c lex.yy.c -o lex.o

lex.yy.c:	lex.l parse.o
		$(LEXER) lex.l

parse.o:	parse.tab.c
		$(CC) $(CFLAGS) -c parse.tab.c -o parse.o

parse.tab.c:	parse.y
		$(PARSER) --defines=parse.h -d parse.y

.PHONY : clean

clean:
	rm -f *.o *.c start parse.h parse.output
