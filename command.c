#include "command.h"


Command * build_command_node(char *com, int numCom)
{
	Command *cn = malloc(sizeof(Command));
	cn->theCommand = (char *)calloc(strlen(com)+1, sizeof(char));
	strcpy(cn->theCommand, com);
	cn->num = numCom;
	
	return cn;
}

char * print_command_node(void *cn)
{
	char *command_str;
	Command *node = (Command *)cn;
	
	char number[10];
	sprintf(number, "%d ", node->num);
	
	size_t nlen = strlen(number); 
	size_t clen = strlen(node->theCommand);
	command_str = (char *)calloc(nlen + clen + 2, sizeof(char));
	
	strcat(command_str, number);
	strcat(command_str, node->theCommand);
	strcat(command_str, "\n");
	
	return command_str;
}

void release_command_node(void *data)
{
	Command *node = (Command *)data;
	free(node->theCommand);
}
