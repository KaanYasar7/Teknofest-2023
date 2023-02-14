#include "LoRa_E32.h"
#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(10, 11);
LoRa_E32 e32ttl(&mySerial);
 

 
byte SensorSays = 1;
const byte Frekanslar[] = { 1 };
byte mevcutLora = 0;
 
struct Signal {
  char type[10] = "Urfa63";
  byte id;
  byte lat[6];
  byte lng[6];
  byte volt[6];
} data;
 
 
 
void setup() {

  Serial.begin(9600);
  e32ttl.begin();
  delay(500);
}
 
void loop() { 
 
    for (mevcutLora = 0; mevcutLora < SensorSays; mevcutLora++) {
      int deger1 = mevcutLora + 1;
      String text1 = ". Sensörün değerleri alınıyor...";
      String sum1 = deger1 + text1;
      Serial.println(sum1);
 
      ResponseStatus rs = e32ttl.sendFixedMessage(0, Frekanslar[mevcutLora], 23, &data, sizeof(Signal));
      Serial.println(rs.getResponseDescription());
 
      delay(750);
    }   
}