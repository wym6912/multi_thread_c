CC = gcc
CFLAGS = -g -O3 -D _GNU_SOURCE
LIBS = -lm  -lpthread
STDF = -std=c99
MYCFLAGS = $(STDF) $(CFLAGS) $(LIBS)

INSTALL = install
PROGS = test

OBJMAIN = threadpool_condition.o threadpool.o test.o

HEADER = threadpool_condition.h threadpool.h

all : $(PROGS) 
	@echo done.

threadpool_condition.o : threadpool_condition.c $(HEADER)
	$(CC) $(MYCFLAGS) -c threadpool_condition.c

threadpool.o : threadpool.c $(HEADER)
	$(CC) $(MYCFLAGS) -c threadpool.c

test.o: test.c $(HEADER)
	$(CC) $(MYCFLAGS) -c test.c

test: $(OBJMAIN)
	$(CC) -o $@ $(OBJMAIN) $(MYCFLAGS) $(LIBS)

clean :
	rm -f *.o *.a *.exe *~  $(PROGS) 