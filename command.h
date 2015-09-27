#ifndef COMMAND_H
#define COMMAND_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct com
{
	int num;
	char* theCommand;
};
typedef struct com Command;

Command * build_command_node(char *com, int numCom);
char * print_command_node(void *cn);
void release_command_node(void *data);

#endif // COMMAND_H
