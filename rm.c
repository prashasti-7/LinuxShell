#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main(int argc, char* argv[]){
    if ((argc<2))
    {
        printf("ERROR:Wrong use of RM");
    }
    else if(argc==2){
        int flag;
        flag = remove(argv[1]);
        if(flag==0){
            printf("Removed File Successfully");
        }
        else{    
            printf("File not found");
            exit(0);
        }  
    }
    else if(argc==3){
        if(strcmp(argv[1],"-i")==0){
            int file;
            char* confirm;
            printf("Press y for confirmation and n to decline\n");
            scanf("%s\n", &*confirm);
            if(confirm="y"){
                file = remove(argv[2]);
                if(file==0){
                    printf("Removed Successfully\n");
                }
            }
        }
        else{
            printf("Cant handle\n");
        }
    }
}