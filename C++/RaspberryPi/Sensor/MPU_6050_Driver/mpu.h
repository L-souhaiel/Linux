#ifndef MPU_H
#define MPU_H

#include "../gpio.h"
#include "../Bitoperation.h"

class Mpu6050 

{

 public : 

 
 Mpu6050(); 
 void Setup(); 
 void Start();
 
 
 struct Values  
{
 float *getAccleration_x; 
 float *getAcceleration_y; 
 float *getAcceleration_z;
 float *getTemperature;  
 float *getRotationSpeed_x; 
 float *getRotationSpeed_y; 
 float *getRotationSpeed_z;
 float *getRotationAngle_x; 
 float *getRotationAngle_y; 
 float *getRotationAngle_z;
};


 Values getVall; 

 Values getAllData() { return getVall;} //that return struct that contain all data . 
 void PrintAllValues();  //print acc_x acc_y acc_z gyro_x .. 


private : 




 I2C m_i2c;
 const uint8_t m_acc_x_out_H;
 float m_acc_x  , m_acc_y , m_acc_z , m_tmp , m_gyro_x , m_gyro_y , m_gyro_z ,m_rotationAngle_y , m_rotationAngle_x , m_rotationAngle_z;
 Values_sensor m_values;
 int8_t buffer[sizeof(Values)]; 


};





















#endif