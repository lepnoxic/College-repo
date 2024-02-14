#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void printStringBinary(const char *str) {
    while (*str) {
        for (int i = 7; i >= 0; i--) {
            printf("%d", (*str >> i) & 1);
        }
        str++;
    }
    printf("\n");
}

int main() {
    int sockfd, new_sock;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server information
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind socket
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(sockfd, 5) == -1) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    // Accept connection
    if ((new_sock = accept(sockfd, (struct sockaddr *)&cliaddr, &len)) == -1) {
        perror("Accepting connection failed");
        exit(EXIT_FAILURE);
    }

    unsigned char binaryData[BUFFER_SIZE];
    recv(new_sock, binaryData, BUFFER_SIZE, 0);
    printStringBinary(binaryData);
    int buffer_len = strlen(binaryData);
    int i;
    for (int i = 0; i < buffer_len; i++) {
        int count = 0;
        for (int j = 0; j < 8; j++) {
            if ((binaryData[i] >> j) & 1)
                count++;
        }
        printf("Byte %d: %s parity\n", i, count % 2 == 0 ? "Even" : "Odd");
    }
    close(new_sock);
    close(sockfd);
    return 0;
}
