#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<fcntl.h>
#include <string.h>

#define MAX_LINE 2048

int main(int argc,char*argv[])
{
    int argument=-1;
    char buff[2048];
    int count;
    if(argc>3){
        printf("ERROR: Wrong syntax for CAT");
        exit(1);
    }
    else if(argc==2){
        argument=open(argv[1], O_RDONLY);
        while((count=read(argument,buff,2048))>0){
            printf("%s",buff);
        }
    }
    else if (argc==3)
    {
        char line[500];
        int counter = 1;
        char* dollar = "$";
        if(strcmp(argv[1], "-n")==0){
            FILE * fp = fopen(argv[2],"r");
            argument=open(argv[2], O_RDONLY);
            while(fgets(line, sizeof(line), fp)){
                printf("%d", counter);
                printf("%s", line);
                counter++;
            }
        }
        else if(strcmp(argv[1], ">")==0){
            FILE * newFile = fopen(argv[2], "w");
            fclose(newFile);
            printf("File created successfully");
        }
        else{
            printf("Cant handle\n");
        }
    }
    
    if(argument==-1){
        printf("cannot open file\n");
        exit(1);
    }

    return 0;
}