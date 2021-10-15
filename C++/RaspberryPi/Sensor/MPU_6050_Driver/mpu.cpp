#include "mpu.h"



Mpu6050::Mpu6050():m_acc_x_out_H(0x3B) , m_i2c(0x68 ,1) , m_acc_z(0), m_gyro_x(0), m_gyro_y(0) , m_gyro_z(0) , m_acc_y(0) , m_acc_x(0) , m_rotationAngle_x(0) , m_rotationAngle_y(0)
{

Values_sensor m_values ; 


getVall.getAccleration_x= &m_acc_x;
getVall.getAcceleration_y= &m_acc_y; 
getVall.getAcceleration_z= &m_acc_z; 
getVall.getTemperature= &m_tmp; 
getVall.getRotationSpeed_x= &m_gyro_x;
getVall.getRotationSpeed_y= &m_gyro_y;
getVall.getRotationSpeed_z= &m_gyro_z; 


getVall.getRotationAngle_x= &m_rotationAngle_x;
getVall.getRotationAngle_y= &m_rotationAngle_y;
getVall.getRotationAngle_z= &m_rotationAngle_z;

}




void Mpu6050::Setup()
{

 const unsigned char mgmt_register=0x6B;   
 m_i2c.WriteByte(0x00 , mgmt_register); // to make the sensor in the standby mode because the sensor come in the sleep mode . 
 RaspiGpio::milisecondDelay(300);

}



void Mpu6050::Start()

{

uint8_t bytesOfBeginRead = m_acc_x_out_H;

for (int i(0) ; i < sizeof(m_values)  ; i++)
{
    buffer[i]=m_i2c.ReadBytes(bytesOfBeginRead);
    RaspiGpio::milisecondDelay(10); 
    bytesOfBeginRead +=1;
}


 convert_uint8_to_int16(values, buffer )






m_acc_x = m_values.acc_x / 16384.0f;
m_acc_y = m_values.acc_y / 16384.0f;
m_acc_z = m_values.acc_z /16384.0f;

int zero_point = -512 - ( 35 * 340); 
m_tmp = (m_values.tmp - zero_point) / 340.0;

m_gyro_x = m_values.gyro_x / 131.0f; 
m_gyro_y = m_values.gyro_y / 131.0f;
m_gyro_z = m_values.gyro_z / 131.0f; 

m_rotationAngle_x= atan(m_acc_x /(sqrt((m_acc_y * m_acc_y)+ (m_acc_z * m_acc_z)))) * ( 180.0 / M_PI);
m_rotationAngle_y= atan(m_acc_y /(sqrt((m_acc_x * m_acc_x)+ (m_acc_z * m_acc_z)))) * ( 180.0 / M_PI); 
m_rotationAngle_z= atan(m_acc_z /(sqrt((m_acc_x * m_acc_x ) + (m_acc_y * m_acc_y)))) * (180.0 / M_PI);



}



 
void Mpu6050::PrintAllValues()
{
system("clear"); 

std::cout << " acceleration in x_achse : " << m_acc_x << " g ." << std::endl;  
std::cout << " acceleration in y_achse : " << m_acc_y << " g ." << std::endl; 
std::cout << " acceleration in z_achse : " << m_acc_z << " g ." << std::endl; 
std::cout << " Temperature  : " << m_tmp << " C ." << std::endl; 
std::cout << " Rotation by x_achse : " << m_gyro_x << " deg/s ." << std::endl; 
std::cout << " Rotation by y_achse : " << m_gyro_y << " deg/s ." << std::endl; 
std::cout << " Rotation by z_achse : " << m_gyro_z << " deg/s ." << std::endl; 

std::cout <<" ---------------------------------------------------"<< std::endl ; 
 
std::cout<<"by Accelerometer  ==> Rotation Angle by the X achse : " << m_rotationAngle_x << " deg ."  <<std::endl;
std::cout<<"by Accelerometer  ==> Rotation Angle by the Y achse : " << m_rotationAngle_y << " deg ."  <<std::endl;
std::cout<<"by Accelerometer  ==> Rotation Angle by the Y achse : " << m_rotationAngle_z << " deg ."  <<std::endl;  


}





 

