#include "DHT.h"
#define LEDPIN 11
#define DHTPIN 21
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Setup serial for monitor and Setup Serial1 for BlueTooth
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  dht.begin();
}

void loop() {
  // Process commands from bluetooth first.
  if(Serial1.available() > 0){
    String str = Serial1.readString().substring(0);
    Serial.println(str);
    if(str == "LED_ON"){
      digitalWrite(LEDPIN, HIGH);
      Serial.println("LED ON");
      Serial1.println("LED ON");
    } else if(str == "LED_OFF"){
      digitalWrite(LEDPIN, LOW);
      Serial.println("LED OFF");
      Serial1.println("LED OFF");
    } else if(str == "DHT"){
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      float f = dht.readTemperature(true);
      if (isnan(h) || isnan(t) || isnan(f)) {
        Serial1.println(F("Failed to read from DHT sensor!"));
        return;
      }
      float hif = dht.computeHeatIndex(f, h);
      float hic = dht.computeHeatIndex(t, h, false);
      Serial.println("Send DHT");
      Serial1.print(F("Humidity: "));
      Serial1.print(h);
      Serial1.print(F("%  Temperature: "));
      Serial1.print(t);
      Serial1.print(F("C "));
      Serial1.print(f);
      Serial1.print(F("F Heat index: "));
      Serial1.print(hic);
      Serial1.print(F("C "));
      Serial1.print(hif);
      Serial1.println(F("F"));
    }
  }
}