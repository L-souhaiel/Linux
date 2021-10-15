#ifndef SSH106_H
#define SSH106_H

#include <iostream> 
#include <string.h> 
#include "gpio.h"

#define SSD1306_DISPLAYON       0xAF
#define SSD1306_DISPLAYOFF      0xAE
#define SSD1306_NORMALDISPLAY   0xA6
#define SSD1306_INVERTDISPLAY   0xA7
#define SSD1306_MULTIPLEX_RATIO 0xA8

#define SSD1306_CONTROL_REG     0x00  

#define SSD1306_DATA_REG        0x40





class Ssh106
{
 
 public: 

 Ssh106(uint8_t slave_addresse); 
 
 void draw_line(int x , int y ,const char ascii_str[16]);
 void clearDisplay();
 void displayOn(); 
 void displayOff();
 void update_display(); 


 private: 
 bool SendCommand(uint8_t reg); 
 bool SendData(unsigned char data);
 void draw(int x , int y , const char asci);


 I2C *_dev;
  

};












#endif
