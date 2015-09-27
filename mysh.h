#ifndef MYSH_H
#define MYSH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "linkedList.h"
#include "utility.h"
#include "alias.h"
#include "command.h"

#define MAX 100
#define ALIAS "alias"
#define CD "cd"
#define PATH "PATH"
#define UNALIAS "unalias"

void handleCommand(LinkedList *clist, LinkedList *alist, char *s);
int handleBuiltInCommand(LinkedList *alist, char *s);
int handleAlias(LinkedList *alist, char *s);
void attach_alias_node(LinkedList *alist, Alias *an);
int handleUnalias(LinkedList * alist, char *s);
int handlePath(char *s);
int handleCD(char *s);
char * findAliases(LinkedList *alist, char *s);
void forkIt(char ** argv,LinkedList *clist, LinkedList *alist,
			int argc, int backgrdProcess);
void pipeIt(char ** prePipe, char ** postPipe, LinkedList *clist, LinkedList *alist,
			int preSize, int postSize, int backgrdProcess);
void saveCommand(LinkedList *list, char *s, int num);
void sigchld_handler(int signum);
void notice_termination(pid_t id);
void clean(int argc, char **argv);
void printargs(int argc, char **argv);
int makeargs(char *s, char *** argv);
void strip(char *s);
char *trim(char *str);
int handleAmpersand(char *str);


#endif //MYSH_H
