#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>
#include "types.h"

void svConnect(configStruct conf) {
  WiFi.begin(conf.ssid, conf.password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void checkForUpdate(char *OTAIPAddress, const char *current_version) {
  char OTAURL[128];
  char OTAPATH[] = "/svUpdate/svUpdate.php";

  Serial.println("Checking for updates.");
  
  t_httpUpdate_return ret = ESPhttpUpdate.update(OTAIPAddress, 80, OTAPATH, current_version);
    switch (ret) {
      case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s",  ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        break;
      case HTTP_UPDATE_NO_UPDATES:
        Serial.println("No updates");
        break;
      case HTTP_UPDATE_OK:
        break;
    }
}

void sendTemperature(byte roomNumber, float temp) {
  return;
}

int getExpectedPosition(byte roomNumber) {
  return SV_CLOSED;
}

