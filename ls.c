#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
static void list_directory (char *dirname, int a, int l);

int main(int argc, char *argv[]) 
{
    printf("hello");
    int i;
    i = 1;
    if (argc == 1) {
        list_directory (".", 0, 0);
    }
    else if(argc>2){
        printf("ERROR: Wrong usage of LS");
    }
    else if(argc==2){
        if(argv[1][0]=='-'){
            int a = 0;
            int l = 0;
            char *p = (char*)(2);
            while(*p){
                if(*p=='a'){
                    a = 1;
                }
                else if(*p=='l'){
                    l = 1;
                }
                else{
                    printf("ERROR: Wont handle, Cant handle");
                    exit(0);
                }
                p++;
            }
            list_directory(".", a, l);
        }
    }
    return 0;
}

void list_directory(char *dirname, int a, int l)
{
    DIR *dir;
    struct dirent *ent;
    dir = opendir (dirname);
    if(!dir){
        fprintf(stderr, "Unable to open directory");
        exit(0);
    }
    if (dir != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if(!a && ent->d_name[0]=='.'){
                continue;
            }
            if (ent->d_type == DT_REG){
                printf("%s\n", ent->d_name);
            }
            else if(ent->d_type == DT_DIR){
                printf ("%s/\n", ent->d_name);
            }
            else if(ent->d_type == DT_LNK){
                printf ("%s@\n", ent->d_name);
            }        
            else{
                printf("%s*\n", ent->d_name);
            }    
            if(l)printf("\n");
        }
        if(!l)printf("\n");
        closedir (dir);
    } else {
        printf ("Cannot open directory %s\n", dirname);
        exit (0);
    }
}

