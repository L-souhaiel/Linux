#include "tfmini.h"

Tfmini::Tfmini(uint8_t Adress_slave): _Adress_slave(Adress_slave)
{
    _i2c = new I2C(_Adress_slave , 1); 
     std::cout<<"Begin Range with Tfmini" << std::endl; 

}



bool Tfmini::BeginTrasnsimission()

{
     
    __u8 _write[3] = { 0x01 , 0x02 , 0x07}; 
    __u8 data[7];    
   _i2c->i2cWrRd(_write , data);  
    RaspiGpio::milisecondDelay(100);


    for ( int i(0) ; i < 7 ; i++)
    {

  switch (i)
  {
  
  case 0:
  
  if (data[0] == 0x00) { std::cout<<"Data Invalid " << std::endl;  return false;}
  else if (data[0] == 0x01) { std::cout<<"Data Valid" << std::endl;}     
  break;
  
  case 2: 
  
   _distance = data[2]; 
    break; 
  case 3: 

  _distance |= data[3] << 8;
   break;

   case 4: 

   _strenth = data[4]; 
    break; 

    case 5:
    _strenth |= data[5] << 8; 
     break;
   
    case 6: 
    _mode = data[6];
    break;
   
  }

    } 
    
   std::cout<<" " << (int)data[0] <<"  " <<(int)data[1] <<"  " <<(int)data[2] <<"  " <<(int)data[3]<<"  " <<(int)data[4]<<"  " <<(int)data[5]<<"  " <<(int)data[6] <<std::endl;
  _data.distance = _distance; 
  _data.strenth =  _strenth;
  _data.mode = _mode;

  return true; 
    
}





void Tfmini::printData()
{
    std::cout<<" Distance = " << _data.distance << "         " << " strenth = " <<_data.strenth << "       " << " mode = " << _data.mode <<std::endl; 

} 


int main ()

{
    Tfmini tfmini(sensor); 
    RaspiGpio::milisecondDelay(500);

    for (;;)
    {
    tfmini.BeginTrasnsimission(); 
    tfmini.printData(); 
    } 

    return 0 ; 
    
}
