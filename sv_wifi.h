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
  
  Serial.print("Checking for update at ");
  Serial.print(OTAIPAddress);
  Serial.println(OTAPATH);
  Serial.print("Current version is: ");
  Serial.println(current_version);
  
  t_httpUpdate_return ret = ESPhttpUpdate.update(OTAIPAddress, 80, OTAPATH, current_version);
    switch (ret) {
      case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s",  ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        break;
      case HTTP_UPDATE_NO_UPDATES:
        Serial.println("[update] Update no Update.");
        break;
      case HTTP_UPDATE_OK:
        Serial.println("[update] Update ok."); // may not called we reboot the ESP
        break;
    }
}

