#include "cshell.h"

char* read_line()
{
	char* str=(char*)malloc(MAX * sizeof(char));
	fgets(str, 1024, stdin);
	return str;
}

int number_of_tokens(char* temp)
{
	int count=1;
	int position=0;
	for(int i=0;temp[i]!='\0';i++){
		if(temp[i]==32){
			count++;				
		}
	}
	return count;
}

char** tokenizer(char* str, int numberoftokens)
{
	char * temp;
	temp = strtok (str,"  \n");
	char** tokens=(char**)malloc((numberoftokens+1) * sizeof(char*));
	int i=0;
  while (temp != NULL)
  {
  	tokens[i]=(char*)malloc(MAX*sizeof(char*));
    tokens[i]=temp;
    temp = strtok (NULL, "  \n");
     i++;
  }
  tokens[numberoftokens]=(char*)malloc(MAX*sizeof(char*));
  tokens[numberoftokens]= NULL;

  return tokens;
}

char* parse_command(char* command)
{
	char* cmd;
	strcpy(cmd, "/bin/"  );
	strcat(cmd, command  );
	return cmd;
}