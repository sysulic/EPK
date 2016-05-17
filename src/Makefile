# Makefile

OBJS	= main.o reader.o lex.o parse.o initial.o EpisCNF.o EpisDNF.o plan.o

CC	= g++
CFLAGS	= -g -Wall
LEXER = flex
PARSER = bison

start:	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o start -O2

main.o:  main.cpp
		$(CC) $(CFLAGS) -c main.cpp -o main.o -O2

plan.o:  plan.cpp plan.h
		$(CC) $(CFLAGS) -c plan.cpp -o plan.o -O2

initial.o:  initial.cpp initial.h
		$(CC) $(CFLAGS) -c initial.cpp -o initial.o -O2

EpisDNF.o:  EpisDNF.cpp EpisDNF.h
		$(CC) $(CFLAGS) -c EpisDNF.cpp -o EpisDNF.o -O2
	
EpisCNF.o:  EpisCNF.cpp EpisCNF.h
		$(CC) $(CFLAGS) -c EpisCNF.cpp -o EpisCNF.o -O2

reader.o:  reader.cpp reader.h
		$(CC) $(CFLAGS) -c reader.cpp -o reader.o -O2

lex.o:  lex.yy.c
		$(CC) $(CFLAGS) -c lex.yy.c -o lex.o -O2

lex.yy.c:  lex.l parse.o
		$(LEXER) lex.l

parse.o:  parse.tab.c
		$(CC) $(CFLAGS) -c parse.tab.c -o parse.o -O2

parse.tab.c:	parse.y
		$(PARSER) --defines=parse.h -d parse.y


.PHONY : clean

clean:
	rm -f *.o *.c parse.h parse.output
