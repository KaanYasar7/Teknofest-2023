#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP280_ADDRESS 0x76
Adafruit_BMP280 bmp;  // I2C
int startAltitude = 0;
int sonH = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  /* Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));*/
  //Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */

  sonH = (bmp.readAltitude(851) - startAltitude);
  Serial.println(sonH);
  Serial.println(" m");
  Serial.println();
  delay(1000);
}

void Bmp280() {
  while (!Serial) delay(100);  // wait for native usb
  Serial.println(F("BMP280 test"));
  unsigned status;
  status = bmp.begin(BMP280_ADDRESS);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    Serial.print("SensorID was: 0x");
    Serial.println(bmp.sensorID(), 16);

    while (1) delay(10);
    /* Default settings from datasheet. */
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
    startAltitude = bmp.readAltitude(851);
  }
}
