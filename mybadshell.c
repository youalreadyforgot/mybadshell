
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#define MAX_ARG_SIZE 256
#define HOST_NAME_MAX 1000
#define USER_NAME_MAX 1000
int main()
{
    int buffersize_string = 100;	
    int numOfArgs = 10;
    int sizeOfArgs = 20;
    //Write prompt
    char* hostname = malloc(sizeof(char) * HOST_NAME_MAX + 1);
    char* user = malloc(sizeof(char) * USER_NAME_MAX);
    strcpy(user, getenv("USER"));
    gethostname(hostname, HOST_NAME_MAX + 1);
    printf("%s@%s:", user, hostname);
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
    


    //for(int i=0;i<cnt;i++)
    //{
	//printf("%s", args[i]);
    //}
    //Execute the command 
    bool cont = true;
    while(cont == true)
    {
        execvp(args[0], args);
    }
    //Catch any errors from the command stderr
    //perror("ERROR");
}
