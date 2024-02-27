IDIR =../.
CC=gcc
CFLAGS=-I$(IDIR)

LDIR =../lib

all : client server
.PHONY : all

client :
	$(CC) client.c -o client $(CFLAGS)

server :
	$(CC) server.c -o server $(CFLAGS)


.PHONY: clean

clean:
	rm -f *.o  
	rm client
	rm server