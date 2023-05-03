#include "DHTesp.h"

#define LEDG D2
#define LEDB D3
#define LEDR D1

const int DHT_PIN = D5;

DHTesp dhtSensor;

void setup() {
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT11);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LEDR, OUTPUT);
}

void activateLamp(char lampCode) {
  switch (lampCode){
    case 'g':
      digitalWrite(LEDG, HIGH);
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDB, LOW);
      break;

    case 'r':
      digitalWrite(LEDG, LOW);
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDB, LOW);
      break;

    case 'b':
      digitalWrite(LEDG, LOW);
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDB, HIGH);
      break;


    default:
      digitalWrite(LEDG, LOW);
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDB, LOW);
  }
}

void setLamp(float temperature) {
  Serial.println(temperature);
  if (temperature <= 36 ) {
    activateLamp('g');
  }else if (temperature >= 36 && temperature <= 40) {
    activateLamp('b');
  }else{
    activateLamp('r');
  }
}


void loop() {
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  Serial.println("---");
  setLamp(data.temperature);
  delay(1000);
}
