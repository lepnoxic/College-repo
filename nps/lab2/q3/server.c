#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
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

    pid = fork();
    if (pid == 0) {
        char outputbuff[strlen(receivemsg) + 1];
        int num_idx = 0;
        for (int i = 0; i < strlen(receivemsg); i++) {
            if (isdigit(receivemsg[i])) {
                outputbuff[num_idx++] = receivemsg[i];
            }
        }
        outputbuff[num_idx] = '\0';

        for (int i = 0; i < num_idx - 1; i++) {
            for (int j = i + 1; j < num_idx; j++) {
                if (outputbuff[i] > outputbuff[j]) {
                    char temp = outputbuff[i];
                    outputbuff[i] = outputbuff[j];
                    outputbuff[j] = temp;
                }
            }
        }

        sprintf(buff, "Output at the child pid %d of the server: %s\n", getpid(), outputbuff);

        sentbytes = send(newsockfd, buff, sizeof(buff), 0);

    } else if (pid > 0) {
        char outputbuff[strlen(receivemsg) + 1];
        int num_idx = 0;
        for (int i = 0; i < strlen(receivemsg); i++) {
            if (isalpha(receivemsg[i])) {
                outputbuff[num_idx++] = receivemsg[i];
            }
        }
        outputbuff[num_idx] = '\0';

        for (int i = 0; i < num_idx - 1; i++) {
            for (int j = i + 1; j < num_idx; j++) {
                if (outputbuff[i] < outputbuff[j]) {
                    char temp = outputbuff[i];
                    outputbuff[i] = outputbuff[j];
                    outputbuff[j] = temp;
                }
            }
        }
        sprintf(buff, "Output at the parent pid %d of the server: %s\n", getpid(), outputbuff);
        sentbytes = send(newsockfd, buff, sizeof(buff), 0);
    }

    close(sockfd);
    close(newsockfd);
}
