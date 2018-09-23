#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
int x = 0;

void numCheck(char *name){
	printf("X came in as %d durring %s process\n", x, name);
	sleep(rand() %4);
	x = rand() % 10;
	printf("rand num for %s : %d\n", name, x);
}

int main(int argc, char *argv[]){
//	int x = 100;
	printf("X is: %d at start of program\n", x);
	pid_t pid = fork();
	srand(time(NULL));
	if(pid < 0){
		perror("Fork Failed");
	}
	if(pid == 0){
		numCheck("child");
	}
	
	numCheck("parent");
	
	printf("X is: %d at end of program\n", x);
	return 0;
}
