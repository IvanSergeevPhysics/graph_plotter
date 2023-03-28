CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: graph


parse.o: parse.c
	$(CC) $(CFLAGS) -c parse.c -o parse.o

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c -o stack.o

rpn.o: rpn.c
	$(CC) $(CFLAGS) -c rpn.c -o rpn.o

calculations.o: calculations.c
	$(CC) $(CFLAGS) -c calculations.c -o calculations.o

graph: graph.c parse.o stack.o rpn.o calculations.o
	$(CC) $(CFLAGS) -c graph.c -o graph.o
	$(CC) $(CFLAGS) graph.o parse.o stack.o rpn.o calculations.o -o ../build/graph

clean:
	rm -f *.a *.o ../build/graph

rebuild:
	clean all