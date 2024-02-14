#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#define MAXSIZE 90

int areAnagrams(char *str1, char *str2) {
    // Get lengths of both strings
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // If lengths are not equal, strings can't be anagrams
    if (len1 != len2) return 0;

    // Sort both strings
    for (int i = 0; i < len1 - 1; i++) {
        for (int j = i + 1; j < len1; j++) {
            if (str1[i] > str1[j]) {
                char temp = str1[i];
                str1[i] = str1[j];
                str1[j] = temp;
            }
            if (str2[i] > str2[j]) {
                char temp = str2[i];
                str2[i] = str2[j];
                str2[j] = temp;
            }
        }
    }

    // Compare sorted strings
    for (int i = 0; i < len1; i++) {
        if (str1[i] != str2[i]) return 0;
    }

    return 1;
}

int main() {
    int sockfd, newsockfd, retval, i;
    socklen_t actuallen;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr, clientaddr;

    char buff[MAXSIZE];
    int a = 0;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == -1) {
        printf("\nSocket creation error");
    }

    int portno;
    printf("Enter server port no: ");
    scanf("%d", &portno);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(portno);
    serveraddr.sin_addr.s_addr = htons(INADDR_ANY);

    retval = bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (retval == 1) {
        printf("Binding error");
        close(sockfd);
    }

    while (1) {
        actuallen = sizeof(clientaddr);
        recedbytes = recvfrom(sockfd, buff, sizeof(buff), 0,
                              (struct sockaddr *)&clientaddr, &actuallen);
        if (recedbytes == -1) {
            perror("Receive error");
            close(sockfd);
            return 1;
        }
        buff[recedbytes] = '\0';

        time_t currentTime;
        struct tm *localTime;
        time(&currentTime);
        localTime = localtime(&currentTime);

        char formattedTime[30];
        strftime(formattedTime, sizeof(formattedTime), "%d-%m-%Y %H:%M:%S", localTime);

        printf("%s : Connection recieved from %s:%d \n", formattedTime, inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

        char first[MAXSIZE], second[MAXSIZE];
        char *token = strtok(buff, "\n");
        strcpy(first, token);
        token = strtok(NULL, "\n");
        strcpy(second, token);

        if (areAnagrams(first, second)) {
            sprintf(buff, "Given strings were anagrams");
        } else {
            sprintf(buff, "Given strings were not anagrams");
        }

        sentbytes = sendto(sockfd, buff, strlen(buff), 0,
                           (struct sockaddr *)&clientaddr, sizeof(clientaddr));
        if (sentbytes == -1) {
            perror("Send error");
            close(sockfd);
            return 1;
        }
    }
    close(sockfd);
    close(newsockfd);
    return 0;
}
