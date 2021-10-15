#include <stdio.h>
#include <stdlib.h>


struct CAN_Type_Def {
    
    __uint16_t Message_Identifier;
    __uint8_t  DLC; 
    __uint8_t RxData[8]; 
    __uint16_t CRC; 

};



typedef struct CAN_Type_Def CAN_Type_Def;


CAN_Type_Def hcan;


void IntToBinary (__uint64_t  a , char *b);
int CAN_RxData_Set_Frame(__uint8_t Frame , int *achieveCrcDel);
void CAN_Paramater_Initialise(int *ENDOfCRC);
__uint16_t CRCCalculator(CAN_Type_Def *hcanstr);
__uint64_t createMask(char  a, char b);

int CAN_Send_Message(CAN_Type_Def TxCan); 

void SetupThe32_bitFrame(__uint32_t *frame);

