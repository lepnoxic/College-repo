#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include <arpa/inet.h>
#define MAXSIZE 90

int main() {
	char buff[MAXSIZE];
	int sockfd,retval,i;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("\nSocket Creation Error");
		return 0;
	}

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==-1)
	{
		printf("Connection error");
		return 0;
	}


    if (recv(sockfd, buff, sizeof(buff), 0) < 0) return 1;
    printf("%s", buff);

    int size;

    scanf("%d", &size);

    if (send(sockfd, &size, sizeof(size), 0) < 0) return 1;

    if (recv(sockfd, buff, sizeof(buff), 0) < 0) return 1;
    printf("%s", buff);

    for (int i = 0; i < size; i++) {
        int current;
        scanf("%d", &current);
        if (send(sockfd, &current, sizeof(current), 0) < 0) return 1;
    }

    if (recv(sockfd, buff, sizeof(buff), 0) < 0) return 1;
    printf("%s", buff);

    while(1) {
        if (recv(sockfd, buff, sizeof(buff), 0) < 0) break;
        printf("%s", buff);

        int choice;
        if (send(sockfd, &choice, sizeof(choice), 0) < 0) break;

        if (choice == 1) {
            if (recv(sockfd, buff, sizeof(buff), 0) < 0) break;
            printf("%s", buff);

            int element;
            if (send(sockfd, &element, sizeof(element), 0) < 0) break;
        }

        if (recv(sockfd, buff, sizeof(buff), 0) < 0) break;
        printf("%s", buff);


    }

	close(sockfd);
    return 0;
}