#ifndef CLASSES_H
#define CLASSES_H

#include<stdio.h> 
#include<stdlib.h> 
#include<ctype.h> 
#include<string.h> 
#include<time.h> 

#define length_chain 6


char getcracter();
void returnchaine(char *originalchaine , char *gamechaine  , char caracter);
void intialisechain(char *gamechain , char  *orignialchain); 
int nbHasard(int sizechain);

#endif 