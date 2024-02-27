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

// max number of bytes we can get at once
#define MAXDATASIZE 300

int main(int argc, char *argv[])
{
	int sockfd, i, c;
    char buf[MAXDATASIZE];
    struct hostent *he;

	// the port client will be connecting to
	int port = 3456;

	// plaintext file handler
	FILE *pFile;
	char input[8];

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

	// open plaintext file to read
	pFile = fopen(argv[3], "r");

	if (pFile == NULL)
	{
			perror("Error opeing file\n");
	}
	else
	{
		// send plaintext to server
		printf("Client: send plaintext\n\n");

		i = 0;
		memset(input, 0, sizeof(input));
  		while (1)
  		{
			c = fgetc(pFile);

    		input[i] = c;
			i++;

			if ((i == 8) || (c == EOF))
			{
				if (send(sockfd, input, 8, 0) == -1)
				{
					perror("Client: send() error lol!");
				}

				// print plaintext
				printf("%c%c%c%c%c%c%c%c", input[0],input[1],input[2],input[3],input[4],input[5],input[6],input[7]);

				i = 0;
				memset(input, 0, sizeof(input));
			}

			if (c == EOF)
			{
				// the end of plaintext
				break;
			}
		}

		printf("\n\n");
	}

    printf("Client: received: %s", buf);
    printf("Client: closing sockfd\n");

	// close plaintext
	fclose(pFile);

	// close socket
    close(sockfd);

    return 0;

}
