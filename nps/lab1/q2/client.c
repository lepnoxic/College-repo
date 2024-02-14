#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXSIZE 90

int main() {
    int sockfd, retval, i;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr, clientaddr;
    char buff[MAXSIZE];
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
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

    retval = bind(sockfd, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
    if (retval == 1) {
        printf("Binding error");
        close(sockfd);
    }

    char first[MAXSIZE];
    getchar();

    while (1) {
        printf("Enter string: ");
        fgets(first, MAXSIZE, stdin);
        first[strlen(first) - 1] = '\0';

        sentbytes = sendto(sockfd, first, strlen(first) + 1, 0,
                           (struct sockaddr*)&serveraddr, sizeof(serveraddr));

        if (sentbytes <= 0) exit(0);

        int actuallen = sizeof(serveraddr);

        recedbytes = recvfrom(sockfd, buff, sizeof(buff), 0,
                              (struct sockaddr*)&serveraddr, &actuallen);

        if (recedbytes <= 0) exit(0);

        puts(buff);
    }

    close(sockfd);
    return 0;
}
