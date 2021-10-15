#include"classes.h" 
#include"disco.h" 
#include<unistd.h>

#define TRUE 1 
#define FALSE 0 
#define length_mouves_max 10


int main () 

{

    int repeatGame= FALSE ; 
    char  chain[100];
    char *chain2 = NULL;
    int mouves ; 
    char caracter; 
    char ask = 0 ; 

    printf("\nWelcome To Pendul Game \n"); 
    sleep(2);
    char i  = 0 ; 
  do 
  {
    while((int) i < 49 ||(int) i > 51)
    {
    printf("\nChoose Type of Chain by Typing : "); 
    printf("\n1:Color");
    printf("\n2:Animal"); 
    printf("\n3:Countrys\n");
    i=(int)getcracter();
    }
    sleep(1);
    char type[30];
    switch((int)i)
    {
        case 49 : strcpy(type , "color.txt"); break ; 
        case 50 : strcpy(type , "animal.txt");break ; 
        default:strcpy(type,"country.txt");
    } 


    findechain(chain ,type);
    chain2=malloc(sizeof(char)*strlen(chain)); 
    intialisechain(chain2,chain); 


  switch(i)
    {
        case 49 : strcpy(type , "color"); break ; 
        case 50 : strcpy(type , "animal");break ; 
        default:strcpy(type,"country");
    } 


    mouves = length_mouves_max ; 
    ask = 0 ; 
    i=0;


    while(strcmp(chain2 , chain ) != 0 && mouves >0)
    { 
    system("clear");
    printf("\nType: %s " , type );     
    printf("\nYou have %d mouves" , mouves);
    printf("\nSecret Chain is : %s",chain2); 
    printf("\nGive Character : ");
    caracter=getcracter(); 
    returnchaine(chain , chain2 , caracter);
    mouves--;
    sleep(1);
    if(strcmp(chain2 , chain)==0 && mouves > 0)
    {
        printf("\nSuccess You did it in %d mouves " ,(10-mouves )  );
        printf("\nSecret Chain is : %s\n",chain2);
        sleep(2); 
        do 
        {
        printf("\nDo you want to play again ?[Y/N] : "  ); 
        ask =getcracter(); 
        }while(ask!='Y' && ask!='N');
        if (ask =='Y') { repeatGame=TRUE; sleep(1);system("clear"); printf("\nGame Will be Repeated \n");sleep(2); system("clear");} else {sleep(1); system("clear"); printf("\nSee you soon Bye nayek \n");sleep(2); system("clear"); exit(EXIT_SUCCESS);} 
    } 
    else if (mouves == 0 )
    {
        printf("\nMouves are Already finshied You Lose\n"); 
             do 
        {
        printf("\nDo you want to play again ?[Y/N] : "  ); 
        ask =getcracter(); 
        }while(ask!='Y' && ask!='N');
        if (ask =='Y') { repeatGame=TRUE; sleep(1);system("clear"); printf("\nGame Will be Repeated \n");sleep(2); system("clear"); } else { sleep(1); system("clear"); printf("\nSee you soon Bye nayek \n");sleep(2); system("clear"); exit(EXIT_SUCCESS);} 
    }

    }

  } while(repeatGame == TRUE);
    return EXIT_SUCCESS;
}




