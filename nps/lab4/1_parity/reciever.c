#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void printBinary(int num) {
    printf("0b");
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
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

    // Receive data
    unsigned char binaryData[BUFFER_SIZE];
    recv(new_sock, binaryData, BUFFER_SIZE, 0);
    int buffer_len = strlen(binaryData);
    // Check parity
    int i;
    for (i = 0; i < buffer_len; i++) {
        int count = 0;
        unsigned char temp = binaryData[i];
        printf("Current byte ");
        printBinary(binaryData[i]);
        while (temp) {
            count += temp & 1;
            temp >>= 1;
        }
        if (count % 2 == 0)
            printf("Byte %d: Even parity\n", i);
        else
            printf("Byte %d: Odd parity\n", i);
    }

    close(new_sock);
    close(sockfd);
    return 0;
}
