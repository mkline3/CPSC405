#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	char inputline[256]; //user input
	char *args[32];
	int i=0;
	int pid;
	while(*args != "exit\0"){
		printf("mysh> ");
		fgets(inputline, sizeof(inputline), stdin);
		inputline[sizeof(inputline)-1] ='\0';
		
		int j=0;
		while(inputline[j] !='\n'){
			j++;
		}
		inputline[j] = '\0';
		*args = inputline;

		args[1] = NULL;

		pid = fork();
		if(pid < 0){
			printf("\nThe fork Failed\n");
			return 0;
		}
		else{
			if(pid == 0){
				printf("\n In the child process about to run %s\n", *args);
				execvp(*args, args);
				if(*args == "exit")
					printf("Goodbye\n");
				return(0);
			}
			else{
				wait(NULL);
			}
		}
		//printf("Args before while: %s\n", *args);
		i++;
	}
	return(0);
}
