// SRAM PCF8583, 256 x 8  240 for user
// 
//---------------------------------------------------------------------------------------------------------

//       _____
//  CL -|  ^  |- VCC
//  CL -|     |- INT
//  A0 -|     |- SCL
// GND -|_____|- SDA

#include <PCF8583RAM.h>
PCF8583RAM sram(0x50);                             // 0x50 = A0(GND)

char ZN;
//---------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  sram.init();
}
//---------------------------------------------------------------------------------------------------------
void loop() {
  Serial.println("SRAM PCF8583:");
  Serial.println("r - Read");
  Serial.println("0 - Write (write 0x00) data");
  Serial.println("b - Blank (write 0xFF)");
  Serial.println("x - Write random data");
  Serial.println();

  while (1) {
    if (Serial.available() > 0) {
      ZN = Serial.read();

      if (ZN == 'r')                              // read
        sram_read();

      if (ZN == 'b') {                            // blank and read
        sram_blank();
        sram_read();
      }
       if (ZN == '0') {                            // write 00 and read
        sram_00();
        sram_read();
      }

      if (ZN == 'x') {                            // write random data and read
        sram_write_random_data();
        sram_read();
      }
    }
  }
}
//---------------------------------------------------------------------------------------------------------
void sram_read() {
  Serial.print("         ");
  for (uint8_t i = 0; i < 16; i++) {
    Serial.print('0');
    Serial.print(i, HEX);
    Serial.print(' ');
  }
  Serial.println();

  for (uint8_t j = 0; j < 16; j++) {
    Serial.print("000000");
    Serial.print(j, HEX);
    Serial.print("0 ");
    for (uint8_t k = 0; k < 16; k++) {
      uint8_t read_byte = sram.read(j * 16 + k);
      if (read_byte < 16)
        Serial.print('0');
      Serial.print(read_byte, HEX);
      Serial.print(' ');
    }
    Serial.println();
  }
  Serial.println();
}
//---------------------------------------------------------------------------------------------------------
void sram_blank() {
  for (uint16_t i = 17; i < 256; i++)
    sram.write(i, 0xFF);
}
//---------------------------------------------------------------------------------------------------------
void sram_write_random_data() {
  for (uint16_t i = 17; i < 256; i++)
    sram.update(i, random(0, 256));
}
//---------------------------------------------------------------------------------------------------------
void sram_00() {
  for (uint16_t i = 17; i < 256; i++)
    sram.write(i, 0x00);
 }   
