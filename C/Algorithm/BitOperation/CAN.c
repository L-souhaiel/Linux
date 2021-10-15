#include "CAN.h"

static int ZeroCount   =  1;
static int OneCount    =  0;
static int FrameError  =  0;
static int SetBitCount =  0;




void CAN_Paramater_Initialise(int *ENDOfCRC)
{
    ZeroCount   =  1;
    OneCount    =  0;
    FrameError  =  0;
    SetBitCount =  0;
    *ENDOfCRC    =  0;

    hcan.Message_Identifier  = 0x00;
    hcan.DLC = 0x00;
    hcan.CRC = 0x00;

    for (int i = 0; i < 8 ; i++)
        hcan.RxData[i] = 0x00; 
 

}



int CAN_RxData_Set_Frame(__uint8_t Frame , int *achieveCrcDel)
{
    int onebit = 0;

    if (*achieveCrcDel == 0)

    {

    if (ZeroCount == 5 && OneCount == 0)
    {
        onebit = (Frame >> 7) & 1;
        if(onebit == 0)
        {
            printf("Error in zero Bit");
            return 1; 
            
        }

        else 
        {
            ZeroCount = 0;
            OneCount = 0;
            return 0;
            
        }
        
    }

    else if(OneCount == 5 && ZeroCount == 0)
    {
        onebit = (Frame >> 7) & 1;
        if (onebit == 1)
        {
            printf("Error in one Bit");
            return 1;
        }

        else 
        {
            OneCount  = 0;
            ZeroCount = 0;
            return 0;
        }
    }

    else if((ZeroCount < 5 && OneCount ==0) || (ZeroCount == 0 && OneCount <5 ))
    {
        
        onebit = (Frame >> 7) & 1;

        if (onebit == 0)
        {
        ZeroCount++;
        OneCount = 0;
        
        }

        else if(onebit == 1)
        {
            ZeroCount = 0;
            OneCount++;
            
        }
        
        
        
        if(SetBitCount < 11)
        {
            hcan.Message_Identifier = (hcan.Message_Identifier<< 1) | (Frame >> 7);
            SetBitCount++;
            return 0;
            
        }

        else if((SetBitCount >= 11) && (SetBitCount <14))
         {
             SetBitCount++;
             return 0;
         }


        else if((SetBitCount >= 14) && (SetBitCount <=17))
        {
            hcan.DLC = (hcan.DLC << 1) | (Frame >> 7); 
            SetBitCount++;
            return 0;
        }

        if(SetBitCount >= 18)
        {

            if (hcan.DLC == 0)
            {
                if((SetBitCount >=18) && (SetBitCount <=32))
                {
                    hcan.CRC = (hcan.CRC << 1) | (Frame >>7);
                      SetBitCount++;
                       return 0;
                }
                else if(SetBitCount == 33)
                {
                    onebit = (Frame >> 7) & 1;
                    if(onebit == 0)
                       { 
                            printf("Error in one Bit DLC 0\n");
                           return 1;
                       }

                    else if(onebit == 1)
                        {*achieveCrcDel = 1;
                        return 0;
                           
                        }                        
                }
            }


            else if(hcan.DLC == 1)
            {
                if((SetBitCount >= 18) && (SetBitCount <=25))
                {
                    hcan.RxData[0] = (hcan.RxData[0] << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }

                else if((SetBitCount >= 26) && (SetBitCount <=40))
                {
                    hcan.CRC = (hcan.CRC << 1) | (Frame >> 7);
                      SetBitCount++;
                     return 0;
                }

                else if (SetBitCount == 41)
                {
                      onebit = (Frame >> 7) & 1;
                    if(onebit == 0)
                       {  printf("Error in one Bit DLC 1\n");
                           return 1;
                       }

                    else if(onebit == 1)
                        {*achieveCrcDel = 1;
                        return 0;}

                }

            }


            else if(hcan.DLC == 2)
            {
                if((SetBitCount >= 18) && (SetBitCount <=25))
                {
                    hcan.RxData[0] = (hcan.RxData[0] << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }

                else if((SetBitCount >=26) && (SetBitCount <=33))
                {
                     hcan.RxData[1] = (hcan.RxData[1] << 1) | (Frame >> 7);
                       SetBitCount++;
                      return 0;
                }

                else if((SetBitCount >=34) && (SetBitCount <=48))
                {
                    hcan.CRC = (hcan.CRC << 1) | (Frame >> 7);
                       SetBitCount++;
                      return 0;
                }

                else if(SetBitCount == 49)
                {
                    onebit = (Frame >> 7) & 1;
                    if(onebit == 0)
                        {
                             printf("Error in one Bit DLC 2\n");
                            return 1;
                       }

                    else if(onebit == 1)
                        {*achieveCrcDel = 1;
                        return 0;}
                }

            }

            else if(hcan.DLC == 3)
            {
                  if((SetBitCount >= 18) && (SetBitCount <=25))
                {
                    hcan.RxData[0] = (hcan.RxData[0] << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }

                 else if((SetBitCount >=26) && (SetBitCount <=33))
                {
                     hcan.RxData[1] = (hcan.RxData[1] << 1) | (Frame >> 7);
                       SetBitCount++;
                      return 0;
                }

                 else if((SetBitCount >=34) && (SetBitCount <=41))
                {
                     hcan.RxData[2] = (hcan.RxData[2] << 1) | (Frame >> 7);
                       SetBitCount++;
                       return 0;
                }

                else if((SetBitCount >=42) && (SetBitCount <=56))
                {
                    hcan.CRC = (hcan.CRC << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }

                else if(SetBitCount == 57)
                {
                       onebit = (Frame >> 7) & 1;
                    if(onebit == 0)
                       { 
                           printf("Error in one Bit DLC 3\n");
                           return 1;
                       }

                    else if(onebit == 1)
                       { *achieveCrcDel = 1;
                       return 0;}

                }

            }

            else if(hcan.DLC == 4)
            {
                    if((SetBitCount >= 18) && (SetBitCount <=25))
                {
                    hcan.RxData[0] = (hcan.RxData[0] << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }

                 else if((SetBitCount >=26) && (SetBitCount <=33))
                {
                     hcan.RxData[1] = (hcan.RxData[1] << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }

                 else if((SetBitCount >=34) && (SetBitCount <=41))
                {
                     hcan.RxData[2] = (hcan.RxData[2] << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }

                else if((SetBitCount >=42) && (SetBitCount <=49))
                {
                    hcan.RxData[3] = (hcan.RxData[3] << 1) | (Frame >> 7);
                     SetBitCount++;
                      return 0;
                }

                else if((SetBitCount >= 50) && (SetBitCount <=64))
                {
                    hcan.CRC = (hcan.CRC << 1) | (Frame >> 7);
                     SetBitCount++;
                      return 0;
                }

                else if(SetBitCount == 65)
                {
                        onebit = (Frame >> 7) & 1;
                    if(onebit == 0)
                        {
                            printf("Error in one Bit DLC 4\n");
                            return 1;
                        }

                    else if(onebit == 1)
                       { *achieveCrcDel = 1;
                       return 0;}
                }

            }


            else if(hcan.DLC == 5)
            {
                   if((SetBitCount >= 18) && (SetBitCount <=25))
                {
                    hcan.RxData[0] = (hcan.RxData[0] << 1) | (Frame >> 7);
                     SetBitCount++;
                      return 0;
                }

                else if((SetBitCount >=26) && (SetBitCount <=33))
                {
                     hcan.RxData[1] = (hcan.RxData[1] << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }

                else if((SetBitCount >=34) && (SetBitCount <=41))
                {
                     hcan.RxData[2] = (hcan.RxData[2] << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }

                else if((SetBitCount >=42) && (SetBitCount <=49))
                {
                    hcan.RxData[3] = (hcan.RxData[3] << 1) | (Frame >> 7);
                     SetBitCount++;
                      return 0;
                }

                else if((SetBitCount >= 50) && (SetBitCount <=57))
                {
                    hcan.RxData[4] = (hcan.RxData[4] << 1) | (Frame >> 7);
                     SetBitCount++;
                      return 0;
                }

                else if((SetBitCount >= 58) && (SetBitCount <= 72))
                {
                     hcan.CRC = (hcan.CRC << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }

                else if(SetBitCount == 73)
                {
                     onebit = (Frame >> 7) & 1;
                    if(onebit == 0)
                       { 
                           printf("Error in one Bit DLC 5\n");
                           return 1;
                       }

                    else if(onebit == 1)
                       { *achieveCrcDel = 1;
                       return 0;}

                }

            }

            else if (hcan.DLC == 6)
            {
                    if((SetBitCount >= 18) && (SetBitCount <=25))
                {
                    hcan.RxData[0] = (hcan.RxData[0] << 1) | (Frame >> 7);
                     SetBitCount++;
                      return 0;
                }

                  else if((SetBitCount >=26) && (SetBitCount <=33))
                {
                     hcan.RxData[1] = (hcan.RxData[1] << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }

                  else if((SetBitCount >=34) && (SetBitCount <=41))
                {
                     hcan.RxData[2] = (hcan.RxData[2] << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }

                   else if((SetBitCount >=42) && (SetBitCount <=49))
                {
                    hcan.RxData[3] = (hcan.RxData[3] << 1) | (Frame >> 7);
                     SetBitCount++;
                      return 0;
                }

                   else if((SetBitCount >= 50) && (SetBitCount <=57))
                {
                    hcan.RxData[4] = (hcan.RxData[4] << 1) | (Frame >> 7);
                     SetBitCount++;
                      return 0;
                }

                 else if((SetBitCount >= 58) && (SetBitCount <= 65))
                {
                      hcan.RxData[5] = (hcan.RxData[5] << 1) | (Frame >> 7);
                       SetBitCount++;
                      return 0;
                }

                 else if((SetBitCount >= 66) && (SetBitCount <= 80))
                {
                     hcan.CRC = (hcan.CRC << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }


                else if(SetBitCount == 81)
                {
                     onebit = (Frame >> 7) & 1;
                    if(onebit == 0)
                        {
                            printf("Error in one Bit DLC 6\n");
                            return 1;
                        }

                    else if(onebit == 1)
                        {*achieveCrcDel = 1;
                        return 0;}

                }
            }

            else if(hcan.DLC == 7)
            {

                     if((SetBitCount >= 18) && (SetBitCount <=25))
                {
                    hcan.RxData[0] = (hcan.RxData[0] << 1) | (Frame >> 7);
                     SetBitCount++;
                      return 0;
                }

                else if((SetBitCount >=26) && (SetBitCount <=33))
                {
                     hcan.RxData[1] = (hcan.RxData[1] << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }

                  else if((SetBitCount >=34) && (SetBitCount <=41))
                {
                     hcan.RxData[2] = (hcan.RxData[2] << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }

               else if((SetBitCount >=42) && (SetBitCount <=49))
                {
                    hcan.RxData[3] = (hcan.RxData[3] << 1) | (Frame >> 7);
                     SetBitCount++;
                      return 0;
                }

                 else if((SetBitCount >= 50) && (SetBitCount <=57))
                {
                    hcan.RxData[4] = (hcan.RxData[4] << 1) | (Frame >> 7);
                     SetBitCount++;
                      return 0;
                }

               else if((SetBitCount >= 58) && (SetBitCount <= 65))
                {
                      hcan.RxData[5] = (hcan.RxData[5] << 1) | (Frame >> 7);
                       SetBitCount++;
                      return 0;
                }

                 else if((SetBitCount >= 66) && (SetBitCount <= 73))
                {
                       hcan.RxData[6] = (hcan.RxData[6] << 1) | (Frame >> 7);
                        SetBitCount++;
                      return 0;
                }

                 else if((SetBitCount >= 74) && (SetBitCount <= 88))
                {
                     hcan.CRC = (hcan.CRC << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }


                else if(SetBitCount == 89)
                {
                     onebit = (Frame >> 7) & 1;
                    if(onebit == 0)
                        {
                             printf("Error in one Bit DLC 7\n");
                            return 1;
                       }

                    else if(onebit == 1)
                        {*achieveCrcDel = 1;
                        return 0;}

                }

            }


            else if(hcan.DLC == 8)
            {
                
                   if((SetBitCount >= 18) && (SetBitCount <=25))
                {
                    hcan.RxData[0] = (hcan.RxData[0] << 1) | (Frame >> 7);
                     SetBitCount++;
                      return 0;
                }

                else if((SetBitCount >=26) && (SetBitCount <=33))
                {
                     hcan.RxData[1] = (hcan.RxData[1] << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }

                 else if((SetBitCount >=34) && (SetBitCount <=41))
                {
                     hcan.RxData[2] = (hcan.RxData[2] << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }

                else if((SetBitCount >=42) && (SetBitCount <=49))
                {
                    
                    hcan.RxData[3] = (hcan.RxData[3] << 1) | (Frame >> 7);
                     SetBitCount++;
                      return 0;
                }

                else if((SetBitCount >= 50) && (SetBitCount <=57))
                {
                    hcan.RxData[4] = (hcan.RxData[4] << 1) | (Frame >> 7);
                     SetBitCount++;
                      return 0;
                }

               else if((SetBitCount >= 58) && (SetBitCount <= 65))
                {
                      hcan.RxData[5] = (hcan.RxData[5] << 1) | (Frame >> 7);
                       SetBitCount++;
                      return 0;
                }

                  else if((SetBitCount >= 66) && (SetBitCount <= 73))
                {
                       hcan.RxData[6] = (hcan.RxData[6] << 1) | (Frame >> 7);
                        SetBitCount++;
                      return 0;
                }

                 else if((SetBitCount >= 74) && (SetBitCount <= 81))
                {
                    hcan.RxData[7] = (hcan.RxData[7] << 1) | (Frame >> 7);
                     SetBitCount++;
                      return 0;
                }

                else if((SetBitCount >= 82) && (SetBitCount <= 96))
                {
                   
                     hcan.CRC = (hcan.CRC << 1) | (Frame >> 7);
                      SetBitCount++;
                      return 0;
                }

            


                else if(SetBitCount == 97)
                {
                     onebit = (Frame >> 7) & 1;
                    if(onebit == 0)
                       { 
                            printf("Error in one Bit DLC 8\n");
                           return 1;
                      }

                    else if(onebit == 1)
                        {*achieveCrcDel = 1;
                        return 0;}

                }

            }


        }

    
    
    
    }


    }

    return 0;
}



void IntToBinary (__uint64_t  a , char *b)
{

    /*
    Write a Sequence of the 1 and 0 bit of a specific usigned 64 long World. 
    */

    char c; 
    int counter = 31;
    
    if(NULL == b)
        return; 

     for(int i = 0; i  < 32 ; i++)
     {
         if(a % 2 == 0)
            b[i]='0'; 
         else 
            b[i]='1'; 
        

        a = a /2;
             
     } 

     b[32] = '\0';      

     for(int i = 0 ; i < 16; i++ )
     {
      c = b[counter];
      b[counter] = b[i]; 
      b[i] = c; 
      counter --;
     }
     
}

//#define CRC_Generetor_Polynome 0xC599;  //1100010110011001

//data = data ^ (CRC_Generetor_Polynome << 4); 


__uint32_t DivisorPoly  = 0xC599;

__uint64_t createMask(char  a, char b)
{

   /*
   Create a Mask for a byte to find those bits.
   - a : should be the start bit index
   - b : should be the end bit index

   for exemeple to create a mask from bit 11 to 16
   of a world a = 11 , b = 16  
   */


   __uint64_t r = 0;
   for (unsigned i=a; i<=b; i++)
       r |= 1ul << i;

   return r;
}



__uint16_t CRCCalculator(CAN_Type_Def *hcanstr)
{

    /*Calculate CRC checksum based on CAN_Type_def strcut data*/

int bitStatus;

__uint16_t CRC = 0x00;

int shifter = 11;

   
if (hcanstr->DLC == 0)
{
 __uint64_t data = 0x00;

data =((__uint64_t) hcanstr->Message_Identifier  << 7) | hcanstr->DLC;
data = data << 15;
shifter = 11;


do 
{
    shifter--;
    bitStatus = (hcanstr->Message_Identifier >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);
shifter++;
int bitcounter  = 15 + 3 + 4 + shifter;
int shifting = 15;
do
{
 __uint64_t r = createMask((bitcounter -1) - shifting ,bitcounter -1);
 
 
  if((bitcounter -1) - shifting >=0)
 {CRC =CRC |((r & data) >> (bitcounter -1 -shifting));}

 else if ((bitcounter -1) - shifting < 0)
 {
     __uint64_t r = createMask(0,bitcounter -1);
     CRC =CRC | (r & data);
     return CRC >> (-(bitcounter -1 -shifting));
 } 

CRC = CRC ^ DivisorPoly;


shifter = 16;
do 
{
    shifter--;
    bitStatus = (CRC >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);

shifter++;
shifter = 16 -shifter; 
CRC = CRC << shifter;

bitcounter = bitcounter-(shifting + 1); 
shifting = shifter -1;

}while(bitcounter > 0);

return (CRC >> shifter);   

}

if (hcanstr->DLC == 1)
{

 __uint64_t data = 0x00;

data =((__uint64_t) hcanstr->Message_Identifier  << 7) | hcanstr->DLC;
data = (data << 8) | hcanstr->RxData[0];
data = data << 15;
shifter = 11;


do 
{
    shifter--;
    bitStatus = (hcanstr->Message_Identifier >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);
shifter++;

int bitcounter  = 15 + 3 + 4 + 8   + shifter;

int shifting = 15;

do
{
 __uint64_t r = createMask((bitcounter -1) - shifting ,bitcounter -1);

  if((bitcounter -1) - shifting >=0)
 {CRC =CRC |((r & data) >> (bitcounter -1 -shifting));}

 else if ((bitcounter -1) - shifting < 0)
 {
     __uint64_t r = createMask(0,bitcounter -1);
     CRC =CRC | (r & data);
     return CRC >> (-(bitcounter -1 -shifting));
 } 


CRC = CRC ^ DivisorPoly;



shifter = 16;
do 
{
    shifter--;
    bitStatus = (CRC >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);

shifter++;
shifter = 16 -shifter; 
CRC = CRC << shifter;
bitcounter = bitcounter-(shifting + 1); 
shifting = shifter -1;
}while(bitcounter > 0);

return (CRC >> shifter);   
    
}

if (hcanstr->DLC == 2)
{

 __uint64_t data = 0x00;

data =((__uint64_t) hcanstr->Message_Identifier  << 7) | hcanstr->DLC;
data = (data << 8) | hcanstr->RxData[0];
data = (data << 8) | hcanstr->RxData[1];
data = data << 15;
shifter = 11;



do 
{
    shifter--;
    bitStatus = (hcanstr->Message_Identifier >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);
shifter++;

int bitcounter  = 15 + 3 + 4 + 8  + 8 + shifter;

int shifting = 15;

do
{
 __uint64_t r = createMask((bitcounter -1) - shifting ,bitcounter -1);

  if((bitcounter -1) - shifting >=0)
 {CRC =CRC |((r & data) >> (bitcounter -1 -shifting));}

 else if ((bitcounter -1) - shifting < 0)
 {
     __uint64_t r = createMask(0,bitcounter -1);
     CRC =CRC | (r & data);
     return CRC >> (-(bitcounter -1 -shifting));
 } 


CRC = CRC ^ DivisorPoly;


shifter = 16;
do 
{
    shifter--;
    bitStatus = (CRC >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);

shifter++;
shifter = 16 -shifter; 

CRC = CRC << shifter;


bitcounter = bitcounter-(shifting + 1); 
shifting = shifter -1;

}while(bitcounter > 0);

return (CRC >> shifter);   
    
}

if (hcanstr->DLC == 3)
{

  __uint64_t data = 0x00;

data =((__uint64_t) hcanstr->Message_Identifier  << 7) | hcanstr->DLC;
data = (data << 8) | hcanstr->RxData[0];
data = (data << 8) | hcanstr->RxData[1];
data = (data << 8) | hcanstr->RxData[2];
data = data << 15;
shifter = 11;



do 
{
    shifter--;
    bitStatus = (hcanstr->Message_Identifier >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);
shifter++;

int bitcounter  = 15 + 3 + 4 + 8  + 8 + shifter +8;

int shifting = 15;

do
{
 __uint64_t r = createMask((bitcounter -1) - shifting ,bitcounter -1);
 
 if((bitcounter -1) - shifting >=0)
 {CRC =CRC |((r & data) >> (bitcounter -1 -shifting));}

 else if ((bitcounter -1) - shifting < 0)
 {
     __uint64_t r = createMask(0,bitcounter -1);
     CRC =CRC | (r & data);
     return CRC >> (-(bitcounter -1 -shifting));
 } 



CRC = CRC ^ DivisorPoly;




shifter = 16;
do 
{
    shifter--;
    bitStatus = (CRC >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);

shifter++;
shifter = 16 -shifter; 

CRC = CRC << shifter;


bitcounter = bitcounter-(shifting + 1); 
shifting = shifter -1;

}while(bitcounter > 0);

return (CRC >> shifter);      
}


if (hcanstr->DLC == 4)
{
    __uint64_t data = 0x00;

data =((__uint64_t) hcanstr->Message_Identifier  << 7) | hcanstr->DLC;
data = (data << 8) | hcanstr->RxData[0];
data = (data << 8) | hcanstr->RxData[1];
data = (data << 8) | hcanstr->RxData[2];
data = (data << 8) | hcanstr->RxData[3];

int boolien =0;
shifter = 11;



do 
{
    shifter--;
    bitStatus = (hcanstr->Message_Identifier >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);
shifter++;

int bitcounter  =  3 + 4 + 8  + 8 + shifter +8 + 8;

int shifting = 15;

do
{
 __uint64_t r = createMask((bitcounter -1) - shifting ,bitcounter -1);

  if((bitcounter -1) - shifting >=0)
 {CRC =CRC |((r & data) >> (bitcounter -1 -shifting));}

 else if ((bitcounter -1) - shifting < 0)
 {
     __uint64_t r = createMask(0,bitcounter -1);
     CRC =CRC | (r & data);
     return CRC >> (-(bitcounter -1 -shifting));
 } 


CRC = CRC ^ DivisorPoly;



shifter = 16;
do 
{
    shifter--;
    bitStatus = (CRC >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);

shifter++;
shifter = 16 -shifter; 

CRC = CRC << shifter;


bitcounter = bitcounter-(shifting + 1); 
shifting = shifter -1;


if (bitcounter < 40 && boolien == 0)
{
    data = data << 15;
    bitcounter = bitcounter + 15;
    boolien = 1;
}

}while(bitcounter > 0);

return (CRC >> shifter); 
}

if (hcanstr->DLC == 5)
{
     __uint64_t data = 0x00;

data =((__uint64_t) hcanstr->Message_Identifier  << 7) | hcanstr->DLC;
data = (data << 8) | hcanstr->RxData[0];
data = (data << 8) | hcanstr->RxData[1];
data = (data << 8) | hcanstr->RxData[2];
data = (data << 8) | hcanstr->RxData[3];
data = (data << 8) | hcanstr->RxData[4];

int boolien =0;
shifter = 11;



do 
{
    shifter--;
    bitStatus = (hcanstr->Message_Identifier >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);
shifter++;

int bitcounter  =  3 + 4 + 8  + 8 + shifter +8 + 8 +8;

int shifting = 15;

do
{
 __uint64_t r = createMask((bitcounter -1) - shifting ,bitcounter -1);
 
  if((bitcounter -1) - shifting >=0)
 {CRC =CRC |((r & data) >> (bitcounter -1 -shifting));}

 else if ((bitcounter -1) - shifting < 0)
 {
     __uint64_t r = createMask(0,bitcounter -1);
     CRC =CRC | (r & data);
     return CRC >> (-(bitcounter -1 -shifting));
 } 



CRC = CRC ^ DivisorPoly;



shifter = 16;
do 
{
    shifter--;
    bitStatus = (CRC >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);

shifter++;
shifter = 16 -shifter; 

CRC = CRC << shifter;


bitcounter = bitcounter-(shifting + 1); 
shifting = shifter -1;


if (bitcounter < 40 && boolien == 0)
{
    data =  data << 15;
    bitcounter = bitcounter + 15;
    boolien = 1;
}

}while(bitcounter > 0);

return (CRC >> shifter);    
}

if (hcanstr->DLC == 6)
{
__uint64_t data = 0x00;

data =((__uint64_t) hcanstr->Message_Identifier  << 7) | hcanstr->DLC;
data = (data << 8) | hcanstr->RxData[0];
data = (data << 8) | hcanstr->RxData[1];
data = (data << 8) | hcanstr->RxData[2];
data = (data << 8) | hcanstr->RxData[3];
data = (data << 8) | hcanstr->RxData[4];

int boolien =0;
shifter = 11;



do 
{
    shifter--;
    bitStatus = (hcanstr->Message_Identifier >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);
shifter++;

int bitcounter  =  3 + 4 + 8  + 8 + shifter +8 + 8 +8;

int shifting = 15;

do
{
 __uint64_t r = createMask((bitcounter -1) - shifting ,bitcounter -1);
 
 if((bitcounter -1) - shifting >=0)
 {CRC =CRC |((r & data) >> (bitcounter -1 -shifting));}

 else if ((bitcounter -1) - shifting < 0)
 {
     __uint64_t r = createMask(0,bitcounter -1);
     CRC =CRC | (r & data);
     return CRC >> (-(bitcounter -1 -shifting));
 } 


CRC = CRC ^ DivisorPoly;



shifter = 16;
do 
{
    shifter--;
    bitStatus = (CRC >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);

shifter++;
shifter = 16 -shifter; 

CRC = CRC << shifter;


bitcounter = bitcounter-(shifting + 1); 
shifting = shifter -1;


if (bitcounter < 35 && boolien == 0)
{
    data = (data << 8) | hcanstr->RxData[5];

    data = data << 15;
    bitcounter = bitcounter + 15 + 8;
    boolien = 1;
}
}while(bitcounter > 0);

return (CRC >> shifter);  

}

if (hcanstr->DLC == 7)
{
  __uint64_t data = 0x00;

data =((__uint64_t) hcanstr->Message_Identifier  << 7) | hcanstr->DLC;
data = (data << 8) | hcanstr->RxData[0];
data = (data << 8) | hcanstr->RxData[1];
data = (data << 8) | hcanstr->RxData[2];
data = (data << 8) | hcanstr->RxData[3];
data = (data << 8) | hcanstr->RxData[4];

int boolien =0;
shifter = 11;



do 
{
    shifter--;
    bitStatus = (hcanstr->Message_Identifier >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);
shifter++;

int bitcounter  =  3 + 4 + 8  + 8 + shifter +8 + 8 +8;

int shifting = 15;

do
{
 __uint64_t r = createMask((bitcounter -1) - shifting ,bitcounter -1);

 if((bitcounter -1) - shifting >=0)
 {CRC =CRC |((r & data) >> (bitcounter -1 -shifting));}

 else if ((bitcounter -1) - shifting < 0)
 {
     __uint64_t r = createMask(0,bitcounter -1);
     CRC =CRC | (r & data);
     return CRC >> (-(bitcounter -1 -shifting));
 } 

CRC = CRC ^ DivisorPoly;



shifter = 16;
do 
{
    shifter--;
    bitStatus = (CRC >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);

shifter++;
shifter = 16 -shifter; 

CRC = CRC << shifter;


bitcounter = bitcounter-(shifting + 1); 
shifting = shifter -1;


if (bitcounter < 27 && boolien == 0)
{
   data = (data << 8) | hcanstr->RxData[5];
   data = (data << 8) | hcanstr->RxData[6];
   data = data << 15;
    bitcounter = bitcounter + 15 + 8 +8;
    boolien = 1;
}
}while(bitcounter > 0);

return (CRC >> shifter);    
}

if (hcanstr->DLC == 8)
{
   __uint64_t data = 0x00;

data =((__uint64_t) hcanstr->Message_Identifier  << 7) | hcanstr->DLC;
data = (data << 8) | hcanstr->RxData[0];
data = (data << 8) | hcanstr->RxData[1];
data = (data << 8) | hcanstr->RxData[2];
data = (data << 8) | hcanstr->RxData[3];
data = (data << 8) | hcanstr->RxData[4];

printf("Data = %lu\n",data);



int boolien =0;
shifter = 11;


do 
{
    shifter--;
    bitStatus = (hcanstr->Message_Identifier >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);
shifter++;



int bitcounter  =  3 + 4 + 8  + 8 + shifter +8 + 8 + 8;


int shifting = 15;

do
{
 __uint64_t r = createMask((bitcounter -1) - shifting ,bitcounter -1);
 
 if((bitcounter -1) - shifting >=0)
 {CRC =CRC |((r & data) >> (bitcounter -1 -shifting));}

 else if ((bitcounter -1) - shifting < 0)
 {
     __uint64_t r = createMask(0,bitcounter -1);
     CRC =CRC | (r & data);
     return CRC >> (-(bitcounter -1 -shifting));
 } 


CRC = CRC ^ DivisorPoly;


shifter = 16;
do 
{
    shifter--;
    bitStatus = (CRC >> shifter) & 1;

}while(bitStatus == 0 && shifter > 0);

shifter++;
shifter = 16 -shifter; 

CRC = CRC << shifter;

if (bitcounter-(shifting + 1) >= 0)
    bitcounter = bitcounter-(shifting + 1); 

else 
    bitcounter = 0;

shifting = shifter -1;

if (bitcounter < 19 && boolien == 0)
{

data = (data << 8) | hcanstr->RxData[5];
data = (data << 8) | hcanstr->RxData[6];
data = (data << 8) | hcanstr->RxData[7];
data = data << 15;
   
    bitcounter = bitcounter + 15 + 8 +8 +8;
    boolien = 1;

}
}while(bitcounter > 0);

return (CRC >> shifter);     
}
          
}


//pio_sm_put_blocking(pio, sm, 1);

int CAN_Send_Message(CAN_Type_Def TxCan)
{
int Zerocounter = 0;
int Onecounter =  0;
int bitStatus = 0;

__uint32_t Firstframe = 0x00;
__uint32_t Secdeframe = 0x00;
__uint32_t Thirdframe = 0x00;
__uint32_t Fourtframe = 0x00;

int FirstFrameBitCounter = 0; 
int SeconFrameBitCounter = 0; 
int ThirdFrameBitCounter = 0; 
int FourtFrameBitcounter = 0;

Zerocounter++; 
Onecounter = 0;

for (int i = 10; i >= 0; i--)
{
 bitStatus = ( TxCan.Message_Identifier >> i) & 1;
if (bitStatus == 0)
{
    Zerocounter++; 
    Onecounter = 0;
    
    if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (bitStatus << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (bitStatus << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (bitStatus << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (bitStatus << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }


    if (Zerocounter == 5)
    {
        
    if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (1 << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (1 << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (1 << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (1 << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }

        Zerocounter = 0;
        Onecounter = 0;
    }

}

else if (bitStatus == 1)
{
    Onecounter++;
    Zerocounter = 0;
   
       if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (bitStatus << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (bitStatus << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (bitStatus << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (bitStatus << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }

   
   
   
    if (Onecounter == 5)
    {
        
    if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (0 << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (0 << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (0 << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (0 << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }


        Onecounter  = 0;
        Zerocounter = 0;
    }
}

}

 
Zerocounter++;
Onecounter = 0;

    if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (0 << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (0 << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (0 << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (0 << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }



if (Zerocounter == 5)
{
Zerocounter = 0;
Onecounter = 0;
    if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (1 << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (1 << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (1 << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (1 << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }
}

Zerocounter++;
Onecounter = 0;


    if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (0 << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (0 << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (0 << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (0 << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }



if (Zerocounter == 5)
{
Zerocounter = 0;
Onecounter = 0;
    if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (1 << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (1 << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (1 << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (1 << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }
}

Zerocounter++;
Onecounter = 0;

    if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (0 << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (0 << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (0 << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (0 << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }


if (Zerocounter == 5)
{
Zerocounter = 0;
Onecounter = 0;
    if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (1 << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (1 << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (1 << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (1 << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }
}

for (int i = 3 ; i >= 0; i--)
{
bitStatus = ( TxCan.DLC >> i) & 1;

if (bitStatus == 0)
{
    Zerocounter++; 
    Onecounter = 0;
        if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (bitStatus << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (bitStatus << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (bitStatus << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (bitStatus << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }




    if (Zerocounter == 5)
    {
            if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (1 << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (1 << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (1 << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (1 << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }
        
        Zerocounter = 0;
        Onecounter = 0;
    }

}




else if (bitStatus == 1)
{
    Onecounter++;
    Zerocounter = 0;
        if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (bitStatus << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (bitStatus << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (bitStatus << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (bitStatus << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }

    if (Onecounter == 5)
    {
            if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (0 << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (0 << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (0 << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (0 << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }
        Onecounter  = 0;
        Zerocounter = 0;
    }
}
}


for (int j = 0; j < TxCan.DLC ; j++)
{
 for (int i = 7; i >=0; i--)
 {
    bitStatus = ( TxCan.RxData[j] >> i) & 1;

if (bitStatus == 0)
{
    Zerocounter++; 
    Onecounter = 0;
       if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (bitStatus << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (bitStatus << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (bitStatus << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (bitStatus << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }

    if (Zerocounter == 5)
    {
            if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (1 << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (1 << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (1 << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (1 << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }
        Zerocounter = 0;
        Onecounter = 0;
    }

}

else if (bitStatus == 1)
{
    Onecounter++;
    Zerocounter = 0;
    
        if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (bitStatus << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (bitStatus << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (bitStatus << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (bitStatus << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }




    if (Onecounter == 5)
    {
            if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (0 << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (0 << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (0 << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (0 << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }
        Onecounter  = 0;
        Zerocounter = 0;
    }
} 
 }   
}




for(int i = 14; i >= 0; i--)
{
   bitStatus = ( TxCan.CRC >> i) & 1;

if (bitStatus == 0)
{
    Zerocounter++; 
    Onecounter = 0;
     if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (bitStatus << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (bitStatus << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (bitStatus << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (bitStatus << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }

    if (Zerocounter == 5)
    {
         if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (1 << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (1 << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (1 << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (1 << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }
        Zerocounter = 0;
        Onecounter = 0;
    }

}

else if (bitStatus == 1)
{
    Onecounter++;
    Zerocounter = 0;
     if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (bitStatus << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (bitStatus << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (bitStatus << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (bitStatus << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }
    if (Onecounter == 5)
    {
         if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (0 << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (0 << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (0 << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (0 << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }
        Onecounter  = 0;
        Zerocounter = 0;
    }
} 
}

Onecounter++;
 if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (1 << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (1 << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (1 << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (1 << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }

if(Onecounter == 5)
{
     if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (1 << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (1 << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (1 << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (1 << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }
    Onecounter = 0;
    Zerocounter = 0;
}



do 
{
       if (FirstFrameBitCounter < 32 && SeconFrameBitCounter == 0 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Firstframe = Firstframe | (1 << (31 - FirstFrameBitCounter));
    FirstFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter <  32 && ThirdFrameBitCounter == 0 && FourtFrameBitcounter == 0)
    {
    Secdeframe = Secdeframe | (1 << (31 - SeconFrameBitCounter));
    SeconFrameBitCounter++;
    }

    else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter < 32 && FourtFrameBitcounter == 0)
    {
    Thirdframe = Thirdframe | (1 << (31 - ThirdFrameBitCounter));
    ThirdFrameBitCounter++;
    }
     
     else if (FirstFrameBitCounter == 32 && SeconFrameBitCounter == 32 && ThirdFrameBitCounter == 32 && FourtFrameBitcounter < 32)
    {
    Fourtframe = Fourtframe | (1 << (31 - FourtFrameBitcounter));
    FourtFrameBitcounter++;
    }


}while(FourtFrameBitcounter < 32);




return 0;



}


__uint32_t createMask2(char  a, char b)
{

   /*
   Create a Mask for a byte to find those bits.
   - a : should be the start bit index
   - b : should be the end bit index

   for exemeple to create a mask from bit 11 to 16
   of a world a = 11 , b = 16  
   */


   __uint32_t r = 0;
   for (unsigned i=a; i<=b; i++)
       r |= 1 << i;

   return r;
}


 __uint8_t data[128]; 


void SetupThe32_bitFrame(__uint32_t *frame)

{
   
    
    int j = 0;

    for (int i = 0; i < 4 ; i++)
    {
       
      for (int z = 31 ; z >=0; z--)
      {
          __uint32_t r = createMask2(z,z);
          data[j] = ((r & frame[i]) >> z) << 7;
          j++;
      }

    }

    for (int i= 0 ; i < 128; i++)
    {
        char b[100];
        IntToBinary(data[i],b);
        printf("%s\n",b);
    }
    
}
    






 
  