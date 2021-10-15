#ifndef LISTE_CHAIn_H
#define LISTE_CHAIN_H
#include<stdio.h> 
#include<stdlib.h> 


typedef struct Element Element; 
struct Element
{
   int element ; 
   Element *next; 
};

typedef struct Liste Liste ; 
struct  Liste
{
    Element *first ; 
};



Liste *intilise(); 
void AddElementAtLastListe(Liste *liste , int number);
void showListe(Liste *liste); 
void AddElemntAtMidList(Liste *liste , int number , int adresse ,  int adresse_apres);
int sizeList(Liste *liste);



#endif 