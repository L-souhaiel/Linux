#include<stdio.h>
#include<stdlib.h> 

void takechain(char *chain);

int main ( int argc , char *argv[])
{
    
char chain[10];
printf("\nEnter you Name\n");
takechain(chain);
printf("you name is : %s",chain);
printf("you name is : %s",chain); 


return EXIT_SUCCESS;
}



void takechain( char *chain)
{
fgets(chain,10,stdin); 
}