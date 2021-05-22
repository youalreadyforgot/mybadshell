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


char **parse_command(char *arg, char **args){
	int argv = strlen(arg);
   
    
    for (int i=0;i<NUM_ARGS;i++)
    {
	    args[i] = malloc(sizeof(char) * MAX_ARG_SIZE);
    }
    int cnt = 0;
    int j = 0;

    for(int i=0;i<=strlen(arg);i++)
    {
        if(arg[i] == '\n') {
		arg[i] = '\0';
		}

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
	return args;

}

int mybadshell_start(char **args){
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
	       } 
		   while(!WIFEXITED(status) && !WIFSIGNALED(status));
	   }

	   return 1;
}

//Some shell built ins

//String array with builts ins
char* built_in[] = {
	"cd",
	"help",
	"exit"
};



int sh_num_built_ins(){
	return sizeof(built_in) / sizeof(char *);
}

int sh_cd(char **args){
	if(args[1] == NULL){
		fprintf(stderr, "mybadshell: expected argument to \"cd\"\n");
	}
	else{
		if(chdir(args[1]) != 0){
			perror("mybadshell");
		}
	}
	return 1;
}

int sh_help(char **args){
	int i;
	printf("This is a shell bro you type commands in.\n");
	printf("Here are the built ins\n");

	for(i = 0; i<sh_num_built_ins(); i++){
		printf(" %s\n", built_in[i]);
	}
	printf("Use man if you didn't find what you are looking for.\n");
	return 1;
}

int sh_exit(char **args){
	return 0;
}

//Not sure what this does yet something to do with correlating the functions to each other
int (*builtin_func[]) (char **) = {
  &sh_cd,
  &sh_help,
  &sh_exit
};


int sh_execute(char **args){
	int i;
	if(args[0] == NULL){
		//Literally the idiot didn't type anything
		return 0;
	}

	for(i = 0; i<sh_num_built_ins(); i++){
		if(strcmp(args[0], built_in[i]) == 0){
			return (*builtin_func[i])(args);
		}
	}

	return mybadshell_start(args);
}


int main()
{
	//Write prompt
	printf("Welcome to my bad shell\n");
	while(1){
	    
		//Creating hostname and user strings
	    char* hostname = malloc(sizeof(char) * HOST_NAME_MAX + 1);
        char* user = malloc(sizeof(char) * USER_NAME_MAX);
        strcpy(user, getenv("USER"));
        gethostname(hostname, HOST_NAME_MAX + 1);
        printf("%s@%s>", user, hostname);
        
		//Take in unparsed command
		char *arg = malloc(sizeof(char) * BUFFER_SIZE);
        
		//Write a fgets that seperates them by spaces
        fgets(arg, MAX_ARG_SIZE, stdin);

    
   
        // Write a loop to serperate into different strings
        char *args[MAX_ARG_SIZE];
    
		//Parse the args	
        parse_command(arg, args);

	    //Check for exit in args
	    if(strcmp(args[0], "exit") == 0){
	        return 0;
	    }
		
		//Execute the command 

		sh_execute(args);

    	//Catch any errors from the command stderr
    	//perror("ERROR");
    	//Free up some memory
    	free(hostname);
		free(user);
		free(arg);
		for (int i=0;i<NUM_ARGS;i++)
    		{
	    		free(args[i]);
        	}
	//End of loop
	}
	return 0;
}
