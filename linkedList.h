#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    void * data;
    struct node * next;
};
typedef struct node Node;


struct linkedlist
{
    Node * head;
    int size;
};
typedef struct linkedlist LinkedList;


LinkedList * linkedList();

Node * buildNode();
void sort(LinkedList * theList);
void clearList(void (*release)(void *), LinkedList * theList);
void printList(char *(*print)(void *), LinkedList *theList);
void addLast(LinkedList * theList, Node * nn);
void addFirst(LinkedList * theList, Node * nn);
int findMatch (int (*match)(void*, char*), LinkedList * theList,
			char *token);
int removeItem (void (*release)(void *), int (*match)(void*, char*), 
			LinkedList * theList, char *token);


#endif // LINKEDLIST_H
