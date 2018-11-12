#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc,char* argv[] ){
	char inputline[256]; //user input
	char inputline2[256];
	char *args[32];
	char *stuff[32];
	char str[256];
	char *s[32];
	int i=0;
	int pid;
	int pid2;
	int status;

	char error_message[30] = "An error has occurred\n";
	char cwd[256];
	
    
	if(argc >1){
		printf("\tBatch Mode:\n");
		FILE* file = fopen(argv[1], "r");
		if(file == NULL){
			printf("Error with file\n");
		}
		else{
			while(strstr(inputline, "exit") == NULL){
				printf("mysh> ");
				fgets(inputline, sizeof(inputline), file);
				printf("%s", inputline);
				inputline[sizeof(inputline)-1] ='\0';
				int j=0;
				while(inputline[j] !='\n'){
					j++;
				}
			
				inputline[j] = '\0';
				char holder[256];
				char *token;
			
			 /* get the first token */
   				token = strtok(inputline, " ");
   			//printf("\n %s\n", inputline);
   			/* walk through other tokens */
  			 	while( token != NULL ) {
  			 	
      				strcat(holder, token);
      			
      				strcat(holder, " ");
      			
    
      				token = strtok(NULL, " ");
   				}
   			

			
		    	*args = inputline;
				char *input;
			
            	input = strtok(inputline, " ");
            
				strcpy(inputline2, holder);
				args[1] = NULL;
				*args =input;
			//strcpy(inputline, holder);
				pid = fork();
				if(pid < 0){
					printf("\nThe fork Failed\n");
					return 0;
				}
				else{
					if(pid == 0){
					//	printf("\n In the child process about to run %s\n", *args);

					//	execvp(*args, args);
					//printf("%s\n",inputline);
						if(strcmp(input,"exit")==0){
							printf("Goodbye\n");
						
						//shell = 0;
						
							exit(0);
						}
					/*else if(strcmp(inputline,"cd") == 0){
						chdir(getenv("HOME"));
						getcwd(cwd,sizeof(cwd));
						printf("%s\n", cwd);
					}*/
						else if(strcmp(input, "pwd")==0){
							getcwd(cwd, sizeof(cwd));
							printf( "%s\n",cwd);
						}
						else if(strcmp(input, "wait") == 0){
								
						

							
						}
						else if(strcmp(input, "hash")==0){

								int process = execvp("md5sum", args);
								if(process == -1){
								//printf("HEY\n");
									write(STDERR_FILENO, error_message, strlen(error_message));
								}
								
						}
					
			
						else if(strstr(inputline2,"cd") != NULL){

							char *t;
							int i;
							t = strtok(inputline2, " ");
							for (i=0; i < 2; i++) {
						  
								if((i ==1) && (t == NULL)){
									chdir(getenv("HOME"));
									getcwd(cwd,sizeof(cwd));
									printf("%s\n", cwd);
								
						
								}
								else{
									if(i == 1){
									
										if(chdir(t) == 0){
											getcwd(cwd,sizeof(cwd));
											printf("%s\n",cwd);
										}
										else{
											write(STDERR_FILENO, error_message, strlen(error_message));
										}
									}
									
								}
								t = strtok(NULL, " ");
						  
							}


						}
						else if(strstr(inputline2,">")!=NULL){
							//printf("Redirection\n");
							int newfd;
							int copy = dup(1);
							char h[256];
							char *t;
							i = 0;
				 			/* get the first token */
	   						t = strtok(inputline2, " ");
	   						//printf("\n %s\n", inputline);
	   						/* walk through other tokens */
	  						 while( t != NULL ) {
	  			 				stuff[i] = t;    
	      						t = strtok(NULL, " ");
	      						i = i + 1;
	   						}
	   						stuff[i] = NULL;
	   						if(stuff[2] == NULL)
	   							write(STDERR_FILENO, error_message, strlen(error_message));
	   						else if((newfd = open(stuff[2], O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0)
	   							write(STDERR_FILENO, error_message, strlen(error_message));
	   						else{
	   							printf("Writing %s to file: %s \n", stuff[0], stuff[2]);
	   							dup2(newfd, 1);
	   							if(execvp(*args, args) >= 0)
	   								execvp(*args, args);

	   							else
	   								write(STDERR_FILENO, error_message, strlen(error_message));
	   							dup2(copy, 1);
	   						}

						}
						else if(strstr(inputline2,"&")){
							//printf("In here\n");
							
							//printf("%s\n",str[i]);
							
						}
						else if(strstr(inputline2,".py") != NULL){

							args[1] = args[0];
							args[0] = "python";
							args[2] = NULL;
							if(execvp(*args, args) >= 0){
								execvp(*args, args);	
							}
							else
								write(STDERR_FILENO, error_message, strlen(error_message));
							
						}
						else if(strstr(inputline2,".pl") != NULL){
							args[1] = args[0];
							args[0] = "perl";
							args[2] = NULL;
							if(execvp(*args, args) >= 0)
								execvp(*args, args);
							else
								write(STDERR_FILENO, error_message, strlen(error_message));
							
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

						
						if(strstr(inputline2,"cd") != NULL){
							char *t;
							int i;
							
							t = strtok(inputline2, " ");
							for (i=0; i < 2; i++) {
								//printf("In parent %s\n", t);
								if(i == 1 && t == NULL){
	                                chdir(getenv("HOME"));
	                                getcwd(cwd,sizeof(cwd));

								}
								else{
									if(i ==1){
										if(chdir(t) == 0){
											getcwd(cwd,sizeof(cwd));
											//printf("parent cwd %s\n", cwd);
										}
										
									}
								}
								t = strtok(NULL, " ");
							}


						}

					}
				}
				//printf("holder: %s\n", holder);
				//strcpy(inputline, holder);
				strcpy(holder, "");
				
				//strcpy(inputline, input);
				
			}	
				
				
					//printf("Input before while: %s\n", inputline);
		}
		fclose(file);
	}					
	else{
		while(strstr(inputline,"exit")==NULL){
			printf("mysh> ");
			fgets(inputline, sizeof(inputline), stdin);

			inputline[sizeof(inputline)-1] ='\0';
			int j=0;
			while(inputline[j] !='\n'){
				j++;
			}
			
			inputline[j] = '\0';
			char holder[256];
			char *token;
			
			 /* get the first token */
   			token = strtok(inputline, " ");
   			//printf("\n %s\n", inputline);
   			/* walk through other tokens */
  			 while( token != NULL ) {
  			 	
      			strcat(holder, token);
      			
      			strcat(holder, " ");
      			
    
      			token = strtok(NULL, " ");
   			}
   			

			
		    *args = inputline;
			char *input;
			
            input = strtok(inputline, " ");
            
			strcpy(inputline2, holder);
			args[1] = NULL;
			*args =input;
			//strcpy(inputline, holder);
			pid = fork();
			if(pid < 0){
				printf("\nThe fork Failed\n");
				return 0;
			}
			else{
				if(pid == 0){
					//	printf("\n In the child process about to run %s\n", *args);

					//	execvp(*args, args);
					//printf("%s\n",inputline);
					if(strcmp(input,"exit")==0){
						printf("Goodbye\n");
						
						//shell = 0;
						
						exit(0);
					}
					/*else if(strcmp(inputline,"cd") == 0){
						chdir(getenv("HOME"));
						getcwd(cwd,sizeof(cwd));
						printf("%s\n", cwd);
					}*/
					else if(strcmp(input, "pwd")==0){
						getcwd(cwd, sizeof(cwd));
						printf( "%s\n",cwd);
					}
					else if(strcmp(input, "wait") == 0){
							//printf("%s\n",s);
					}
					else if(strcmp(input, "hash")==0){

							int process = execvp("md5sum", args);
							if(process == -1){
								//printf("HEY\n");
								write(STDERR_FILENO, error_message, strlen(error_message));
							}
								
					}
					
			
					else if(strstr(inputline2,"cd") != NULL){

						char *t;
						int i;
						t = strtok(inputline2, " ");
						for (i=0; i < 2; i++) {
						  
							if((i ==1) && (t == NULL)){
								chdir(getenv("HOME"));
								getcwd(cwd,sizeof(cwd));
								printf("%s\n", cwd);
								
						
							}
							else{
								if(i == 1){
									
									if(chdir(t) == 0){
										getcwd(cwd,sizeof(cwd));
										printf("%s\n",cwd);
									}
									else{
										write(STDERR_FILENO, error_message, strlen(error_message));
									}
								}
								
							}
							t = strtok(NULL, " ");
						  
						}


					}
					else if(strstr(inputline2,">")!=NULL){
						//printf("Redirection\n");
						int newfd;
						int copy = dup(1);
						char h[256];
						char *t;
						i = 0;
			 			/* get the first token */
   						t = strtok(inputline2, " ");
   						//printf("\n %s\n", inputline);
   						/* walk through other tokens */
  						 while( t != NULL ) {
  			 				stuff[i] = t;    
      						t = strtok(NULL, " ");
      						i = i + 1;
   						}
   						stuff[i] = NULL;
   						if(stuff[2] == NULL)
   							write(STDERR_FILENO, error_message, strlen(error_message));
   						else if((newfd = open(stuff[2], O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0)
   							write(STDERR_FILENO, error_message, strlen(error_message));
   						else{
   							printf("Writing %s to file: %s \n", stuff[0], stuff[2]);
   							dup2(newfd, 1);
   							if(execvp(*args, args) >= 0)
   								execvp(*args, args);

   							else
   								write(STDERR_FILENO, error_message, strlen(error_message));
   							dup2(copy, 1);
   						}

					}
					else if(strstr(inputline2,"&")){
						//printf("In here\n");
						strcat(s, input);
						strcat(s, " ");	
						//printf("%s\n",str);

						
					}
					else if(strstr(inputline2,".py") != NULL){

						args[1] = args[0];
						args[0] = "python";
						args[2] = NULL;
						if(execvp(*args, args) >= 0){
							execvp(*args, args);	
						}
						else
							write(STDERR_FILENO, error_message, strlen(error_message));
						
					}
					else if(strstr(inputline2,".pl") != NULL){
						args[1] = args[0];
						args[0] = "perl";
						args[2] = NULL;
						if(execvp(*args, args) >= 0)
							execvp(*args, args);
						else
							write(STDERR_FILENO, error_message, strlen(error_message));
						
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

					
					if(strstr(inputline2,"cd") != NULL){
						char *t;
						int i;
						
						t = strtok(inputline2, " ");
						for (i=0; i < 2; i++) {
							//printf("In parent %s\n", t);
							if(i == 1 && t == NULL){
                                chdir(getenv("HOME"));
                                getcwd(cwd,sizeof(cwd));

							}
							else{
								if(i ==1){
									if(chdir(t) == 0){
										getcwd(cwd,sizeof(cwd));
										//printf("parent cwd %s\n", cwd);
									}
									
								}
							}
							t = strtok(NULL, " ");
						}


					}

				}
			}
			//printf("holder: %s\n", holder);
			//strcpy(inputline, holder);
			strcpy(holder, "");
			
			//strcpy(inputline, input);
			
		}	

	}
	return(0);
}


