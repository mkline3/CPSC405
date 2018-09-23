#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
int main(int argc, char *argv[]){
	pid_t pid = fork();
//	srand(time(NULL));
	char *args[] = {"/bin/ls", NULL};
	if(pid < 0){
		perror("Fork Failed");
	}
	if(pid == 0){
		execvp("/bin/ls", args);
	//	execvP("/bin/ls", args);	
		exit(0);
	}
	//wait(NULL);
//	sleep(1);
	execvp("/bin/ls", args);
//	execvP("/bin/ls", args);	
	
	return 0;
}
