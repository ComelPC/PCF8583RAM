// PCF8583RAM library for Arduino, 256 x 8  240 for user
// 
//---------------------------------------------------------------------------------------------------------
#include <Arduino.h>
#include <Wire.h>
#include "PCF8583RAM.h"
//       _____
//  CL -|  ^  |- VCC
//  CL -|     |- INT
//  A0 -|     |- SCL
// GND -|_____|- SDA

// I2C address is 0x50 = A0(GND)
//---------------------------------------------------------------------------------------------------------
PCF8583RAM::PCF8583RAM(uint8_t _i2c_addr) {
  m_chip_addr = _i2c_addr;                                  // I2C adres PCF8583 SRAM
}
//---------------------------------------------------------------------------------------------------------
void PCF8583RAM::init() {                                      //
  Wire.begin();
}
//---------------------------------------------------------------------------------------------------------
void PCF8583RAM::write(uint8_t m_addr, uint8_t m_data) {       //
  Wire.beginTransmission(m_chip_addr);
  Wire.write(m_addr);
  Wire.write(m_data);
  Wire.endTransmission();
  delay(5);
}
//---------------------------------------------------------------------------------------------------------
void PCF8583RAM::update(uint8_t m_addr, uint8_t m_data) {      // 
  uint8_t m_exist_data;                                     //

  m_exist_data = read(m_addr);
  if (m_data != m_exist_data) {                             //
    Wire.beginTransmission(m_chip_addr);
    Wire.write(m_addr);
    Wire.write(m_data);
    Wire.endTransmission();
    delay(5);
  }
}
//---------------------------------------------------------------------------------------------------------
uint8_t PCF8583RAM::read(uint8_t m_addr) {                     // 
  uint8_t m_data = 0xFF;

  Wire.beginTransmission(m_chip_addr);
  Wire.write(m_addr);
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)m_chip_addr, (uint8_t)1);
  if (Wire.available())
    m_data = Wire.read();
  return m_data;
}
