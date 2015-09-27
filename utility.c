#include "utility.h"

int isSaveable(char *s)
{
	regex_t regex;
	int res;

	res = regcomp(&regex, "^[[:graph:]]", 0);
	if (res)
	{
		fprintf(stderr, "Could not compile regex\n");
		exit(-1);
	}

	res = regexec(&regex, s, 0, NULL, 0);
	regfree(&regex);
	if (!res)
		return 1;
	return 0;
}

void strip(char *s)
{
  int len;
  len = strlen(s);
  if(s[len - 2] == '\r')
    s[len -2] = '\0';

  else if(s[len - 1] == '\n')
    s[len -1] = '\0';
}// end strip

int handleAmpersand(char *str)
{
	int len = strlen(str);

	if (str[len-1] == '&')
	{
		str[len-1] = '\0';
		char *pt = NULL, *ptr = str + len-1;
		//remove whitespaces
		if (ptr != str)
		{
			while ( isspace(*(--ptr)) && ptr != str) {}
		}
		if (str + len - 1 != ptr)
			*(ptr+1) = '\0';
		//printf("string is: %s\n", str);
		return 1;
	}
	return 0;
}

char *trim(char *str)
{
	if (str == NULL || str[0] == '\0')
		return NULL;
	size_t len = 0;
	char *frontptr = str, *backptr = NULL;

	len = strlen(str);
	backptr = str + len;

	//shift front and back pointer until they reach a non-whitespace
	while ( isspace(*frontptr) )
		++frontptr;
	if (backptr != frontptr)
	{
		while(isspace(*(--backptr)) && backptr != frontptr) {}
	}

	if (str + len -1 != backptr)
		*(backptr+1) = '\0';
	else if(frontptr != str && backptr == frontptr)
		*str = '\0';

	backptr = str;
	if ( frontptr != str)
	{
		while (*frontptr)
		{
			*backptr++ = *frontptr++;
		}
		*backptr = '\0';
	}

	return str;
}//end trim

int getNumCommand(char *s)
{
	char delim = '|';
	int i, count = 1, len = strlen(s);
	for ( i = 0; i < len; i++)
	{
		if (s[i] == delim)
			count++;
	}
	return count;
}

int countTokens(char *sentence)
{
	size_t size;
	int count = 0;
	size = strlen(sentence);
	char *ptr = sentence;

	if (sentence[0] != ' ')
		count++;

	while ( (ptr = strchr(ptr, ' ')) != NULL )
	{
		count++;
		ptr++;
	}

	if (sentence[size-1] == ' ')
		count--;

	return count;
}
/*
char * getCommand(char *command, char **arg)
{
	int i;
	for (i = 0;  i < sizeof(*arg); i++)
	{
		strcat(command, (char*)arg[i]);
		fprintf(stdout, "%s\n", command);
		strcat(command, " ");
	}
	fprintf(stdout, "%s\n", command);
	return command;
}
*/


