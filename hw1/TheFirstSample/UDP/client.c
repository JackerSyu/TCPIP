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
    int sockfd = 0, byteSent,byteRecv;
    char message[SEND_MAX] = {0};
    char receiveMessage[RECV_MAX] = {};

    printf("*** HINT: send \"exit\" to close the server ***\n");
    printf("Packet content: ");
    scanf("%[^\n]",message);// 解決scanf無法讀取空格問題, more info to the reference [1] 

    printf("****************************************************\n\n");
    sockfd = socket(AF_INET , SOCK_DGRAM , 0);
    if (sockfd == -1){
        printf("Fail to create a socket.");
    }
    else
    {
        printf("\tbuilding socket successfully... \n");
    }

    //socket的連線
    struct sockaddr_in info;
    int address_length = sizeof(info);
    bzero(&info,sizeof(info));
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = inet_addr("127.0.0.1");
    info.sin_port = htons(8080);
    
    //Send a message to server
    byteSent = sendto(sockfd, message, sizeof(message),0, (struct sockaddr *)&info, address_length);
    gettimeofday(&start,NULL); //// start to cal the time
    if(byteSent < 0)
    {
        printf("\tFail to send packet....\n");
        close(sockfd);
        return 0;
    }
    else
    {
        printf("\tSent packet successfully....\n\n");
    }
    printf("****************************************************\n");
    byteRecv = recvfrom(sockfd, receiveMessage, sizeof(receiveMessage), 0, (struct sockaddr *) &info, &address_length); 
    gettimeofday(&end,NULL);//// end to cal the time 
    printf("Server : %s\n", receiveMessage); 

    diff = 1000000 *(end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    double latency = (double)diff / 1000000;
    printf("latency =  %lf sec\n", latency);   
    
    printf("throughput= %lf MB/sec\n", ((sizeof(message) + sizeof(receiveMessage)) / latency) / (1024 * 1024));
    close(sockfd);
    return 0;
}