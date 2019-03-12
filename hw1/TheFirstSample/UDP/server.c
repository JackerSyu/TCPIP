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
    sockfd = socket(AF_INET , SOCK_DGRAM , 0);
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
    int byteRecv, byteSent;
    int clientAddrLen = sizeof(clientInfo);
    bzero(&serverInfo,sizeof(serverInfo));

    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(8080);
    printf("\tbinding...\n");
    if (bind(sockfd,(struct sockaddr *)&serverInfo,sizeof(serverInfo)) == -1)
    {
        printf("\tfailed to bind...\n");
        close(sockfd);
        return 0;
    }
    else
    {
        printf("\tbinded successfully!\n");
    }
    
    
    while(1)
    {
        printf("\twaitting  for connection...\n\n****************************************************\n");
        
        byteRecv = recvfrom(sockfd, inputBuffer, sizeof(inputBuffer), 0, (struct sockaddr *)&clientInfo,&clientAddrLen);
        if (byteRecv < 0)
        {
            printf("\tfail to receive the packet\n");
        }
        printf("\tRecieved packet: %s \n",inputBuffer);

        byteSent = sendto(sockfd, message, sizeof(message),0, (const struct sockaddr *) &clientInfo, clientAddrLen); 
        if(byteSent < 0)
        {
            printf("\tFail to send packet....\n");
            close(sockfd);
            return 0;
        }
        else
        {
            printf("\tResponse packet: %s\n",message);
        }
         if((strcmp(inputBuffer, "exit")) == 0)
        {
            printf("Detected the exit instruction see you then!\n");
            return 0;
        }
    }
       
    return 0;
}