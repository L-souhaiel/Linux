#ifndef TFMINI_I2C_H
#define TFMINI_I2C_h

#include "gpio.h"

#define sensor 0X10



struct  Data
{
    int distance; 
    int strenth; 
    int mode;  
};





class Tfmini 
{

public: 

Tfmini(uint8_t Adress_slave);

bool BeginTrasnsimission(); 
Data getData() { return _data;}
void printData(); 


private:

int16_t _distance; 
int16_t _strenth; 
int8_t _mode; 
uint8_t _Adress_slave; 
I2C *_i2c; 
Data _data;
};







#endif