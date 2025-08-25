#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
}Node ;


typedef struct LinkedList
{
    Node *head;
    Node *tail;
    int size;
    
}LinkedList;
