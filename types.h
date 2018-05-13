#ifndef _SV_TYPES_
#define _SV_TYPES_

struct configStruct {
  char otaIPAddress[4];
  byte roomNumber;
  char ssid[64];
  char password[64];
};
#endif
