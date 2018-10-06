#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc,char* argv[] ){
	char inputline[256]; //user input
	char *args[32];
	int i=0;
	int pid;
	char error_message[30] = "An error has occurred\n";
	char cwd[256];
	if(argc >1){
		printf("\tBatch Mode:\n");
		FILE* file = fopen(argv[1], "r");
		if(file == NULL){
			printf("Error with file\n");
		}
		else{
			while(strcmp(inputline, "exit") != 0){
				printf("mysh> ");
				fgets(inputline, sizeof(inputline), file);
				printf("%s", inputline);
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
							printf("%s\n", cwd);
						}
						else if(strcmp(inputline, "pwd")==0){
							getcwd(cwd, sizeof(cwd));
							printf( "%s\n",cwd);
						}
						else if(strstr(inputline,"cd") != NULL){
							char *t;
							int i;
							t = strtok(inputline, " ");
							for (i=0; t != NULL; i++) {
								if(i == 1){
									if(chdir(t) == 0){
										getcwd(cwd,sizeof(cwd));
										printf("%s\n",cwd);
									}
									else{
										write(STDERR_FILENO, error_message, strlen(error_message));
									}
								}
								t = strtok(NULL, " ");
							}


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
						else if(strstr(inputline,"cd") != NULL){
							char *t;
							int i;
							t = strtok(inputline, " ");
							for (i=0; t != NULL; i++) {
								if(i == 1){
									if(chdir(t) == 0){
										getcwd(cwd,sizeof(cwd));
									}
									else{
									//	write(STDERR_FILENO, error_message, strlen(error_message));	
									}
								}
								t = strtok(NULL, " ");
							}


						}
					}
				}
			}		//printf("Input before while: %s\n", inputline);
		}
		fclose(file);
	}					
	else{
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
						printf("%s\n", cwd);
					}
					else if(strcmp(inputline, "pwd")==0){
						getcwd(cwd, sizeof(cwd));
						printf( "%s\n",cwd);
					}
					else if(strstr(inputline,"cd") != NULL){
						char *t;
						int i;
						t = strtok(inputline, " ");
						for (i=0; t != NULL; i++) {
							if(i == 1){
								if(chdir(t) == 0){
									getcwd(cwd,sizeof(cwd));
									printf("%s\n",cwd);
								}
								else{
									write(STDERR_FILENO, error_message, strlen(error_message));
								}
							}
							t = strtok(NULL, " ");
						}


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
					else if(strstr(inputline,"cd") != NULL){
						char *t;
						int i;
						t = strtok(inputline, " ");
						for (i=0; t != NULL; i++) {
							if(i == 1){
								if(chdir(t) == 0){
									getcwd(cwd,sizeof(cwd));
								}
								else{
								//	write(STDERR_FILENO, error_message, strlen(error_message));	
								}
							}
							t = strtok(NULL, " ");
						}


					}
				}
			}
			//printf("Input before while: %s\n", inputline);
		}	

	}
	return(0);
}


