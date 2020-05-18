#include "Arduino.h"

#ifndef PCF8583RAM_h
#define PCF8583RAM_h
//---------------------------------------------------------------------------------------------------------
class PCF8583RAM {
  public:
    PCF8583RAM(uint8_t);                          // PCF8583 SRAM
    void init();                                  // 
    void write(uint8_t m_addr, uint8_t m_data);   // 
    void update(uint8_t m_addr, uint8_t m_data);  // 
    uint8_t read(uint8_t m_addr);                 // 
  private:
    uint8_t m_chip_addr;                          // I2C adres
};
//---------------------------------------------------------------------------------------------------------
#endif
