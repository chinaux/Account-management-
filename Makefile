OBJS=acms.o menu.o list.o
CC=gcc
CFLAGS=-g -o
acms:$(OBJS)
	$(CC) $(CFLAGS) acms $(OBJS)
acms.o:acms.c
	$(CC) -c acms.c
menu.o:menu.c menu.h 
	$(CC) -c menu.c
list.o:list.c
	$(CC) -c list.c
clean:
	rm *.o acms
run:
	./acms root root
