#include "sv_eeprom.h"
#include "initialize.h"
#include "sv_wifi.h"

const char CURRENT_VERSION[] = "1.1";

configStruct conf;
char OTAIPAddress[16];

void setup() {
  Serial.begin(115200);
  Serial.println("Getting configuration...");
  conf = getConfiguration();

  sprintf(OTAIPAddress, "%d.%d.%d.%d", conf.otaIPAddress[0], conf.otaIPAddress[1], conf.otaIPAddress[2], conf.otaIPAddress[3]);

  Serial.print("OTA IP Address is: ");
  Serial.println(OTAIPAddress);
  
  if(conf.roomNumber == 0) {
    Serial.println("Not set up");
    initialize();
  }
  else {
    Serial.print("Got room number: ");
    Serial.println(conf.roomNumber, DEC);
  }

  Serial.print("SSID is:  ");
  Serial.println(conf.ssid);
  Serial.print("Password is: ");
  Serial.println(conf.password);

 Serial.println("Connecting to wifi...");
 svConnect(conf);
 Serial.println("Connected.");
 
}

void loop() {
  checkForUpdate(OTAIPAddress, (char *)CURRENT_VERSION);

  delay(30000);
}
