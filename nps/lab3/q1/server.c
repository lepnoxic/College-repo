#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 2

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int portno;
    printf("Enter port no: ");
    scanf("%d", &portno);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(portno);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr,
             sizeof(serverAddr)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, MAX_CLIENTS) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
        if (clientSocket == -1) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        if (fork() == 0) {
            close(serverSocket);
            char buffer[1024];
            recv(clientSocket, buffer, sizeof(buffer), 0);
            if (strcmp(buffer, "Institute Of")) {
                printf("Received: Institute Of from %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
                FILE *file = fopen("textfile.txt", "a");
                if (file != NULL) {
                    fprintf(file, "Institute Of ");
                    fclose(file);
                }
            } else if (strcmp(buffer, "Technology")) {
                printf("Received: Technology from %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
                FILE *file = fopen("textfile.txt", "a");
                if (file != NULL) {
                    fprintf(file, "Technology ");
                    fclose(file);
                }
            }
            close(clientSocket);
            exit(0);
        } else {
            close(clientSocket);
        }
    }
    close(serverSocket);
    return 0;
}