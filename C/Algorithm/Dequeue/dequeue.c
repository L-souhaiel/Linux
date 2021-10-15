#include"dequeue.h" 
#include<errno.h>



Dequeue *intiliseDequeue()
{
    Dequeue *liste= malloc(sizeof(Dequeue)); 
    Element *element1 =malloc(sizeof(Element)); 
    if(element1==NULL || liste==NULL) { exit(EXIT_FAILURE);} 
    liste->first=NULL;
    return liste;
}



void showQueue(Dequeue *dequeue)  
{
    if (dequeue== NULL) { printf("\ncondo\n");exit(EXIT_FAILURE);}
    Element *element =dequeue->first;  
    do 
    {  
    printf("\n%d.",element->elemnt);
    element = element->next; 
    }while(element!=NULL);
}




void stacking(Dequeue *dequeue , int nb) //empilage
{

Element *element1=malloc(sizeof(Element)); 
if ( dequeue ==NULL || element1==NULL ) {perror("malloc");   exit(EXIT_FAILURE);}
element1->elemnt=nb;
element1->next=dequeue->first;
dequeue->first = element1; 

}




int unstacking(Dequeue *dequeue) //depilage
{
int nbreturned=0;

if (dequeue==NULL){perror("malloc"); exit(EXIT_FAILURE);}
if (dequeue->first!=NULL && dequeue!=NULL)
{
nbreturned=dequeue->first->elemnt;
dequeue->first=dequeue->first->next; 
}

return nbreturned; 
}
