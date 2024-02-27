// client.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <openssl/des.h>

// max number of bytes we can get at once
#define MAXDATASIZE 1024

int main(int argc, char *argv[])
{
	int sockfd, i, j, c;
    char buf[MAXDATASIZE];
    struct hostent *he;

	// the port client will be connecting to
	int port = 3456;

	// plaintext file handler
	FILE *pFile;

    // connector’s address information
    struct sockaddr_in their_addr;

    // if no command line argument supplied
    if(argc != 4)
    {
        printf("Usage: %s the_client_hostname portnum textfile\n", argv[0]);
        exit(1);
    }

	// port number
	port = atoi(argv[2]);

    // get the host info
    if ((he=gethostbyname(argv[1])) == NULL)
    {
        perror("gethostbyname()");
        exit(1);
    }
    else
	{
        printf("Client: the remote host is %s\n", argv[1]);
	}

	// create socket
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket()");
        exit(1);
    }
    else
	{
        printf("Client: the socket() sockfd is OK...\n");
	}

    // host byte order
    their_addr.sin_family = AF_INET;

    // short, network byte order
    printf("Server: %s and port %d...\n", argv[1], port);

    their_addr.sin_port = htons(port);
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);

    // zero the rest of the struct
    memset(&(their_addr.sin_zero), '\0', 8);

	// connect to server
    if(connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect()");
        exit(1);
    }
    else
	{
        printf("Client: connect() is OK...\n");
	}

	// init des
	DES_cblock key, input, output;
	DES_key_schedule sched;

	fprintf(stderr, "Setting up the DES library...\n");
	DES_string_to_key("Mary had a little lamb, it's fleece as white as snow. Everywhere that Mary went, the lamb would surely go...", &key);

	fprintf(stderr, "Schedualling the key...\n");

	switch(DES_set_key_checked(&key, &sched)){
		case -1:
			fprintf(stderr, "Bad parity\n");
			_exit(42);
			break;

		case -2:
			fprintf(stderr, "Key is weak\n");
			_exit(42);
			break;
	}

	// open plaintext file to read
	pFile = fopen(argv[3], "r");

	if (pFile == NULL)
	{
			perror("Error opeing file\n");
	}
	else
	{
		// send plaintext to server
		printf("Client: send cipher text\n\n");

		i = 0;
		j = 0;
		memset(input, 0, sizeof(input));

  		while (1)
  		{
			c = fgetc(pFile);

    		input[i] = c;
    		buf[j] = c;

			i++;
			j++;

			if ((i == 8) || (c == EOF))
			{
				// encryption
				DES_ecb_encrypt(&input, &output, &sched, DES_ENCRYPT);

				if (send(sockfd, output, 8, 0) == -1)
				{
					perror("Client: send() error lol!");
				}

				// print cipher text
				fprintf(stdout, "%c%c%c%c%c%c%c%c", output[0], output[1], output[2],
					output[3], output[4], output[5], output[6], output[7]);

				i = 0;
				memset(input, 0, sizeof(input));
			}

			if (c == EOF)
			{
				// the end of plaintext
				buf[j] = '\0';
				break;
			}
		}

		printf("\n\n");
	}

    printf("plaintext sent: \n\n%s\n\n", buf);

    printf("Client: closing sockfd\n");

	// close plaintext
	fclose(pFile);

	// close socket
    close(sockfd);

    return 0;

}
