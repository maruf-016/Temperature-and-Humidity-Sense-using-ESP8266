#define BLYNK_PRINT Serial    
#include <SPI.h>
#include <ESP8266WiFi.h>       
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "gK6W0QJJGJ_byUfwoPjaDoOm_x7s3qaa";
char ssid[] = "Hell Room";  
char pass[] = "203203203";
#define DHTPIN 5
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void setup() {
  Serial.begin(9600); 
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  
  timer.setInterval(2000, sendSensor);
}

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }  
  Blynk.virtualWrite(V3, h); 
  Blynk.virtualWrite(V2, t);
}


void loop() {
  Blynk.run(); 
  timer.run(); 

}
