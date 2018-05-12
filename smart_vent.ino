#include "sv_eeprom.h"
#include "initialize.h"

char OTAIPAddress[16];
byte roomNumber;

void setup() {
  Serial.begin(115200);
  Serial.println("Getting IP Address...");
  getOTAIPAddress((char *)&OTAIPAddress);
  Serial.print("OTA IP Address is: ");
  Serial.println(OTAIPAddress);
  
  roomNumber = getRoomNumber();
  if(roomNumber == 0) {
    Serial.println("Not set up");
    initialize();
  }
  else {
    Serial.print("Got room number: ");
    Serial.println(roomNumber, DEC);
  }
  
 
}

void loop() {}
