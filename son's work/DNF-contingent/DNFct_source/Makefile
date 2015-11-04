# Makefile

OBJS	= bison.o lex.o main.o reader.o action.o planner.o state.o

CC	= g++
CFLAGS	= -g -Wall -ansi

DNFct:	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o DNFct -lfl

lex.o:		lex.c
		$(CC) $(CFLAGS) -c lex.c -o lex.o

lex.c:		lcp.lex 
		flex lcp.lex
		cp lex.yy.c lex.c

bison.o:	bison.c
		$(CC) $(CFLAGS) -c bison.c -o bison.o

bison.c:	lcp.y
		bison -d -v lcp.y
		cp lcp.tab.c bison.c
		cmp -s lcp.tab.h tok.h || cp lcp.tab.h tok.h

main.o:	main.cpp planner.h define.h
	echo "#define BUILT_DATE \"`date`\"" > built_date
	cat built_date main.cpp > main.temp.cpp
	$(CC) $(CFLAGS) -c main.temp.cpp -o main.o
	rm main.temp.cpp

reader.o: reader.cpp reader.h  define.h
	$(CC) $(CFLAGS) -c reader.cpp -o reader.o

action.o: action.cpp action.h  define.h
	$(CC) $(CFLAGS) -c action.cpp -o action.o

state.o: state.cpp state.h  define.h planner.h
	$(CC) $(CFLAGS) -c state.cpp -o state.o

planner.o: planner.cpp planner.h  state.h define.h reader.h
	$(CC) $(CFLAGS) -c planner.cpp -o planner.o

lex.o yac.o main.o	: 
lex.o main.o		: 

clean:
	rm -f *.o *~ lex.c lex.yy.c bison.c tok.h lcp.tab.c lcp.tab.h lcp.output
