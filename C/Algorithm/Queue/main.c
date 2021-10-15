#include"queue.h" 
#include<unistd.h>


int main ()
{

Queue *queue=intiliserQueue(); 
addElementQueue(queue,4);
addElementQueue(queue,8);
addElementQueue(queue,15);
addElementQueue(queue,16);
addElementQueue(queue,23);
addElementQueue(queue,42);
showQueue(queue); 
printf("\nI will take %d",unstackingQueue(queue));
printf("\nI will take %d",unstackingQueue(queue));

sleep(3);

showQueue(queue); 
printf("\n"); 
return EXIT_SUCCESS;
}