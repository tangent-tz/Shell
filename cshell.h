#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>	
#include <time.h>
#define MAX 1024
#define TRUE 1

typedef struct {
	char *name;
	char *value;
} EnvVar;

typedef struct {
	char *name;
	struct tm* time;
	int code;
} Command;


char* read_line();
void prompt();
int number_of_tokens(char* temp);
char** tokenizer(char* str, int numberoftokens);
char* parse_command(char* command);
int Built_in(char* cmd, char** args, EnvVar* temp, int size, Command* clock, int clock_size);
void freeblock(char** temp, int numberoftokens);
char* ascii_table();
int environment_search(int size, EnvVar* search, char* target);