#include <Servo.h>

#include "sv_eeprom.h"
#include "initialize.h"
#include "sv_wifi.h"
#include "temperature.h"

const char CURRENT_VERSION[] = "1.39";
const char DEVICE_TYPE[] = "vent";
const char VENT_PIN = 4;

configStruct conf;
char OTAIPAddress[16];
Servo vent;
int currentPos = SV_OPEN;

byte macAddress[6];
char myName[21];
bool isRegistered = false;

void setup() {
  int i;
  Serial.begin(115200);
  Serial.print("Device: ");
  Serial.println(DEVICE_TYPE);
  Serial.print("Software version: ");
  Serial.println(CURRENT_VERSION);
  
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

  svDecrypt(conf.password, sizeof(conf.password));

  WiFi.macAddress(macAddress);

  sprintf(myName, "sv%02x%02x%02x%02x%02x%02x", macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);
  WiFi.hostname(myName);
  
  Serial.print("My host name is: ");
  Serial.println(myName);
  Serial.println("Connecting to wifi...");
  svStartWifi(conf);
  Serial.println("Connected.");

  isRegistered = svRegister(myName, conf.roomNumber);
  
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

void loop() {
  float temperature;
  int expectedPos;
  
  svConnect(conf);

  checkForUpdate(OTAIPAddress, (char *)CURRENT_VERSION, DEVICE_TYPE);

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
