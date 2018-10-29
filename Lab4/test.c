#include "types.h"
#include "user.h"

int main(int argc, char *argv[]){
	int pid = fork();

	if(pid< 0)
		printf(0,"Fork failed\n");
	if(pid == 0){
		printf(0,"Child process\n");

		getpininfo();
		uppriority();
		getpininfo();
		exit();
	}
	if(pid> 0){
		printf(0,"Parent process %d\n");
		getpininfo();
		wait();
		exit();
	}
	exit();	
}