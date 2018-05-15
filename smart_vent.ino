#include <Servo.h>
#include <SpritzCipher.h>
#include "sv_eeprom.h"
#include "initialize.h"
#include "sv_wifi.h"
#include "temperature.h"

const char CURRENT_VERSION[] = "1.25";
const char VENT_PIN = 4;

configStruct conf;
char OTAIPAddress[16];
Servo vent;
int currentPos = SV_OPEN;

void setup() {
  spritz_ctx s_ctx;
  byte key[32] = {'k','a','u','o','k','2','9','u','a','9','$','3','8','7','a','8','9','d','a','8','n','w','?','u','l','s','U','9','3','4','n','o'};
  int i;
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
  
  spritz_setup(&s_ctx, key, sizeof(key));
  spritz_crypt(&s_ctx, conf.password, sizeof(conf.password), conf.password);  
  
 Serial.println("Connecting to wifi...");
 svStartWifi(conf);
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
