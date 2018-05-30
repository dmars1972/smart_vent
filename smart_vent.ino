#include <Servo.h>

#include <SmartConfig.h>
#include <SmartVentComm.h>
#include "SmartTemp.h"

#include "initialize.h"

#define SEND_INTERVAL 30

const char CURRENT_VERSION[] = "1.66";
const char DEVICE_TYPE[] = "vent";
const char VENT_PIN = 4;

SmartVentComm svc(25836, 25837);

SmartConfig c;

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
  c.setup();
  
  if(c.getRoomNumber() == 255) {
    Serial.println("Not set up");
    initialize();
  }
  else {
    Serial.print("Got room number: ");
    Serial.println(c.getRoomNumber(), DEC);
  }

  while( ! svc.registerVent(c.hasTempSensor())) {
    delay(30000);
  }
  
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
  static long lastSend = 0;
  
  c.OTAUpdate(CURRENT_VERSION, DEVICE_TYPE);
  
  if(lastSend == 0 ||                                   // first call
      (millis() - lastSend) / 1000 > SEND_INTERVAL ||   // has interval passed
      millis() < lastSend) {                            // has the millis reset?
    Serial.println("Sending");
    lastSend = millis();
    
    svc.sendTemperature((unsigned char)60);
  }
  
  
}
