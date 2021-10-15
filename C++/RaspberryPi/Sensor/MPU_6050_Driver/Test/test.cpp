#include "../mpu.h"

#include "../../gpio.h"




int main ()

{


  Mpu6050 mpu;
  mpu.Setup(); 
  
  for(;;)
  {
  mpu.Start();
  mpu.PrintAllValues();  
  }

return 0 ; 
}
