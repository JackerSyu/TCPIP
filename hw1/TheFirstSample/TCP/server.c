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
    
    printf("****************************************************\n");
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd == -1){
        printf("Fail to create a socket.");
        close(sockfd);
    }
    else
    {
        printf("\tbuilding socket successfully!\n ");
    }

    //socket的連線
    struct sockaddr_in serverInfo,clientInfo;
    int addrlen = sizeof(clientInfo);
    int byteSend, byteRecv; // just to check the return value 
    bzero(&serverInfo,sizeof(serverInfo));

    serverInfo.sin_family = PF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(8080);
    
    bind(sockfd,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
    printf("\tbinding...\n");
    if(listen(sockfd,5) == 01)
    {
        printf("listening failed !\n");
        close(sockfd);
    }
    printf("\tlisting...\n");
    

    while(1){

        printf("\twaitting  for connection...\n\n****************************************************\n");
        printf("\twaitting for connection...\n");
        forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);
        printf("\taccept...\n");
        
        byteRecv = recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
        if(byteRecv < 0)
        {
            printf("\tFail to send packet....\n");
            close(sockfd);
            return 0;
        }
        else
        {
            printf("\tResponse packet: %s\n",inputBuffer);
        }

        byteSend = send(forClientSockfd,message,sizeof(message),0);
        if (byteSend < 0)
        {
            printf("\tfail to receive the packet\n");
            close(sockfd);
            return 0;
        }
        else
        {
            printf("\tRecieved packet: %s \n",message);
        }
        // detecting to exit program
        if((strcmp(inputBuffer, "exit")) == 0)
        {
            printf("Detected the exit instruction see you then!\n");
            close(sockfd);
            return 0;
        }
    }
    return 0;
}