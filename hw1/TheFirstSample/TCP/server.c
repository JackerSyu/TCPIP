#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc , char *argv[])

{
    //socket的建立
    char inputBuffer[256] = {};
    char message[] = {"welcome\n"};
    int sockfd = 0,forClientSockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    printf("****************************************************\n");
    if (sockfd == -1){
        printf("Fail to create a socket.");
    }
    else
    {
        printf("\tbuilding socket successfully!\n ");
    }

    //socket的連線
    struct sockaddr_in serverInfo,clientInfo;
    int addrlen = sizeof(clientInfo);
    bzero(&serverInfo,sizeof(serverInfo));

    serverInfo.sin_family = PF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(8080);
    bind(sockfd,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
    printf("\tbinding...\n");
    listen(sockfd,5);
    printf("\tlisting...\n");
    

    while(1){

        printf("\twaitting  for connection...\n\n****************************************************\n");
        printf("\twait for connection...\n");
        forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);
        printf("\taccept...\n");
        recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
        printf("\tReceived packet :%s\n",inputBuffer);
        send(forClientSockfd,message,sizeof(message),0);
        printf("\tResponse packet :%s\n", message);

        if((strcmp(inputBuffer, "exit")) == 0)
        {
            printf("Detected the exit instruction see you then!\n");
            return 0;
        }
    }
    return 0;
}