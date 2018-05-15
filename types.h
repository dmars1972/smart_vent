#ifndef _SV_TYPES_
#define _SV_TYPES_

struct configStruct {
  char otaIPAddress[4];
  byte roomNumber;
  bool hasTempSensor;
  char ssid[64];
  byte password[64];
};

const int SV_OPEN = 75;
const int SV_CLOSED = 0;
#endif
