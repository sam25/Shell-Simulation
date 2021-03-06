/*
*
*Sami Awwad
*CSCD340
*
*The Shell 
*
*This is the main file mysh.c
*
*/

#include "mysh.h"
int i = 1;

sig_atomic_t child_exit_status;

int main()
{
	int numCom = 1;
	char s[MAX];
	LinkedList *clist = linkedList();
	LinkedList *alist = linkedList();

	printf("?: ");
	fgets(s, MAX, stdin);

	while(strcmp(s, "exit\n") != 0)
	{
		sigchld_handler(1);
		strip(s);
		trim(s);
				
		if (isSaveable(s))
		{
			saveCommand(clist, s, numCom);
			numCom++;
		}
		
		handleCommand(clist, alist, s);
			
		printList(print_command_node, clist);
		printList(print_alias_node, alist);
		
		printf("?: ");
		fgets(s, MAX, stdin);
		
	}// end while
	
	clearList(release_command_node, clist);
	clearList(release_alias_node, alist);
}// end main

void handleCommand(LinkedList *clist, LinkedList *alist, char *s)
{
	int res1, res2, backgrdProcess;
	char *token, *saveptr, *ns;
	char *delim = "|";
	char ** prePipe = NULL, ** postPipe = NULL;
	
	if (handleBuiltInCommand(alist, s))
		return;
	backgrdProcess = handleAmpersand(s);
	
	ns = findAliases(alist, s);
			
	// code to determine pipe sides
	token = strtok_r(ns, delim, &saveptr);
	trim(token);
	res1 = makeargs(token, &prePipe);
		
	token = strtok_r(NULL, delim, &saveptr);
	trim(token);		
	res2 = makeargs(token, &postPipe);
	free(ns);
		
	if (res1 != -1 && res2 != -1) // pipe between child and grandchild
		pipeIt(prePipe, postPipe, clist, alist, res1, res2, backgrdProcess);
	else if (res1 != -1) // single command, just fork and exec
		forkIt(prePipe, clist, alist, res1, backgrdProcess);
	
	if (res1 != -1)
		clean(res1, prePipe);
	if (res2 != -1)
		clean(res2, postPipe);

}//end handleCommand

int handleBuiltInCommand(LinkedList *alist, char *s)
{
	int retVal = 0;
	char *temp = (char *)calloc(strlen(s)+1, sizeof(char));
	strcpy(temp, s);
	char *token, *saveptr;
	
	if ( (token = strtok_r(temp, " ", &saveptr)) != NULL)
	{	
		char *newTemp = saveptr;
		if (strcmp(token, ALIAS) == 0)
			retVal = handleAlias(alist, newTemp);
		else if (strcmp(token, UNALIAS) == 0)
			retVal = handleUnalias(alist, newTemp);
		else if (strcmp(token, PATH) == 0)
			retVal = handlePath(newTemp);
		else if (strcmp(token, CD) == 0)
			retVal = handleCD(newTemp);	
	}
	free(temp);
	return retVal;
}//end handleBuiltInCommand

int handleAlias(LinkedList *alist, char *s)
{
	char *temp = (char *)calloc(strlen(s)+1, sizeof(char));
	strcpy(temp, s);

	char *token, *key, *value, *saveptr;
	char *delim1 = "=\"";
	Alias *an = NULL;

	if ( (key = strtok_r(temp, delim1, &saveptr)) != NULL)
	{
		if ( (value = strtok_r(NULL, "\"", &saveptr)) != NULL)
		{
			if (!findMatch(is_match, alist, key))
			{
				an = build_alias_node(key, value);
				attach_alias_node(alist, an);
				free(temp);				
				return 1;
			}		
		}
	}
	
	free(temp);
	return 0;
}//end handleAlias

void attach_alias_node(LinkedList *alist, Alias *an)
{
	Node *nn = malloc(sizeof(Node));
	nn->data = an;
	addLast(alist, nn);	
}//end attach_alias_node

int handleUnalias(LinkedList * alist, char *s)
{
	int retVal = 0;
	char *temp = (char *)calloc(strlen(s)+1, sizeof(char));
	strcpy(temp, s);
	char *token, *saveptr;
	
	token = strtok_r(temp, " ", &saveptr);
	
	if ((retVal = removeItem(release_alias_node, is_match, alist, token)))
	{
		fprintf(stdout, "%s was removed\n", token);
	}
		
	free(temp);
	return retVal;
}// end handleUnalias

int handlePath(char *s)
{
	char *temp = (char *)calloc(strlen(s)+1, sizeof(char));
	strcpy(temp, s);
	char *token, *saveptr;
	
	free(temp);
	return 0;
}// end handlePath

int handleCD(char *s)
{
	char *temp = (char *)calloc(strlen(s)+1, sizeof(char));
	strcpy(temp, s);
	char *token, *saveptr;
	
	free(temp);
	return 0;
}// end handleCD

