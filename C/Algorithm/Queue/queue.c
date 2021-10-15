#include"queue.h" 

void showQueue(Queue *queue)  
{
    if (queue== NULL) { printf("\ncondo\n");exit(EXIT_FAILURE);}
    Element *element =queue->first;  
    do 
    {  
    printf("\n%d.",element->nb);
    element = element->next; 
    }while(element!=NULL);
}



Queue *intiliserQueue()
{
    Queue *queue = malloc(sizeof(Queue)); 
    if (queue==NULL){perror("malloc");exit(EXIT_FAILURE);}
    queue->first=NULL; 
    return queue;
}



void addElementQueue(Queue *queue , int nb1 )
{
Element *element1=malloc(sizeof(Element)); 
if(queue==NULL || element1==NULL){perror("malloc"); exit(EXIT_FAILURE);}
element1->nb=nb1;
Element *element2=malloc(sizeof(Element)); 
element2=queue->first; 

if (queue->first!=NULL)
{
while(element2->next!=NULL)
{
element2=element2->next;
}

element2->next=element1;
element1->next=NULL; 
}

else 
{
queue->first=element1;    
}

}



int unstackingQueue(Queue *queue)
{

    int nbreturned = 0;

    if (queue==NULL) {perror("malloc"); exit(EXIT_FAILURE);}
    if (queue->first!=NULL)
    {
        nbreturned=queue->first->nb; 
        queue->first=queue->first->next; 
    }
   else
   {
        perror("Queue Empty"); 

   }
return nbreturned; 

}




