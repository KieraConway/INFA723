// server.c - a stream socket server demo
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <openssl/des.h>

// how many pending connections queue will hold
#define BACKLOG 10

// max number of bytes we can get at once
#define MAXDATASIZE 1024

void sigchld_handler(int s)
{
	while(wait(NULL) > 0);
}

int main(int argc, char *argv[ ])
{
	// the port users will be connecting to
	int port = 3456;

    // listen on sock_fd, new connection on new_fd
    int sockfd, new_fd, numbytes;

    // my address information
    struct sockaddr_in my_addr;

    // connector’s address information
    struct sockaddr_in their_addr;

    char buf[MAXDATASIZE];
    int sin_size;
    struct sigaction sa;
    int yes = 1;

	if (argc != 3)
	{
		printf("Usage: server host portnum\n");
		exit(1);
	}

	// port number
	port = atoi(argv[2]);

	// create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Server: socket() error lol!");
        exit(1);
    }
    else
	{
	    printf("Server: socket() sockfd is OK...\n");
	}

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        perror("Server: setsockopt() error lol!");
        exit(1);
    }
    else
	{
        printf("Server: setsockopt is OK...\n");
	}

    // host byte order
    my_addr.sin_family = AF_INET;

    // short, network byte order
    my_addr.sin_port = htons(port);

    // automatically fill with my IP
    my_addr.sin_addr.s_addr = INADDR_ANY;

    printf("Server: using %s and port %d...\n", inet_ntoa(my_addr.sin_addr), port);

    // zero the rest of the struct
    memset(&(my_addr.sin_zero), '\0', 8);

	// bind
    if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("Server: bind() error");
        exit(1);
    }
    else
	{
        printf("Server: bind() is OK...\n");
	}

	// listen to client connection
    if(listen(sockfd, BACKLOG) == -1)
    {
        perror("Server: listen() error");
        exit(1);
    }

    printf("Server: listen() is OK...Listening...\n");

    // clean all the dead processes
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if(sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("Server: sigaction() error");
        exit(1);
    }
    else
	{
        printf("Server: sigaction() is OK...\n");
	}

	// init des
	DES_cblock key, input, output;
	DES_key_schedule sched;
	int c, i, j;

	fprintf(stderr, "Setting up the DES library...\n");
	DES_string_to_key("Mary had a little lamb, it's fleece as white as snow. Everywhere that Mary went, the lamb would surely go...", &key);

	fprintf(stderr, "Schedualling the key...\n");
	switch(DES_set_key_checked(&key, &sched))
	{
		case -1:
		fprintf(stderr, "Bad parity\n");
 		_exit(42);
		break;

	case -2:
 		fprintf(stderr, "Key is weak\n");
 		_exit(42);
		break;
	}

    // accept() loop
    while (1)
    {
		printf("\n");

    	sin_size = sizeof(struct sockaddr_in);

    	if((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
    	{
    	    perror("Server: accept() error");
    	    continue;
    	}
    	else
		{
			printf("Server: accept() is OK...\n");
		}

    	printf("Server: new socket, new_fd is OK...\n");
    	printf("Server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));

		i = 0;

    	// this is the child process
    	if(!fork())
    	{
    	    // child doesn’t need the listener
       		close(sockfd);

			if((numbytes = recv(new_fd, &(buf[i]), MAXDATASIZE-1, 0)) == -1)
			{
				perror("recv()");
				exit(1);
			}
			else
			{
				printf("client: the recv() is OK...\n\n");
				printf("Cipher text received: \n%s\n", buf);
				printf("\nPlaintext received after decrypting:\n\n");

				// decrypting
				i = 0;
				j = 0;

				while (1)
				{
					input[i] = buf[j];
					i++; j++;

					if (i == 8)
					{
					  DES_ecb_encrypt(&input, &output, &sched, DES_DECRYPT);
					  fprintf(stdout, "%c%c%c%c%c%c%c%c", output[0], output[1], output[2],
						  output[3], output[4], output[5], output[6], output[7]);
					  i = 0;
					}

					if (buf[j] == '\0')
						break;
				}

				printf("\n");
			}

			i = i + numbytes;
			buf[i] = '\0';

       		close(new_fd);
       		exit(0);
    	}
    	else
		{
    	    printf("Server: send is OK...!\n");
		}

    	// parent doesn’t need this
    	close(new_fd);

    	printf("Server: new socket, new_fd closed successfully...\n");
    }

	return 0;
}
