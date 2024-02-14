#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXSIZE 5500

void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}


void permute(char *str, int start, int end) {
    if (start == end)
        printf("%s\n", str);
    else {
        for (int i = start; i <= end; i++) {
            swap((str + start), (str + i));
            permute(str, start + 1, end);
            swap((str + start), (str + i));
        }
    }
}

int main() {
    int sockfd, newsockfd, retval;
    socklen_t actuallen;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr, clientaddr;
    pid_t pid;
    char receivemsg[MAXSIZE];
    int a = 0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        printf("\nSocket creation error");
        exit(0);
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
        exit(0);
    }

    retval = listen(sockfd, 1);
    if (retval == -1) {
        close(sockfd);
        exit(0);
    }

    actuallen = sizeof(clientaddr);
    newsockfd = accept(sockfd, (struct sockaddr*)&clientaddr, &actuallen);

    
    recedbytes = recv(newsockfd, receivemsg, sizeof(receivemsg), 0);

    permute(receivemsg, 0, strlen(receivemsg) - 1);

    close(sockfd);
    close(newsockfd);
}
