#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"

#define BUCKET_SIZE 10
#define INPUT_RATE 4
#define OUTPUT_RATE 1

int intervals[] = {1, 2, 3, 5, 6, 8, 11, 12, 15, 16, 19};
int intervals_len = sizeof(intervals) / sizeof(int);
char data[] = "Hello world nice day bro, nice weather also";
int data_len = (sizeof(data) / sizeof(char));

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int portno;
    printf("Enter port no: ");
    scanf("%d", &portno);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(portno);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr,
                sizeof(serverAddr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    int ta = 0;                 // arrival time
    int aux_var = BUCKET_SIZE;  // auxillary variable
    int cur_var = 0;            // leaky bucket counter
    int lct = 0;                // last conformance time

    while(cur_var <= data_len) {
        
    }

    close(clientSocket);
    return 0;
}
