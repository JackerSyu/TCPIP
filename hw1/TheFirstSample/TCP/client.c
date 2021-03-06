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
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SEND_MAX 256
#define RECV_MAX 256

int main(int argc , char *argv[])
{
    // time function , more info to the folder of TimeFunction or reference [2]
    struct  timeval start;
    struct  timeval end;
    unsigned long diff;

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
    int byteSend, byteRecv;
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
    byteSend = send(sockfd,message,sizeof(message),0);
    gettimeofday(&start,NULL); //// start to cal the time
    if( byteSend == -1)
    {
        printf("\tFail to send packet....\n");
        close(sockfd);
        return 0;
    }
    else
    {
        printf("\tsending  a message: %s \n", message);
    }
    
    byteRecv = recv(sockfd,receiveMessage,sizeof(receiveMessage),0);
    gettimeofday(&end,NULL);//// end to cal the time 
    if( byteRecv == -1)
    {
        printf("\tfail to receive the packet\n");
        close(sockfd);
        return 0;
    }
    else
    {
        printf("\n****************************************************\n");
        printf("Server: %s\n",receiveMessage);
    }
    diff = 1000000 *(end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    double latency = (double)diff / 1000000;
    printf("latency =  %lf sec\n", latency);  
    close(sockfd);
    printf("throughput= %lf MB/sec\n", ((sizeof(message) + sizeof(receiveMessage)) / latency) / (1024 * 1024));
    return 0;
}