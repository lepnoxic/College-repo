#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAXSIZE 90

int main()
{
	int sockfd,retval,i;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr, clientaddr;
	char buff[MAXSIZE];
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd==-1)
	{
		printf("\nSocket Creation Error");
		return 1;
	}
	int portno;
    printf("Enter client port no: ");
    scanf("%d", &portno);

    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(portno);
    clientaddr.sin_addr.s_addr = htons(INADDR_ANY);

    printf("Enter server port no: ");
    scanf("%d", &portno);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(portno);
    serveraddr.sin_addr.s_addr = htons(INADDR_ANY);

	retval=bind(sockfd,(struct sockaddr*)&clientaddr,sizeof(clientaddr));
	if(retval==1)
	{
		printf("Binding error");
		close(sockfd);
	}

    char first[MAXSIZE], second[MAXSIZE];
    getchar();
    printf("Enter first string: ");
    fgets(first, MAXSIZE, stdin);
    // first[strlen(first) - 1] = "\0";
    printf("Enter second string: ");
    fgets(second, MAXSIZE, stdin);
    second[strlen(second) - 1] = '\0';

    strcat(first, second);

    sentbytes=sendto(sockfd,first,strlen(first) + 1,0,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

    int actuallen = sizeof(serveraddr);

    recedbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&serveraddr, &actuallen);

    puts(buff);
	
	close(sockfd);

    return 0;
}
