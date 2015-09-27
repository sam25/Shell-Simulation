#ifndef UTILITY_H
#define UTILITY_H

#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int isSaveable(char *s);
void strip(char *s);
int handleAmpersand(char *str);
char *trim(char *str);
int getNumCommand(char *s);
int countTokens(char *sentence);
//char * getCommand(char *command, char **arg);

#endif //UTILITY_H
