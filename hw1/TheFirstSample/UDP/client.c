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
    // time function 
    struct  timeval start;
    struct  timeval end;
    unsigned long diff;



    //socket的建立
    int sockfd = 0, byteSent,byteRecv;
    char message[SEND_MAX] = {0};
    char receiveMessage[RECV_MAX] = {};

    printf("*** HINT: send \"exit\" to close the server ***\n");
    printf("Packet content: ");
    scanf("%[^\n]",message);
    sockfd = socket(AF_INET , SOCK_DGRAM , 0);
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
    info.sin_family = AF_INET;

    //localhost test
    info.sin_addr.s_addr = inet_addr("127.0.0.1");
    info.sin_port = htons(8080);
    int address_length = sizeof(info);

    
    //Send a message to server
    byteSent = sendto(sockfd, message, sizeof(message),0, (struct sockaddr *)&info, address_length);
    gettimeofday(&start,NULL); ////
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
    gettimeofday(&end,NULL);////
    printf("Server : %s\n", receiveMessage); 

    diff = 1000000 *(end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    printf("latency =  %lf sec\n",(double)diff / 1000000 );   
        
        
    
    close(sockfd);
    return 0;
}