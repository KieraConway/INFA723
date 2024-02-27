IDIR =../.
CC=gcc
CFLAGS=-I$(IDIR)

LDIR =../lib
LIBS=-lcrypto

all : client server
.PHONY : all

client :
	$(CC) client.c -o client $(CFLAGS) $(LIBS)

server :
	$(CC) server.c -o server $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f *.o  
	rm client
	rm server