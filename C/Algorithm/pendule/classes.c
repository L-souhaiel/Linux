#include"classes.h" 

char getcracter()
{
    char caracter = getchar(); 
    caracter=toupper(caracter);
    while(getchar()!='\n'); 
    return caracter; 
}




void returnchaine(char *originalchaine , char *gamechaine  , char caracter)
{
    int size_chain = strlen(originalchaine);
    for ( int i = 0 ; i < size_chain; i ++  )
    {
        if (originalchaine[i]==caracter){gamechaine[i]=caracter;}
    }    
}


void intialisechain(char *gamechain , char  *orignialchain) 
{

    int sizechain = strlen(orignialchain);
    
   
   int nb1 =nbHasard(sizechain);
   if(sizechain> length_chain)
   {
       int nb2; 
       do 
       {
        nb2=nbHasard(sizechain);
       }while(nb2==nb1);
   


    for (int i = 0 ; i < sizechain ; i++)
    {
        if(i==nb1){gamechain[nb1]=orignialchain[nb1];}
        
        else if (i==nb2) {gamechain[nb2]=orignialchain[nb2];}
        
        else 
        {
        gamechain[i]='*';
        }
    }

   }

   else 
   {

        for (int i = 0 ; i < sizechain ; i++)
    {
        if(i==nb1){gamechain[nb1]=orignialchain[nb1];}
         else 
        {
        gamechain[i]='*';
        }
    }
   }
}


int nbHasard(int sizechain)
{
    srand(time(NULL));
    int nb1 = (rand() % (sizechain ));
    return nb1;
}