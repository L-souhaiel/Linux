#include"disco.h"

void writeinChain( char *chainnew , char caracter  , int counter);
int LineNb (FILE  *filee );


void findechain(char *chain , char  *type)
{

    FILE *filee=NULL;
    int size = strlen("/home/louati2/Studium/C/pendule/dico/");
    size+=strlen(type);
    char *path = malloc((size) * sizeof(char)); 
    sprintf(path ,"/home/louati2/Studium/C/pendule/dico/%s",type ); 
    filee=fopen(path,"r");
    int nbline=LineNb(filee); 
    if(filee != NULL)
    { 
    rewind(filee);
    int  nb1 = nbHasard(nbline); 
    if(nb1==0){nb1++;}
    int  caracter=0; 
    rewind(filee);

    while(nb1 > 1) 
    {
    caracter=fgetc(filee);
    if(caracter=='\n')
    {
    nb1--;
    }
    }
    
    int i = 0 ; 
    do
    {
    caracter=fgetc(filee);
    writeinChain(chain,caracter,i);
    i++;
    } while (caracter != '\n');
    }
    else { printf("\nImpossible To open The File . \n");} 
}



int LineNb (FILE  *filee )
{

int counter = 0;
int crarcter = 0;
do 
{ 
    crarcter=fgetc(filee);
    if (crarcter=='\n'){counter+=1;}
}while(crarcter!=EOF);

rewind(filee);
 return counter; 
}






void writeinChain( char *chainnew , char caracter  , int counter)
{
 
 if(((int)caracter >= 65 )&& ((int) caracter <=90))

{ 
chainnew[counter]=caracter;
chainnew[counter+1]='\0';
}


}