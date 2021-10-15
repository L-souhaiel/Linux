
#include "Bitoperation.h"


int16_t convert_big_to_littel_endian(int16_t bits)
{
    int16_t left = bits << 8 ;
    int16_t right=bits >> 8 ; 
    right &= 0xFF; 

    return left | right; 
}





void convert_uint8_to_int16(Values_sensor *values, int8_t *buffer )
{

 values->acc_x= ((int16_t )buffer[0] )  | ((int16_t )buffer[1] << 8 ) ;  
 values->acc_y=((int16_t )buffer[2]  )  | ((int16_t )buffer[3] << 8 ); 
 values->acc_z=((int16_t )buffer[4]   ) | ((int16_t )buffer[5] << 8 ); 
 values->tmp=((int16_t )buffer[6]    )  |   ((int16_t )buffer[7] << 8 ); 
 values->gyro_x=((int16_t )buffer[8]  ) | ((int16_t )buffer[9] << 8 ); 
 values->gyro_y=((int16_t )buffer[10] ) | ((int16_t )buffer[11] << 8 ); 
 values->gyro_z=((int16_t )buffer[12] ) | ((int16_t )buffer[13] << 8 );   

 values->acc_x = convert_big_to_littel_endian( values->acc_x); 
 values->acc_y = convert_big_to_littel_endian( values->acc_y); 
 values->acc_z = convert_big_to_littel_endian( values->acc_z); 
 values->tmp = convert_big_to_littel_endian( values->tmp); 
 values->gyro_x = convert_big_to_littel_endian( values->gyro_x); 
 values->gyro_y = convert_big_to_littel_endian( values->gyro_y); 
 values->gyro_z = convert_big_to_littel_endian( values->gyro_z); 

} 