#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

static void test()
{
    printf("Connection Made!  Closing...");
}

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    char sendBuff[1024];
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    /* get an internet domain socket */
    if (listenfd == -1) {
	perror("socket");
	exit(1);
    }

    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    
    /* Initialize Socket Structure */

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    /* bind socket to port number */
    if (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
	perror("binding failed");
	exit(1);
    }    

    if (listen(listenfd, 10) == -1) {
	perror("listen error");
	exit(1);
    }

    while(1)
	{
	    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
	    read(connfd, sendBuff, strlen(sendBuff)); 

	    snprintf(sendBuff, sizeof(sendBuff),"Hi there!");
	    write(connfd, sendBuff, strlen(sendBuff)); 

	    close(connfd);
	    sleep(1);
	}
    test();
}
