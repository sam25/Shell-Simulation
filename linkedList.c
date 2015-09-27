/*
*
*cscd340
*Sami Awwad
*
*Linked List
*/

#include "linkedList.h"

LinkedList * linkedList()
{
    LinkedList * list = malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}// end linkedList
/*
Node * buildNode()
{
    size_t max = 100;
    size_t strSize;
    char input[max];
    Node * noodle = NULL;

    printf("Enter a Word: \n");
    scanf("%s", input);
    printf("\n");
    strSize = strlen(input);

    noodle = malloc(sizeof(Node));
    noodle->data = (char *)calloc(strSize+1, sizeof(char));
    strncpy(noodle->data, input, strSize);

    return noodle;
}

void sort(LinkedList * theList)
{
    if ( theList->size > 1 )
    {
        Node * i, * j, * pos;
        Node * swap = malloc(sizeof(Node));
        size_t max = 100;
        for ( i = theList->head; i->next != NULL; i = i->next )
        {
            pos = i;
            for( j = i->next; j != NULL; j = j->next )
            {
                if ( strncmp( pos->data, j->data, max ) > 0 )
                    pos = j;
            }
            if ( strncmp( pos->data, i->data, max ) != 0 )
            {
                swap->data = i->data;
                i->data = pos->data;
                pos->data = swap->data;
            }
        }
        free(swap);
    }
    else
        printf("List is too small to need sorting.\n\n");

} */

void 
clearList (void (*release)(void *), LinkedList * theList)
{
    Node * temp;

    while ( theList->head != NULL )
    {
    	temp = theList->head;
        release(temp->data);
        free(temp->data);
        theList->head = theList->head->next;
        free(temp);
    }

    free(theList);
}// end clearList

/*
void printCommandList(LinkedList * theList)
{
    if ( theList->head != NULL )
    {
        Node * curr = NULL;
        Command *temp;
        for( curr = theList->head; curr != NULL; curr = curr->next )
        {
        	temp = (Command *)curr->data;
            printf("%d %s\n", temp->num, temp->theCommand);
        }
        printf("\n");
    }
    else
        printf("Empty List.\n");
} */

void 
printList (char *(*print)(void *), LinkedList *theList)
{
	if ( theList->head != NULL )
    {
        Node * curr = NULL;
       	
        for( curr = theList->head; curr != NULL; curr = curr->next )
        {
        	char *node_info = print(curr->data);
            printf("%s", node_info);
            free(node_info);
        }
        printf("\n");
    }
    else
        printf("Empty List.\n");
}// end printList

void 
addLast (LinkedList * theList, Node * nn)
{

    if ( theList->head != NULL )
    {
        Node * curr = NULL;
        for ( curr = theList->head; curr->next != NULL; curr = curr->next );

        curr->next = nn;
        nn->next = NULL;
    }
    else
    {
        theList->head = nn;
        theList->head->next = NULL;
    }
    theList->size++;
}// end addLast

void 
addFirst (LinkedList * theList, Node * nn)
{

	nn->next = theList->head;
	theList->head = nn;
	theList->size++;
}// end addFirst

int
findMatch (int (*match)(void*, char*), LinkedList * theList,
			char *token)
{
	int isMatch = 0;
	if ( theList->head != NULL )
    {
        Node * curr = NULL;
 
        for( curr = theList->head; curr!= NULL; curr = curr->next )
        {
        	
        	if ( (isMatch = match(curr->data, token)) )
                break;
           	else if( curr->next == NULL )
            	printf("No match.\n");
        }
	}
	return isMatch;		
}// end findMatch				

int 
removeItem (void (*release)(void *), int (*match)(void*, char*), 
			LinkedList * theList, char *token)
{
	int isMatch = 0;
    if ( theList->head != NULL )
    {
        Node * curr = NULL;
        Node * prev = NULL;

        for( curr = theList->head; curr!= NULL;
            prev = curr, curr = curr->next )
        {
        	
        	if ( (isMatch = match(curr->data, token)) )
           	{
            	if ( prev == NULL )
            		theList->head = curr->next;

                else
                    prev->next = curr->next;

				release(curr->data);
                free(curr->data);
                free(curr);
                theList->size--;
                break;
           }
           else if( curr->next == NULL )
           {
                printf("No match.\n");
           }
        }
    }
    else
        printf("The list is empty.\n");
  	return isMatch;      
}// end removeItem
