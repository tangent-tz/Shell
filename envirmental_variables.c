#include "cshell.h"


char* ascii_table()
{
	char* numercals=(char*)malloc(95* sizeof(char));
	for (int i=0; i<(127-32); i++){
		if(i>=16 && i<=25){
			char temp='X';
			numercals[i]=temp;
			continue;
		}

  		char temp = 32+i;
  		numercals[i]=temp;
	}
	return numercals;
}
int environment_search(int size, EnvVar* search, char* target){
	int index=-1;
	for(int i=0;i<size;i++){
		if(strcmp(search[i].name, target)==0){
			return i;
		}
	}
	return index;
}	