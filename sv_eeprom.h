#include <EEPROM.h>

void getOTAIPAddress(char *OTAIPAddress) {
	int eAddr = 0;
	int value[4];

	EEPROM.begin(4);

	value[eAddr] = EEPROM.read(eAddr);
	eAddr = eAddr + 1;
	value[eAddr] = EEPROM.read(eAddr);
	eAddr = eAddr + 1;
	value[eAddr] = EEPROM.read(eAddr);
	eAddr = eAddr + 1;
	value[eAddr] = EEPROM.read(eAddr);

  sprintf(OTAIPAddress, "%d.%d.%d.%d", value[0], value[1], value[2], value[3]);
	return;
}

byte getRoomNumber() {
  byte roomNumber = EEPROM.read(5);
  return roomNumber;
}

