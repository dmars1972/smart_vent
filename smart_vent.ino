#include <Servo.h>
#include "sv_eeprom.h"
#include "initialize.h"
#include "sv_wifi.h"
#include "temperature.h"

const char CURRENT_VERSION[] = "1.17";
const char VENT_PIN = 4;

configStruct conf;
char OTAIPAddress[16];
Servo vent;
int currentPos = SV_OPEN;

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

 Serial.println("Connecting to wifi...");
 svConnect(conf);
 Serial.println("Connected.");

  if(conf.hasTempSensor)
    initTemperatureSensor(DS_PIN);

  vent.attach(VENT_PIN);

  vent.write(SV_OPEN);
  delay(300);
  vent.write(SV_CLOSED);
  delay(300);
  vent.write(SV_OPEN);
  currentPos = SV_OPEN;

  vent.detach();
}

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void loop() {
  float temperature;
  int expectedPos;
  
  svConnect(conf);
  
  checkForUpdate(OTAIPAddress, (char *)CURRENT_VERSION);

  if(conf.hasTempSensor) {
    temperature = getCurrentTemperature();
    sendTemperature(conf.roomNumber, temperature);
  }
  
  expectedPos = getExpectedPosition(conf.roomNumber);

  if(expectedPos != currentPos) {
    vent.attach(VENT_PIN);
    vent.write(expectedPos);
    delay(500);
    vent.detach();
    currentPos = expectedPos;
  }
  
  delay(30000);
}
