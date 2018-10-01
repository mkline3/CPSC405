#include "types.h"
#include "user.h"

int main(int argc, char *argv[]){
	int pid = fork();

	if(pid< 0)
		printf(0,"Fork failed");
	if(pid == 0){
		printf(1,"Random in child %d\n", srand());
		ps();
		exit();
	}
	if(pid> 0){
		printf(1,"Random in parent %d\n",  srand());
		ps();
		wait();
		exit();
	}
	exit();	
}

