#include "alias.h"

Alias * build_alias_node(char *akey, char *avalue)
{
	trim(akey); trim(avalue);
	Alias *an = malloc(sizeof(Alias));
	
	an->key = (char *)calloc(strlen(akey)+1, sizeof(char));
	strcpy(an->key, akey);
	
	an->value = (char *)calloc(strlen(avalue)+1, sizeof(char));
	strcpy(an->value, avalue);
	
	return an;
}

char * print_alias_node(void *an)
{
	char *alias_str;
	Alias *node = (Alias *)an;
	size_t klen = strlen(node->key);
	size_t vlen = strlen(node->value);
	alias_str = (char *)calloc(klen + vlen + 9, sizeof(char));
	
	strcat(alias_str, "alias ");
	strcat(alias_str, node->key);
	strcat(alias_str, "=");
	strcat(alias_str, node->value);
	strcat(alias_str, "\n");
	
	return alias_str;
}

char * get_alias(void *data)
{
	Alias *node = (Alias *)data;
	return node->key;
}

char * get_value(void *data)
{
	Alias *node = (Alias *)data;
	return node->value;
}

void release_alias_node(void *data)
{
	Alias *node = (Alias *)data;
	free(node->key);
	free(node->value);
}

int is_match(void *data, char *word)
{
	Alias *node = (Alias *)data;
	
	if (strcmp(node->key, word) == 0)
		return 1;
	return 0;
}
