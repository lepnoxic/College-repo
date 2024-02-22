#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
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
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);

    printf("Recieved bytes: ");
    fflush(stdout);
    char buffer;
    
    while(recv(clientSocket, &buffer, sizeof(buffer), 0)) {
        printf("%c", buffer);
        fflush(stdout);
        sleep(1);
    }

    close(serverSocket);
    return 0;
}