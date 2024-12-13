#include "gps.h"
#include <TinyGPS++.h>
#define RXD2 17
#define TXD2 16

HardwareSerial neogps(1);
TinyGPSPlus tinyGps;

void GPS::setupGPS() {
  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("neogps serial initialize");
}

bool GPS::getGPS(GPSData& data) {
  //Can take up to 60 seconds
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 2000;) {
    while (neogps.available() > 0) {
      if (tinyGps.encode(neogps.read())) {
        newData = true;
        break;
      }
    }
  }

  //If newData is true
  if (newData == true) {
    newData = false;

    //float altitude;
    //unsigned long date, time, speed, satellites;

    if(tinyGps.location.isUpdated() && tinyGps.time.isUpdated()) {
      if (tinyGps.location.isValid()) {
        data.latitude = String(tinyGps.location.lat(), 6); // Latitude in degrees (double)
        data.longitude = String(tinyGps.location.lng(), 6); // Longitude in degrees (double)
      }

      if (tinyGps.speed.isValid()) {
        data.speed = String(tinyGps.speed.kmph(), 3);
      }

      // Mendapatkan tanggal
      int year = tinyGps.date.year();
      int month = tinyGps.date.month();
      int day = tinyGps.date.day();

      // Mendapatkan waktu
      int hour = tinyGps.time.hour();
      int minute = tinyGps.time.minute();
      int second = tinyGps.time.second();

      // Membuat string timestamp dengan format "yyyy-M-d H:mm:ss"
      char timestampChar[20];
      sprintf(timestampChar, "%04d-%d-%d %02d:%02d:%02d", year, month, day, hour, minute, second);

      // Mengonversi timestamp ke string (C++11 onwards)
      data.timestamp = String(timestampChar);

      //altitude = gps.altitude.meters(); // Altitude in meters (double)
      //date = gps.date.value(); // Raw date in DDMMYY format (u32)
      //time = gps.time.value(); // Raw time in HHMMSSCC format (u32)
      //speed = gps.speed.kmph();

      return true;
    }
    return false;
  }
  return false;
}