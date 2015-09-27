#ifndef ALIAS_H
#define ALIAS_H

#include <stdlib.h>
#include <string.h>

#include "utility.h"

struct alias
{
	char *key;
	char *value;
};
typedef struct alias Alias;

Alias * build_alias_node(char *akey, char *avalue);
char * print_alias_node(void *an);
char * get_alias(void *data);
char * get_value(void *data);
void release_alias_node(void *data);
int is_match(void *data, char *word);


#endif //ALIAS_H
