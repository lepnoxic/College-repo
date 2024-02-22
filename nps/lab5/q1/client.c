#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"

#define BUCKET_SIZE 10
#define INPUT_RATE 4
#define OUTPUT_RATE 1

int intervals[] = {1, 2, 3, 5, 6, 8, 11, 12, 15, 16, 19};
int intervals_len = sizeof(intervals)/sizeof(int);
char data[] = "Hello world nice day bro, nice\0";
int data_len = (sizeof(data) / sizeof(char)) - 1;


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

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    char bucket[BUCKET_SIZE] = {0}; // Initialize bucket
    int front = 0; // Initialize front to 0
    int back = 0;

    int time = 0;
    int current_index = 0;
    int data_index = 0;
    int limit = 0;

    while(time <= intervals[intervals_len - 1]) { // Loop till all intervals are processed
        printf("Current bucket: [");
        for (int i = 0; i < strlen(bucket); i++) {
            printf("%c, ", bucket[i]);
        }
        printf("]\n");

        if (current_index < intervals_len && time == intervals[current_index] && limit < data_len) {
            // Push into bucket
            limit = data_index + INPUT_RATE;
            for (int i = data_index; i < limit && back < BUCKET_SIZE; i++)
                bucket[back++ % BUCKET_SIZE] = data[i];
            data_index = limit;
            current_index++;
        }

        if (front != back) {
            // Pop from bucket and send
            int send_size = (back - front) > OUTPUT_RATE ? OUTPUT_RATE : (back - front);
            send(clientSocket, &bucket[front % BUCKET_SIZE], send_size, 0);
            front += OUTPUT_RATE;
        } else {
            printf("Bucket empty\n");
        }

        sleep(1);
        time++;
    }

    close(clientSocket);
    return 0;
}
