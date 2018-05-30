#ifndef _SMART_TEMP
#define _SMART_TEMP

#include <DallasTemperature.h>

const int DS_PIN = 5;

class SmartTemp
{
  private:
    OneWire oneWire = OneWire(DS_PIN);
    DallasTemperature sensors = DallasTemperature(&oneWire);
    DeviceAddress tempAddress;

    bool sensorExists;
  public:
    SmartTemp();

    bool hasSensor() { return sensorExists; };
};

#endif
