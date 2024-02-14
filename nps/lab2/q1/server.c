#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXSIZE 5500

int main() {
    int sockfd, newsockfd, retval;
    socklen_t actuallen;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr, clientaddr;
    pid_t pid;
    char buff[MAXSIZE], receivemsg[5500];
    int a = 0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        printf("\nSocket creation error");
    }

    int portno;
    printf("Enter port no: ");
    scanf("%d", &portno);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(portno);
    serveraddr.sin_addr.s_addr = htons(INADDR_ANY);
    retval = bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (retval == 1) {
        printf("Binding error");
        close(sockfd);
    }

    retval = listen(sockfd, 1);
    if (retval == -1) {
        close(sockfd);
    }

    actuallen = sizeof(clientaddr);
    newsockfd = accept(sockfd, (struct sockaddr*)&clientaddr, &actuallen);

    pid = fork();
    if (pid == 0) {
        printf("Child, pid: %d, ppid: %d\n", getpid(), getppid());
        while (1) {
            recedbytes = recv(newsockfd, receivemsg, sizeof(receivemsg), 0);
            if (recedbytes <= 0) {
                close(sockfd);
                close(newsockfd);
                exit(0);  
            }
            puts(receivemsg);
        }
    } else if (pid > 0) {
        printf("Parent, pid: %d, ppid: %d\n", getpid(), getppid());
        while (1) {
            scanf("%s", buff);
            sentbytes = send(newsockfd, buff, sizeof(buff), 0);
        }
    }
    if (newsockfd == -1) {
        close(sockfd);
    }

    if (sentbytes == -1) {
        close(sockfd);
        close(newsockfd);
    }

    close(sockfd);
    close(newsockfd);
}
