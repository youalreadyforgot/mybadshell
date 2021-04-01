
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#define MAX_ARG_SIZE 256
int main()
{
    int buffersize_string = 100;	
    int numOfArgs = 10;
    int sizeOfArgs = 20;
    //Write prompt
    printf("login_prompt:");
    char *arg = malloc(sizeof(char) * buffersize_string);
    //Write a fgets that seperates them by spaces
    fgets(arg, MAX_ARG_SIZE, stdin);

    int argv = strlen(arg);
    //Test Code for printing number of args
    //printf("\n%d",argv);
   
    // Write a loop to serperate into different strings
    char *args[sizeOfArgs];
    
    for (int i=0;i<numOfArgs;i++)
    {
	args[i] = malloc(sizeof(char) * sizeOfArgs);
    }
    int cnt = 0;
    int j = 0;

    for(int i=0;i<=strlen(arg);i++)
        {
            if(arg[i] == '\n') {arg[i] = '\0';}
	        if(arg[i] == ' ' || arg[i] == '\0') 
	        {
		    args[cnt][j] = '\0';
		    cnt++;
		    j=0;

		}
	
	    else
		{
		    args[cnt][j] = arg[i];
		    j++;
		}
	}
    //Add a NULL to the end so exec can read
    args[cnt] = NULL;
    
    //char* test_arg[sizeOfArgs];
    //strcpy(test_arg[0], "-la\0");
    //strcpy(test_arg[1], "/home\0");
    //printf("%d", cnt);

    //More test code
    //for(int i=0;i<strlen(args[2]);i++)
    //{printf("[%c]_", arg[i]);}
    //for(int i=0;i<sizeof(args) 
    printf("[%s]", args[0]);
    printf("[%s]", args[1]);
    printf("[%s]", args[2]);
    printf("[%s]", args[3]);
    printf("[%s]", args[4]);

    //for(int i=0;i<cnt;i++)
    //{
	//printf("%s", args[i]);
    //}
    //Execute the command 
    execvp(args[0], args);
    //Catch any errors from the command stderr
    //perror("ERROR");
}
