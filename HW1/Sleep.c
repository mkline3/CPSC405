#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
int main(int argc, char *argv[]){
	pid_t pid = fork();
	srand(time(NULL));
	if(pid < 0){
		perror("Fork Failed");
	}
	if(pid == 0){
		printf("Hello\n");
		exit(0);
	}
	//wait(NULL);
	sleep(1);
	printf("Goodbye\n");
	
	
	return 0;
}
