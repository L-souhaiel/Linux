#include"dequeue.h" 



int main ( int argc , char *argv[])
{

Dequeue *queue = intilise(); 

stacking(queue,4);
stacking(queue,8);
stacking(queue,15);
stacking(queue,16);
stacking(queue,23);
stacking(queue,42);
printf("\nState Queue: \n");
showQueue(queue); 

sleep(3); 


printf("\nUnstacking number : %d",unstacking(queue));
printf("\nUnstacking number : %d",unstacking(queue));
sleep(2);
printf("\nState Queue: \n");
sleep(1);
showQueue(queue);
printf("\n"); 

    return EXIT_SUCCESS;
}