#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utility.h"
#include "linkedList.h"

#define MAX 100

int splitInput(char* s, char ***args);
void forkIt(char ** argv, int argc, LinkedList * theList);
int makeargs(char *s, char *** argv);
commands *createCommand(char *s, int numCom);
Node *createNode(commands *com);
void clean(int argc, char **argv);

int main()
{
	char **args = NULL, **argv = NULL, s[MAX];
	int i, argsc, numCommand = 1;
	LinkedList *list = linkedList();
	commands *command = NULL;
	Node *nn = NULL;

	printf("?: ");
	fgets(s, MAX, stdin);

 	while(strcmp(s, "exit\n") != 0)
  	{
		if (strcmp(s, "print\n") == 0)
			printList(list);

		if (!isValidInput(s))
			continue;

		argsc = splitInput(s, &args, numCommand);


		printf("?: ");
		fgets(s, MAX, stdin);

	}// end while
}// end main

int splitInput(char* s, char ***args)
{
	/*
	if ( s == NULL || s[0] == '\0' || s[0] == '\n' )
		return 0;
	*/
	char *ns = (char *)calloc(strlen(s)+1, sizeof(char));
	strcpy(ns, sizeof(char))
	char *comm, delim = '|';
	int i, numCom, count, saveptr, numToken = 0;

	numCom = getNumCommand(s);

	comm = strtok_r(ns, delim, &saveptr);

	(*args) = (char **)calloc(numCom+1, sizeof(char*));
	(*args)[0] = (char *)calloc(strlen(comm)+1, sizeof(char));
	strcpy((*args)[0], comm);

	for ( i = 1; i < numCom; i++)
	{
		comm = strtok_r(NULL, delim, &saveptr));
		(*args)[0] = (char *)calloc(strlen(comm)+1, sizeof(char));
		strcpy((*args)[i], comm);
	}

	return numCom;
}

void forkIt(char ** argv, int argc, LinkedList * theList)
{
	pid_t id = fork();
	int status;

	if ( id != 0 )
	{
		waitpid(-1, &status, 0);
	}
	else if ( id == 0 )
	{
		if ( execvp(argv[0], argv) == -1 )
		{
			clean(argc, argv);
			clearList(theList);
  			argv = NULL;
  			exit(-1);
		}
	}
}// end forkIt

int makeargs(char *s, char *** argv)
{
	if ( s == NULL || s[0] == '\0' || s[0] == '\n' )
		return -1;


	int numToken = 1, i;
	char *ptr = s;
	char *saveptr;
	char *token;
	const char *delim = " ";

	while ( (ptr = strchr(ptr, ' ')) != NULL )
	{
		numToken++;
		ptr++;
	}

	(* argv) = (char **)calloc(numToken+1, sizeof(char*));

	token = strtok_r(s, delim, &saveptr);


	(*argv)[0] = (char *)calloc(strlen(token)+1, sizeof(char));
	strcpy((*argv)[0], token);

	for( i = 1; i < numToken; i++)
	{
		token = strtok_r(NULL, delim, &saveptr);
		(*argv)[i] = (char *)calloc(strlen(token)+1, sizeof(char));
		strcpy((*argv)[i], token);
	}

	(*argv)[numToken] = NULL;

   return numToken;

}// end makeArgs

commands *createCommand(char *s, int numCom)
{
	commands *c = malloc(sizeof(commands));
	c->theCommand = (char *)calloc(strlen(s)+1, sizeof(char));
	strcpy(c->theCommand, s);
	c->num = numCom;

	return c;
}

Node *createNode(commands *com)
{
	Node *n = malloc(sizeof(Node));
	//n->data = (commands *)malloc(sizeof(commands));
	n->data = com;

	return n;
}

void clean(int argc, char **argv)
{
	int i;
	for ( i = 0; i < argc+1; i++ )
	{
		free(argv[i]);
	}
	free(argv);
}// end clean

