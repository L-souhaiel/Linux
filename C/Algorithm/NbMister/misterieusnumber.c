#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MIN 1
#define MAX 100
#define TRUE 1 
#define FALSE 0 

int main (int argc , char *argv[])

{
char a = 'y' ;
int continuee=FALSE; 
do
{
int nb=0 ;
int givnb;
int  cost = 0;
srand(time(NULL));
nb = (rand() % (MAX - MIN + 1)) + MIN;
a = 'y';

while(nb !=givnb)

{
printf("\nWhat is the Number !  ");
scanf("%d",&givnb);
cost+=1;
if(givnb > nb ) { printf("\nMore less");}
else if ( givnb<nb){printf("\nUpper");}
else
{
printf("\nCongratulation . it's equal. your Cost is %d \n" , cost);
do
{
printf("\nDo you want to play again ? [y/n] \n");
scanf("%c",&a);
}while((a != 'y') && (a != 'n'));

if ( a == 'y') { continuee = TRUE;}else {continuee=FALSE;}
}


}


}while(continuee==TRUE);

return EXIT_SUCCESS ;
}
