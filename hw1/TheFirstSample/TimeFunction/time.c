#include<stdio.h>
#include<sys/time.h>
#include<unistd.h>
  
  
int main()
{
        struct  timeval start;
        struct  timeval end;
        
        unsigned long diff;
        gettimeofday(&start,NULL);
        sleep(5);
        gettimeofday(&end,NULL);
        diff = 1000000 *(end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        printf("thedifference is %lf sec\n",(double)diff / 1000000 );
        return 0;
        
}