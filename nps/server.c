#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 2

void processClient(int clientSocket, struct sockaddr_in clientAddr);

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, MAX_CLIENTS) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
        if (clientSocket == -1) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        if (fork() == 0) {
            close(serverSocket); 
            processClient(clientSocket, clientAddr);
            exit(0); 
        } else {
            close(clientSocket);
        }
    }

    close(serverSocket);
    return 0;
}

void processClient(int clientSocket, struct sockaddr_in clientAddr) {
    char buffer[1024];
	char cmpbuffer[13];
	char cmpsecbuffer[11];
    recv(clientSocket, buffer, sizeof(buffer), 0);
	
	strcpy(cmpbuffer, buffer);
	cmpbuffer[12] = '\0';


    if (strcmp(cmpbuffer, "Institute Of") == 0) {
        printf("Received: Institute Of from %s:%d\n",
               inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
        FILE *file = fopen("textfile.txt", "a");
        if (file != NULL) {
            fprintf(file, "Institute Of ");
            fclose(file);
        }
    } 
	
	strcpy(cmpsecbuffer, cmpbuffer);
	cmpsecbuffer[10] = '\0';

	if (strcmp(cmpsecbuffer, "Technology") == 0) {
        printf("Received: Technology from %s:%d\n",
               inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
        FILE *file = fopen("textfile.txt", "a");
        if (file != NULL) {
            fprintf(file, "Technology ");
            fclose(file);
        }
    }

    close(clientSocket);
}
