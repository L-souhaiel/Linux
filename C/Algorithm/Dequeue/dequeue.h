#ifndef DEQUEUE_H 
#define DEQUEUE_H

//LIFO last come first out

#include<stdio.h> 
#include<stdlib.h>
#include<unistd.h>

typedef struct Element Element; 
struct Element 
{
int elemnt ; 
Element *next ; 
};

typedef struct Dequeue Dequeue;
struct Dequeue
{
Element *first; 
};

void stacking(Dequeue *dequeue , int nb); //empilage
int unstacking(Dequeue *dequeue); //depilage
Dequeue *intiliseDequeue();
void showQueue(Dequeue *dequeue);  


#endif









