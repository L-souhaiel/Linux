#include "gpio.h"
#define Led 16
#define Taster 4

int main ()
{

    RaspiGpio led(Led,OUT);
    RaspiGpio taster(Taster,IN);
    
    taster.ExportPin(); 
    taster.DirectionPin(IN);
   
    led.ExportPin();
    led.DirectionPin(OUT);
    
    RaspiGpio::milisecondDelay(1000);

    std::cout<<"Begin"<<std::endl;

    for(;;)
    {
   
      if(taster.digitalReadPin()==0)
       {led.digitalWritePin(HIGH);}
       else
       {
         led.digitalWritePin(LOW);
       }
       
      
    }


return 0 ; 
}

