#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAXSIZE 5500

int main() {
    pid_t pid;
    int sockfd, retval;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr;
    char buff[MAXSIZE], sendmsg[5500];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("\nSocket Creation Error");
    }
    int portno;
    printf("Enter port no: ");
    scanf("%d", &portno);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(portno);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    retval = connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (retval == -1) {
        printf("Connection error");
    }

    pid = fork();
    if (pid == 0) {
        printf("Child, pid: %d, ppid: %d\n", getpid(), getppid());
        while (1) {
            scanf("%s", sendmsg);
            send(sockfd, sendmsg, sizeof(sendmsg), 0);
        }
    } else if (pid > 0) {
        printf("Parent, pid: %d, ppid: %d\n", getpid(), getppid());
        while (1) {
            recedbytes = recv(sockfd, buff, sizeof(buff), 0);
            if (recedbytes <= 0) {
                close(sockfd);
                exit(0);  
            }
            puts(buff);
        }
    }
}
