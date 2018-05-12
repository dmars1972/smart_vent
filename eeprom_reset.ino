#include <EEPROM.h>

int addr = 0;
byte value;

void setup() {
  Serial.begin(115200);
  Serial.print("Writing...");
  EEPROM.begin(4);
  EEPROM.write(addr, 192);
  EEPROM.write(addr+1, 168);
  EEPROM.write(addr+2, 1);
  EEPROM.write(addr+3, 100);

  EEPROM.commit();
  // put your setup code here, to run once:

}

void loop() {
  addr = 0;

  value = EEPROM.read(addr);
  Serial.print("Read:  ");
  Serial.print(value, DEC);
  Serial.print(".");
  addr = addr + 1;
  
  value = EEPROM.read(addr);
  Serial.print(value, DEC);
  Serial.print(".");
  addr = addr + 1;
  
  value = EEPROM.read(addr);
  Serial.print(value, DEC);
  Serial.print(".");
  addr = addr + 1;

  value = EEPROM.read(addr);
  Serial.print(value, DEC);

  Serial.println();

  addr = addr + 1;
  value = EEPROM.read(addr);
  Serial.print("Room number: ");
  Serial.println(value, DEC);
  delay(1000);
}
