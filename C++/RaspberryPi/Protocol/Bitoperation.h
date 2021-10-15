#include <iostream> 
#include<cstdlib> 

// convert big to big endian 

int16_t convert_big_to_littel_endian(int16_t bits);

  struct Values_sensor 
  {
  int16_t acc_x ; 
  int16_t acc_y;
  int16_t acc_z; 
  int16_t tmp ; 
  int16_t gyro_x; 
  int16_t gyro_y; 
  int16_t gyro_z;
  };


//convert uint8 to ont16 ans store the data in a structure 

void convert_uint8_to_int16(Values_sensor *values, int8_t *buffer );