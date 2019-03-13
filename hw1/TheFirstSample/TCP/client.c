/*

Basic: Socket Programming with UDP & TCP (75 pts)
 UDP Socket Programming: send/receive UDP packets.
 TCP Socket Programming: send/receive TCP packets

Advanced: 
Measure the latency of UDP and TCP packets, respectively (10 pts)

Measure the throughput (Mbps) by using UDP and TCP sockets, respectively (15 pts)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SEND_MAX 256
#define RECV_MAX 256

int main(int argc , char *argv[])
{

    //socket的建立
    int sockfd = 0; 
    char message[SEND_MAX] = {0};
    char receiveMessage[RECV_MAX] = {};

    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    printf("*** HINT: send \"exit\" to close the server ***\n");
    printf("Packet content: ");
    scanf("%[^\n]",message); // 解決scanf無法讀取空格問題
    printf("****************************************************\n\n");
    if (sockfd == -1){
        printf("Fail to create a socket.");
    }
    else
    {
        printf("\tbuilding socket successfully... \n");
    }

    //socket的連線

    struct sockaddr_in info;
    bzero(&info,sizeof(info));
    info.sin_family = PF_INET;
    info.sin_addr.s_addr = inet_addr("127.0.0.1");
    info.sin_port = htons(8080);


    int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
    if(err == -1)
    {
        printf("Connection error");
        close(sockfd);
        return 0;
    }
    else
    {
        printf("\tSocket connection successfully...\n");
    }


    //Send a message to server
    if(send(sockfd,message,sizeof(message),0) == -1)
    {
        printf("\tFail to send packet....\n");
        close(sockfd);
        return 0;
    }
    else
    {
        printf("\tsending  a message: %s \n", message);
    }
    
    if(recv(sockfd,receiveMessage,sizeof(receiveMessage),0) == -1)
    {
        printf("\tfail to receive the packet\n");
        close(sockfd);
        return 0;
    }
    else
    {
        printf("\n****************************************************\n");
        printf("\treceived a message: %s\n",receiveMessage);
        printf("\tclose Socket\n");
    }

    close(sockfd);
    return 0;
}