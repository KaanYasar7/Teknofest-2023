#include <TinyGPS.h>
TinyGPS gps;
#include <SoftwareSerial.h>
SoftwareSerial ss(10, 11); // Rx Tx

void setup() {
  Serial.begin(9600);//Seri Haberleşme Hızı
  ss.begin(9600);//Seri Port Hızı

}

void loop() {
  smartdelay(1000);
  Serial.println();

  uint8_t sat = gps.satellites();// Uydu Sayısının Verilerinin Tanımlanması
  Serial.print("Uydu Sayısı:"); Serial.println(sat); //Uydu Verilerinin Yazdırlırması

  float flat, flon; // Enlem Ve Boylam Verilerinin Tanımlanması
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);
  Serial.print("Enlem:"); Serial.println(flat, 6); //Enlem Verilerinin Yazdırlması
  Serial.print("Boylam:"); Serial.println(flon, 6); //Boylam Verilerinin Yazdırlması

  int alt = gps.f_altitude(); // İrtifa Verilerinin Tanımlanması
  Serial.print("İrtifa:"); Serial.println(alt); // İrtifa Verilerinin Yazdırlması

  int spd = gps.f_speed_kmph(); //Hız Verilerininin Tanımlanması
  Serial.print("Hız:"); Serial.println(spd);// Hız Verilerinin Yazdırlaması

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
