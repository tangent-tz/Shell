#include "cshell.h"


int Built_in(char* cmd, char** args, EnvVar* temp, int size, Command* clock, int clock_size)
{
	if(!strcmp(cmd, "exit")){
		return -10;
	}

	else if(!strcmp(cmd, "log")){
		for(int i=0;i<clock_size;i++){
			printf("%s",asctime(clock[i].time));
			printf("%s\n",clock[i].name );
			printf("%d\n",clock[i].code );
		}
		return 0;
	}

	else if(!strcmp(cmd, "print")){
		for(int i=1;args[i]!=NULL; i++){
			int j=environment_search(size, temp, args[i]);
			if(j!=-1){
				printf("%s\n", temp[j].value);
				return 0;
			}
			printf("%s ", args[i] );
		}
		printf("\n");
		return 0;
	}

	else if(!strcmp(cmd, "theme")){
		char* temp[8]={"black", "red", "green", "yellow", "blue", "magenta", "cyan", "white" };

		if(args[1]==NULL){
			printf("%s\n", args[1] );
			return 0;
		}
		for(int i=0; i<8; i++){
			if(!strcmp(temp[i], args[1])){
				printf("\x1b[%dm", 30+i);
				break;
			}
		}
		return 0;
	}
	return -1;
}