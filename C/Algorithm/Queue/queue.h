#ifndef QUEUE_H
#define QUEUE_H 
#include<stdio.h> 
#include<stdlib.h> 

//FIFO first come first out 

typedef struct Element Element; 
struct Element
{
    int nb ; 
    Element *next; 
};
 

typedef struct Queue Queue;
struct  Queue 

{

Element *first ; 
};


Queue *intiliserQueue(); 
void addElementQueue(Queue *queue , int nb1); 
void showQueue(Queue *queue);

int unstackingQueue(Queue *queue);

#endif