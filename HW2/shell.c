#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
char word1(char *inputline);
char word2(char *inputline);
int count;
int main(){
	char inputline[256]; //user input
	char one[256];
	char two[256];
	char *args[32];
	int i=0;
	int pid;
	char error_message[30] = "An error has occurred\n";
	char cwd[256];
	
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
			
			//	execvp(*args, args);
				if(strcmp(inputline,"exit")==0){
					printf("Goodbye\n");
					exit(0);
				}

				else if(strcmp(inputline,"cd") == 0){
					chdir(getenv("HOME"));
					getcwd(cwd,sizeof(cwd));
					printf("Current working directory is: %s\n", cwd);
				}
				else if(strcmp(inputline, "pwd")==0){
					getcwd(cwd, sizeof(cwd));
					printf("Current working directory is: %s\n",cwd);
				}
				else if(execvp(*args, args) < 0){
					write(STDERR_FILENO, error_message, strlen(error_message));
				}
				else{
					execvp(*args, args);
				}
				return(0);
			}
			else{
				wait(NULL);
				if(strcmp(inputline,"cd")==0){
					chdir(getenv("HOME"));
					getcwd(cwd,sizeof(cwd));
				}
			}
		}
		//printf("Input before while: %s\n", inputline);
		
	
	}
	return(0);
}

char word1(char *inputline){
	count =0;
	int i = 0;
	int start;
	int end;
	for(count; count< strlen(buffer); count++){
		while(i ==0){
			ch = inputline[count];
			if//get white spaces
	}

}
