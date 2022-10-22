#include <TinyGPS.h>
TinyGPS gps;
#include <SoftwareSerial.h>
SoftwareSerial ss(10, 11); // Rx Tx

void setup() {
  Serial.begin(9600);//Serial Communication Speed
  ss.begin(9600);//Serial Port Speed

}

void loop() {
  smartdelay(1000);
  Serial.println();

  uint8_t sat = gps.satellites();// Identification of Satellite Number Data
  Serial.print("Uydu Sayısı:"); Serial.println(sat); //Printing Satellite Data

  float flat, flon; // Defining Latitude and Longitude Data
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);
  Serial.print("Latitude:"); Serial.println(flat, 6); //Printing Latitude Data
  Serial.print("Longitude:"); Serial.println(flon, 6); //Printing Longitude Data

  int alt = gps.f_altitude(); // Defining Altitude Data
  Serial.print("Altitude:"); Serial.println(alt); // Printing Altitude Data

  int spd = gps.f_speed_kmph(); //Defining Speed Data
  Serial.print("Speed:"); Serial.println(spd);// Printing of Speed Data

  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age2;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths);
  Serial.print("Year:"); Serial.println(year);
  Serial.print("Month:"); Serial.println(month);
  Serial.print("Day:"); Serial.println(day);

  Serial.print("Hour:"); Serial.println(hour+3);
  Serial.print("Minute:"); Serial.println(minute);
  Serial.print("Second:"); Serial.println(second);
  Serial.print("----------------------------------------------------------------------------");
}


static void smartdelay(unsigned long ms) 
{
  unsigned long start = millis();
  do
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