char * findAliases(LinkedList *alist, char *s)//may belong in utility
{
	int keySize, valSize;
	char *h, *key, *value, *ptr = NULL;
	char buf[MAX], buf2[MAX];
	strcpy(buf, s);
	strcpy(buf2, s);
	size_t size = strlen(s);
	//h = buf;
	//printf("%p\n", s);
	//strcpy(h, s);
	
	if ( alist->head != NULL )
    {
        Node * curr = NULL;
 
        for( curr = alist->head; curr!= NULL; curr = curr->next )
        {
        	key = get_alias(curr->data);
        	value = get_value(curr->data);
        	keySize = strlen(key);
        	valSize = strlen(value);
        	while ((ptr = strstr(s, key)) != NULL)
        	{
        		printf("%s\n", buf);
        		strncpy(buf, s, ptr - s);
        		
        		buf[ptr-s] = '\0';
        		sprintf(buf+(ptr - s), "%s%s", value, ptr+keySize);
				printf("%s\n", ptr+keySize);
        		strcpy(s, buf);
        	}              
        }       
	}
	char *new = (char *)calloc(strlen(buf)+1, sizeof(char));
	strcpy(new, buf);
	printf("new string is: %s\n", new);
	return new;
}

void
forkIt(char ** argv,LinkedList *clist, LinkedList *alist,
		int argc, int backgrdProcess)
{
	int status;
	pid_t pid = fork();

	if ( pid != 0 && !backgrdProcess)
	{
		waitpid(pid, &status, 0);
		child_exit_status = status;
	}

	else if ( pid == 0 )
	{
		if ( backgrdProcess )
		{
			//setpgid(0,0);
			fprintf(stdout,"[%d]-Starting \n", getpid() );
		}
		if ( execvp(argv[0], argv) == -1 )
		{
			fprintf(stdout, "command not found\n");
			clean(argc, argv);
  			argv = NULL;
  			clearList(release_command_node, clist);
			clearList(release_alias_node, alist);
  			exit(-1);
		}
	}
}// end forkIt

void
pipeIt(char ** prePipe, char ** postPipe, LinkedList *clist, LinkedList *alist,
		int preSize, int postSize, int backgrdProcess)
{
	int status;
	pid_t pid = fork();
	
	if (pid != 0 && !backgrdProcess)
	{
		waitpid(pid, &status, 0);
		child_exit_status = status;
	}
	if (pid == 0)//in child
	{
		int fd[2];
	
		if (pipe(fd) < 0)
			exit(0);
		
		if (fork() == 0)//in grandchild
		{
			close(fd[0]);
			close(1);
		
			dup(fd[1]);
			close(fd[1]);
		
			if (execvp(prePipe[0], prePipe) == -1)
			{	
				fprintf(stderr, "command not found\n");
				clean(preSize, prePipe);
				clean(postSize, postPipe);
				clearList(release_command_node, clist);
				clearList(release_alias_node, alist);
				prePipe = NULL;
				exit(-1);
			} 
		}
		else
		{
			if (backgrdProcess)
				fprintf(stdout,"[%d]-Starting \n", getpid() );
			
			close(fd[1]);
			close(0);
		
			dup(fd[0]);
			close(fd[0]);
		
			if (execvp(postPipe[0], postPipe))
			{
				char command[MAX+MAX];
				fprintf(stderr, "command not found\n");
				clean(postSize, postPipe);
				clean(preSize, prePipe);
				clearList(release_command_node, clist);
				clearList(release_alias_node, alist);
				postPipe = NULL;
				exit(-1);
			}
		}
	}
}// end pipeIt

void saveCommand(LinkedList *clist, char *s, int num)
{
	Node *nn = malloc(sizeof(Node));
	nn->data = build_command_node(s, num);
	addLast(clist, nn);
}

void sigchld_handler (int signum)
{
  int pid, status, serrno;
  serrno = errno;
  while (1)
    {
      pid = waitpid (WAIT_ANY, &status, WNOHANG);
      if (pid < 0)
          break;
      if (pid == 0)
        break;
      child_exit_status = status;
      notice_termination (pid);
    }
  errno = serrno;
}// end sigchld_handler

void notice_termination(pid_t id)
{
	fprintf(stdout, "[%d]+ Done\tWith exit_status: %d\n", id, child_exit_status);
}// end notice_termination

void clean(int argc, char **argv)
{
	int i;
	for ( i = 0; i < argc+1; i++ )
	{
		free(argv[i]);
	}

	free(argv);
	argv = NULL;

}// end clean

void printargs(int argc, char **argv)
{
	int x;
	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);

}// end printargs

int makeargs(char *s, char *** argv)
{
	if ( s == NULL || s[0] == '\0' || s[0] == '\n' )
		return -1;

	int numToken = 1, i;
	char *ptr = s;
	char *saveptr;
	char *token;
	int size = strlen(s);

	while ((ptr = strchr(ptr, ' ')) != NULL)
	{
		numToken++;
		while ( isspace(*(++ptr)) && ptr != s + size-1) {}
	}

	token = strtok_r(s, " ", &saveptr);
	(* argv) = (char **)calloc(numToken+1, sizeof(char*));
	(*argv)[0] = (char *)calloc(strlen(token)+1, sizeof(char));
	strcpy((*argv)[0], token);

	for( i = 1; i < numToken; i++)
	{
		token = strtok_r(NULL, " ", &saveptr);
		(*argv)[i] = (char *)calloc(strlen(token)+1, sizeof(char));
		strcpy((*argv)[i], token);
	}

	(*argv)[numToken] = NULL;

   return numToken;

}// end makeArgs

