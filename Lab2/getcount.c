#include "types.h"
#include "user.h"
#include"syscall.h"

int main(int argc, char *argv[]){
	int x;
	x = getcount();
	printf(1,"%d total system calls\n", x);
	exit();
}
