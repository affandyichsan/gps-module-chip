#ifndef GPS_H
#define GPS_H

#include <Arduino.h>

struct GPSData {
  String latitude;
  String longitude;
  String timestamp;
  String speed;
};

class GPS {
  public:
  void setupGPS();
  bool getGPS(GPSData& data);
};

#endif