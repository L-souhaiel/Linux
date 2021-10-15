#include"liste_chain.h"
Liste *intilise()
{
    Liste *liste= malloc(sizeof(Liste)); 
    Element *element1 =malloc(sizeof(Element)); 
    if(element1==NULL || liste==NULL) { exit(EXIT_FAILURE);}

    element1->element=0; 
    element1->next=NULL; 
    liste->first=element1; 
    return liste;
}



void AddElementAtLastListe(Liste *liste , int number) 
{
    Element *element = liste->first;
    Element *addtetElemnt=malloc(sizeof(Element)); 
    if (liste==NULL || addtetElemnt==NULL ){exit(EXIT_FAILURE);}
    addtetElemnt->element=number; 

    while(element->next!=NULL)
    {   

        element=element->next; ; 
    }

    element->next=addtetElemnt; 
    addtetElemnt->next=NULL; 

}


void showListe(Liste *liste)
{
    if (liste == NULL) { printf("\ncondo\n");exit(EXIT_FAILURE);}
    Element *element = liste->first; 
    do 
    {  
    printf("\n%d.",element->element);
    element = element->next; 
    }while(element!=NULL);
}

void AddElemntAtMidList(Liste *liste , int number , int adresse ,  int adresse_apres)
{

Element *newElemnt = malloc(sizeof(Element)); 
newElemnt->element=number; 
if (liste==NULL || newElemnt==NULL){printf("\ncondo\n");exit(EXIT_FAILURE);}
Element *elemnt1=liste->first;

while(elemnt1->element!=adresse && elemnt1->next->element!=adresse_apres)
{
    
    elemnt1=elemnt1->next;;
}


newElemnt->next=elemnt1->next;
elemnt1->next=newElemnt; 

}



int sizeList(Liste *liste)
{
    int size = 0;
    Element *elemt = liste->first; 
    while(elemt!=NULL)
    {
        elemt=elemt->next;
        size++;
    } 

    return size ;

}