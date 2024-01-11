#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90

int main()
{
	int sockfd,newsockfd,retval,i;
	socklen_t actuallen;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr,clientaddr;
	char buff[MAXSIZE];
	
	int a=0;
	sockfd=socket(AF_INET,SOCK_STREAM,0);

	if(sockfd==-1)
	{
	printf("\nSocket creation error");
	}

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
	retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==1)
	{
		printf("Binding error");
		close(sockfd);
	}

	retval=listen(sockfd,1);
	if(retval==-1)
	{
	close(sockfd);
	}
	actuallen=sizeof(clientaddr);
	newsockfd=accept(sockfd,(struct sockaddr*)&clientaddr,&actuallen);
	if(newsockfd==-1)
	{
		close(sockfd);
	}
	

    char initbuff[] = "Enter size of array: ";
    if (send(newsockfd, initbuff, sizeof(initbuff), 0) < 0) return 1;

    int size;
    if (recv(newsockfd, &size, sizeof(size), 0) < 0) return 1;

    char askingarray[] = "Enter elements: ";
    if (send(newsockfd, askingarray, sizeof(askingarray), 0) < 0) return 1;

    int mainarray[size];

    for (int i = 0; i < size; i++) {
        int current;
        if (recv(newsockfd, &current, sizeof(current), 0) < 0) return 1;
        mainarray[i] = current;
    }

    char *prompt, *request;
    char menu[] = "1) Search for number\n2) Sort numbers in ascending\n3) Sort numbers in descending\n4) Display Odd\n5)Display Even\n6) Exit\nEnter choice: ";
    char ask[] = "Enter choice: ";
    if (send(newsockfd, menu, sizeof(menu), 0) < 0) return 1;
    while(1) {
        if (send(newsockfd, ask, sizeof(ask), 0) < 0) return 1;

        int choice;
        if (recv(newsockfd, &choice, sizeof(choice), 0) < 0) return 1;

        if (choice == 6) break;



        switch(choice) {
            case 1:
                request = "Enter element to find: ";
                if (send(newsockfd, request, sizeof(request), 0) < 0) return 1;

                int element;
                if (recv(newsockfd, &element, sizeof(element), 0) < 0) return 1;

                int found = 0;
                for (int i = 0; i < size; i++) {
                    if (mainarray[i] == element) {
                        found = 1;
                        break;
                    }
                }
                if (found) prompt = "Element found";
                else prompt = "Element not found";
                break;
            default:
                prompt = "Wrong input";
        }

    }



	close(sockfd);
	close(newsockfd);
    return 0;
}
