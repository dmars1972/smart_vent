#include <ESP8266WiFi.h>

void initialize() {
  IPAddress local_IP(192,168,43,77);
  IPAddress gateway(192,168,1,1);
  IPAddress subnet(255,255,255,0);
  char uniqueSSID[63];
  String mac = WiFi.macAddress();

  Serial.println("Beginning initial setup...");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed");

  sprintf(uniqueSSID, "sv-%s", mac.c_str());
  Serial.print("My SSID is: ");
  Serial.println(uniqueSSID);
  Serial.println(WiFi.softAP((const char *) uniqueSSID) ? "Ready" : "Failed");
  Serial.print("My address is: ");
  Serial.println(WiFi.softAPIP());
}

