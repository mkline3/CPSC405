#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	char inputline[256]; //user input
	char *args[32];
	int i=0;
	int pid;
	
	while(strcmp(inputline, "exit") != 0){
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
			//	printf("\n In the child process about to run %s\n", *args);
				execvp(*args, args);
				if(strcmp(inputline,"exit")==0)
					printf("Goodbye\n");
				return(0);
			}
			else{
				wait(NULL);
			}
		}
		//printf("Input before while: %s\n", inputline);

		i++;
	}
	return(0);
}
