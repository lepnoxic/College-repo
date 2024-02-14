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

int isPalindrome(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        if (str[i] != str[length - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

void countVowels(char *str, int *vowelCount) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' ||
            str[i] == 'u' || str[i] == 'A' || str[i] == 'E' || str[i] == 'I' ||
            str[i] == 'O' || str[i] == 'U') {
            ++vowelCount[str[i]];
        }
    }
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

        if (strcmp("Halt", buff) == 0) {
            close(sockfd);
            close(newsockfd);
            return 0;
        }

        char first[strlen(buff) + 1];
        strcpy(first, buff);

        int vowelCount[256] = {0};
        countVowels(first, vowelCount);

        char result[MAXSIZE];
        sprintf(result, "Length: %ld\n", strlen(first));

        strcat(result, isPalindrome(first)
                           ? "Palindrome\n"
                           : "Not Palindrome\n");

        strcat(result, "Vowel Counts:\n");
        for (int i = 0; i < 256; i++) {
            if (vowelCount[i] != 0) {
                sprintf(result + strlen(result), "%c: %d\n", i, vowelCount[i]);
            }
        }

        sentbytes = sendto(sockfd, result, strlen(result), 0,
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
