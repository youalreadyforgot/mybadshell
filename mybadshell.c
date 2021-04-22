
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#define MAX_ARG_SIZE 20
#define NUM_ARGS 10
#define HOST_NAME_MAX 50
#define USER_NAME_MAX 50
#define BUFFER_SIZE 100
int main()
{
        while(1){
	    //Write prompt
	    printf("Welcome to my bad shell\n");
	    char* hostname = malloc(sizeof(char) * HOST_NAME_MAX + 1);
            char* user = malloc(sizeof(char) * USER_NAME_MAX);
            strcpy(user, getenv("USER"));
            gethostname(hostname, HOST_NAME_MAX + 1);
            printf("%s@%s>", user, hostname);
            char *arg = malloc(sizeof(char) * BUFFER_SIZE);
            //Write a fgets that seperates them by spaces
            fgets(arg, MAX_ARG_SIZE, stdin);

            int argv = strlen(arg);
            //Test Code for printing number of args
            //printf("\n%d",argv);
   
            // Write a loop to serperate into different strings
            char *args[MAX_ARG_SIZE];
    
            for (int i=0;i<NUM_ARGS;i++)
            {
	        args[i] = malloc(sizeof(char) * MAX_ARG_SIZE);
            }
            int cnt = 0;
            int j = 0;

            for(int i=0;i<=strlen(arg);i++)
            {
                if(arg[i] == '\n') {
		    arg[i] = '\0';}
	        if(arg[i] == ' ' || arg[i] == '\0'){
		    args[cnt][j] = '\0';
		    cnt++;
		    j=0;
		}
	
	    else{
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
	   pid_t pid, wpid;
	   int status;
	   
	   pid = fork();
	   if(pid == 0){
	   	//Child process
		// If exec returns the there is an error
		if(execvp(args[0], args) == -1) {
		    perror("mybadshell");
		}
		exit(EXIT_FAILURE);   
	   }
		
	   else if(pid < 0) {
               //Error Forking
	       perror("mybadshell");
	   }
           else{
               //Parent Process
	       do{
	           wpid = waitpid(pid, &status, WUNTRACED);
	       } while(!WIFEXITED(status) && !WIFSIGNALED(status));
	   }
           
    	  
          //Catch any errors from the command stderr
          //perror("ERROR");
          //Free up some memory
          free hostname, user, arg;
	  for (int i=0;i<NUM_ARGS;i++)
            {
	        free args[i];
            }
	}
	
	printf("\nEXIT");
	return 1;
}
