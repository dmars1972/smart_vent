#include "SmartTemp.h"

SmartTemp::SmartTemp()
{
  sensors.begin();

  if(sensors.getDeviceCount() > 0)
    sensorExists = true;
  else
    sensorExists = false;
}

