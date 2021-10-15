#include"liste_chain.h"



int main (int argc , char *argv[])
{
int nb1=1,nb2=2,nb3=3,nb4=4,nb5=5,nb6=7;


Liste *liste = intilise(); 
AddElementAtLastListe(liste , nb1);
AddElementAtLastListe(liste , nb2);
AddElementAtLastListe(liste , nb3);
AddElementAtLastListe(liste , nb4);
AddElementAtLastListe(liste , nb5);
AddElemntAtMidList(liste,nb6,nb3,nb4);
showListe(liste);
int size = sizeList(liste);
printf("\n%d\n",size);



    return EXIT_SUCCESS; 
}







