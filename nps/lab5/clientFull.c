#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include <arpa/inet.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAXSIZE 5500

int main() {
    pid_t pid;
    int sockfd,retval;
    int recedbytes,sentbytes;
    struct sockaddr_in serveraddr;
    char buff[MAXSIZE],sendmsg[5500];
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1) printf("\nSocket Creation Error");
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(3388);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(retval==-1) printf("Connection error");

    pid=fork();
    if(pid==0) {
        while(1) {
            scanf("%s",sendmsg);
            send(sockfd,sendmsg,sizeof(sendmsg),0);
        }
    } else if(pid>0) {
        while(1){
            recedbytes=recv(sockfd,buff,sizeof(buff),0);
            puts(buff);
        }
    }
}
