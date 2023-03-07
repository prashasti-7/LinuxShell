#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include<string.h>

int main(int argc, char* argv[])
{
    struct tm *currTime;
    time_t now;
    time(&now);
    if(argc==1){
        currTime = localtime(&now);
        printf ("%d/%d/%d %2d:%02d\n", currTime->tm_mday, currTime->tm_mon+1, currTime->tm_year+1900,currTime->tm_hour % 24, currTime->tm_min);
    }
    if(argc>=2){
        if(strcmp(argv[1],"-u")==0){
            currTime = gmtime(&now);
            printf ("%d/%d/%d %2d:%02d\n", currTime->tm_mday, currTime->tm_mon+1, currTime->tm_year+1900,currTime->tm_hour % 24, currTime->tm_min);
        }
        else if(strcmp(argv[1],"-d")==0){
            if(strcmp(argv[2],"tomorrow")==0){
                currTime = gmtime(&now);
                printf ("%d/%d/%d %2d:%02d\n", currTime->tm_mday+1, currTime->tm_mon+1, currTime->tm_year+1900,currTime->tm_hour % 24, currTime->tm_min);
            }
        }
    }
}