#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
int main(int argc, char *argv[]){
//	int x = 100;
	char buffer[100];
	int input_fd, output_fd;    /* Input and output file descriptors */
    	ssize_t ret_in, ret_out;
	int file = open("testfile.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    	if(file < 0)
        	return 1;
	pid_t pid = fork();
	srand(time(NULL));
	if(pid < 0){
		perror("Fork Failed");
	}
	if(pid == 0){
		ret_out = write (file, "Child\n",5);
		exit(0);
	}
	//wait(NULL);
	ret_out = write (file, "Parent\n",6);
	
	
	return 0;
}
