#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
int main(int argc, char *argv[]){
	printf("Start of parent process\n");
	pid_t pid = fork();
//	srand(time(NULL));
	char *args[] = {"/bin/ls", NULL};
	if(pid < 0){
		perror("Fork Failed");
	}
	if(pid == 0){
		wait(NULL);
		printf("In child Process\n");	
		exit(0);
	}
//	wait(NULL);
	printf("In parent process\n");
	return 0;
}
