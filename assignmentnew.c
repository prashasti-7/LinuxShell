#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/wait.h>
#include <pthread.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64
#define MAX_COMMANDS 11
#define MAX_PROCESSES 64

static char line[MAX_INPUT_SIZE];
static int makeToken[MAX_PROCESSES];
static char presentDir[MAX_TOKEN_SIZE];

static char **tokens;

void freemem() {
	int i;
	for(i = 0 ; tokens[i] != NULL ; i++)
		free(tokens[i]);
	free(tokens);
}

char pwdFunction(int tokensfound, int l, int p){
    if(tokensfound==1){
        char buff[FILENAME_MAX];
        getcwd(buff, FILENAME_MAX);
        printf("Current working directory is: %s", buff);
    }
    else if(tokensfound==2){
        if(l){
            char buff[FILENAME_MAX];
            getcwd(buff, FILENAME_MAX);
            printf("%s", buff); 
        }
        if(p){
            char buff[FILENAME_MAX];
            getenv(buff);
            printf("%s", buff);         
        }
    }
    else{
        printf("ERROR: Wrong use of PWD");
        exit(0);
    }
    printf("\n");
}

int execute(char** args, int tokensfound){
    if(strcmp(args[0], "cd")==0){
        char *h="/home";
        if(tokensfound==1){
            printf(" ");
        }
        else if(tokensfound>4){
            printf("ERROR: Wrong syntax for CD Command");
        }
        if(strcmp(args[1], "..")==0){
            chdir(args[1]);
            printf("Changing directories \n");
        }
        else if(args[1]==NULL){
            chdir(h);
        }
        else if(strcmp(args[1], "/usr")==0 || strcmp(args[1], "/tmp")==0 || strcmp(args[1], "/error")==0){
            if(chdir(args[1])!=0){
                printf("chdir() to %s failed", args[1]);
            }
        }
        else if((strcmp(args[1],"~")==0) || (strcmp(args[1], "~/")==0)){
            chdir(h);
        }
        else if(strcmp(args[1], "-L")==0){
            printf("dwdh");
        }
        else{
            if(chdir(args[1])==-1){
                printf("%s: No such directory\n", args[1]);
            }
        }
    }
    else if(strcmp(args[0], "exit")==0){
        printf("EXIT\n");
        exit(0);
    }
    else if(strcmp(args[0], "cat")==0){
        printf("%s", args[1]);
        char *argv[] = {"./cat", args[1], NULL};
        execvp(argv[0], argv);
        printf("Ending..");
    }
    else if(strcmp(args[0], "ls")==0){
        if(tokensfound==1){
            char *argv[] = {"./ls", args[1], NULL};
            execvp(argv[0], argv);
        }
        else if(tokensfound==2){
            char *argv[] = {"./ls", args[1], NULL};
            execvp(argv[0], argv);       
        }
        else if (tokensfound>2){
            printf("ERROR: Wrong syntax");
            exit(0);
        }
    }
    else if(strcmp(args[0], "rm")==0){
        char *argv[] = {"./rm", args[1], NULL};
        execvp(argv[0], argv);
    }
    else if(strcmp(args[0], "mkdir")==0){
        char *argv[] = {"./rm", args[1], NULL};
        execvp(argv[0], argv);
    }
    else if(strcmp(args[0], "date")==0){
        char *argv[] = {"./rm", args[1], NULL};
        execvp(argv[0], argv);
    }
    else if(strcmp(args[0], "pwd")==0){
        int l = 0;
        int p = 0;
        if(tokensfound==1){
            pwdFunction(tokensfound, l, p);
        }
        else if(tokensfound==2){
            if(strcmp(args[1], "-L")==0){
                l=1;
                p=0;
                pwdFunction(tokensfound, l, p);
            }
            else if(strcmp(args[1], "-P")==0){
                l=0;
                p=1;
                pwdFunction(tokensfound, l, p);
            }
        }
        else{
            printf("ERROR: Wrong use of PWD");
            exit(0);
        }
    }
    else if(strcmp(args[0], "echo")==0){
        char new_args[1024];
        int index = 0;
        int i = 1;
        while(args[i]){
            if(*args[i]=='\0'){
                break;
            } 
            int j=0;
            while(args[i][j]){
                new_args[index] = args[i][j];
                index++;
                j++;
            }  
            new_args[index]=' ';
            index++;
            i++;
        }
        new_args[index]='\0';
        printf("%s\n",new_args);
    }
    else if(strcmp(args[0], "&t")==0){
        char str[1028];
        if(strcmp(args[0],"date")==0){
            strcpy(str, "./date");
        }
        else if(strcmp(args[0],"mkdir")==0){
            strcpy(str,"./mkdir");
        }
        else if(strcmp(args[0], "rm")==0){
            strcpy(str, "./rm");
        }
        else if(strcmp(args[0], "cat")==0){
            strcpy(str, "./cat");
        }        
        else if(strcmp(args[0], "ls")==0){
            strcpy(str, "./ls");
        }
    }
    else{
        int err;
        pid_t pid = fork();
        if(fork()==0){
            int status_code = execvp(args[0], args);
            if(status_code==-1){
                printf("COMMAND FAILED\n");
                return 0;
            }
            else if(strcmp(args[0], "mkdir")==0){
                char *argv[] = { "./mkdir",args[1], 0};
                execvp(argv[0], argv);
            }
        }
        else if(pid==-1){
            printf("ERROR: FORKING FAILED\n");
            return 0;
        }
        else{
            waitpid(pid, &err, WUNTRACED);
        }
    }
    return 0;
}

char **tokenize(char *line, int* tokensfound) {
	char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
	char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
	int i, tokenIndex = 0, tokenNo = 0;

	for(i =0; i < strlen(line); i++){
        char readChar = line[i];

        if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
            token[tokenIndex] = '\0';
            if (tokenIndex != 0){
                tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
            strcpy(tokens[tokenNo++], token);
            tokenIndex = 0; 
            }
        }
        else
            token[tokenIndex++] = readChar;
	}
 
	free(token);
	tokens[tokenNo] = NULL ;
	*tokensfound = tokenNo;
	return tokens;
}

void main(void) {
	int i, tokensfound, status;
	while (1) {		
		char s[100];
        printf("PS %s>> ", getcwd(s, 100));
		bzero(line, MAX_INPUT_SIZE);
		fgets(line, MAX_INPUT_SIZE, stdin);
		line[strlen(line)] = '\n'; 					//terminate with new line
		tokens = tokenize(line, &tokensfound);
		
		execute(tokens, tokensfound);

		for(i = 0 ; i < MAX_PROCESSES ; i++) {
			if(makeToken[i] != -1)
				if(waitpid(makeToken[i], &status, WUNTRACED) == makeToken[i])
					makeToken[i] = -1;
		}
		freemem();
	}
}