#include<stdio.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>

int main(int argc, char* argv[])
{   
    int make;
    if(argc==2){
        if(mkdir(argv[1],0777)==-1){
            printf("error");
            if(errno==EEXIST){
                printf("Already exists");
            }
            return 0;
        }
        printf("Made new directory");
        return 1;
    }
    if(argc==3){
        if(strcmp(argv[1],"-v")==0){
            if(mkdir(argv[2],0777)==-1){
                printf("error");
                if(errno==EEXIST){
                    printf("Already exists");
                }
                return 0;
            }
            printf("mkdir: created directory '%s'\n", argv[2]);
            return 1;
        }
        else{
            printf("Cant handle\n");
        }
    }
}