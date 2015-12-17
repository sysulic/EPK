# Makefile

OBJS	= main.o reader.o lex.o parse.o initial.o

CC	= g++
CFLAGS	= -g -Wall
LEXER = flex
PARSER = bison

#DFL
DFL_HEADER = define.h reader.h initial.h

start:	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o start

main.o:  main.cpp
		$(CC) $(CFLAGS) -c main.cpp -o main.o

initial.o:  initial.cpp initial.h
		$(CC) $(CFLAGS) -c initial.cpp -o initial.o

reader.o:  reader.cpp reader.h
		$(CC) $(CFLAGS) -c reader.cpp -o reader.o

lex.o:  lex.yy.c
		$(CC) $(CFLAGS) -c lex.yy.c -o lex.o

lex.yy.c:  lex.l parse.o
		$(LEXER) lex.l

parse.o:  parse.tab.c
		$(CC) $(CFLAGS) -c parse.tab.c -o parse.o

parse.tab.c:	parse.y
		$(PARSER) --defines=parse.h -d parse.y

.PHONY : clean

clean:
	rm -f *.o *.c parse.h parse.output
