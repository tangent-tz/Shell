#include "cshell.h"


void prompt()
{
	system("clear");
	printf("###########################_________###########################\n");
	printf("##************************|  CSHELL  |***********************##\n");
	printf("###########################~~~~~~~~~###########################\n\n");
}


int main (int argc, char*argv[]){

//Variables
	int child_status;
	char* str;
	int status=1;
	char* ascii= ascii_table();
	char** test;
	int numberoftokens;
	char* command;
	char cmd[MAX];
	EnvVar *environment_vals=(EnvVar*)malloc(MAX*sizeof(EnvVar));
	int EnvVar_count=0;
	ssize_t totalRead= 0;
	Command *log_list=(Command*)malloc(MAX*sizeof(Command));
	int log_count=0;
	time_t clock;
	



	prompt();
//Main loop
	while(1){
	
		log_list[log_count].name=(char*)malloc(sizeof(char));
		printf("cshell~$ ");
		str=read_line();
		numberoftokens=number_of_tokens(str);
		test=tokenizer(str, number_of_tokens(str));
		strcpy(log_list[log_count].name, test[0]);
		printf("%d\n", log_count );
		time(&clock);
		log_list[log_count].time=localtime(&clock);

//For Environmental variables
		if(!strncmp(test[0], "$", 1)){
			char* pos=strchr(test[0], '=');
			if(pos==NULL){
				errno=EACCES;
				perror("Error");
				log_list[log_count].code=-1;
				continue;
			}
			int positon=pos-test[0];
			char target[MAX];
			strncpy(target, test[0], positon);
			target[positon]='\0';
			printf("%d\n", EnvVar_count );
			int result_search=environment_search(EnvVar_count, environment_vals,target);
			printf("%d\n", result_search );
			if(result_search!=-1){
				strncpy(environment_vals[result_search].value, test[0]+positon+1, (int)strlen(test[0])-positon);
				continue;
			}


			if(strpbrk(test[0]+positon+1, ascii)==NULL){
				environment_vals[EnvVar_count].name=(char*)malloc(sizeof(char));
				environment_vals[EnvVar_count].value=(char*)malloc(sizeof(char));
				strncpy(environment_vals[EnvVar_count].name, test[0], positon);
				environment_vals[EnvVar_count].name[positon]='\0';
				strncpy(environment_vals[EnvVar_count].value, test[0]+positon+1, (int)strlen(test[0])-positon);
				EnvVar_count++;
			}
			goto misc;
		}

//Built in Commands
		else if((!strcmp(test[0], "exit") || !strcmp(test[0], "log") || !strcmp(test[0], "print") || !strcmp(test[0], "theme"))){
			status=Built_in(test[0], test, environment_vals, EnvVar_count, log_list, log_count);
			if(status==-10){
				log_list[log_count].code=0;
				log_count++;
				goto Exit_routine;
			}
			log_list[log_count].code=status;
			goto misc;	
		}


		else{
			command=test[0];
			strcpy(cmd, parse_command(command));
			free(test[0]);
			test[0]=cmd;

			int fds[2];
			if(pipe(fds)==-1){
				perror("error: ");
				return -1;
			}

			int fc=fork();
			if(fc<0){
				exit(1);
			}

			else if(fc>0){
				char buffer[MAX]={'\0'};
				while (1) {
					totalRead = read(fds[0], buffer, sizeof(buffer));
					if (totalRead < 0) {
						if (errno == EINTR){
							continue;
						}
						else {
							perror("read");
							break;
						}
					}
					else if (totalRead == 0){
						break;
					}
					else {
						printf("%s\n", buffer);
						break;
					}
				}
				close(fds[0]);
				wait(&child_status);
				if(child_status!=0)
					log_list[log_count].code=-1;
				goto misc;
			}

			else{
				close(fds[0]);
				dup2(fds[1], STDOUT_FILENO);
				dup2(fds[1], STDERR_FILENO);
				close(fds[1]);
				close(fds[0]);
				execve(cmd, test, NULL );
				perror("Error");
				exit(1);
			}
		}
		misc:
		log_count++;

	}


	Exit_routine:
		printf("Shell closed\n");
		for (int i=0; i<log_count;i++)
				free(log_list[i].name);
		for (int i=0; i<EnvVar_count;i++){
				free(environment_vals[i].name);
				free(environment_vals[i].value);
			}
		free(test);
		free(environment_vals);
		free(log_list);
		free(ascii);
		free(str);
		free(command);
		return 0;
}