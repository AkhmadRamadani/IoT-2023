#include "DHTesp.h"
#include <LCD_I2C.h>

#define LEDG D7
#define LEDB D5
#define LEDR D6

#define triggerPin D4
#define echoPin D8

float duration = 0;
float jarak = 0;
float temperature = 0;
float humidity = 0;

const int DHT_PIN = D3;

DHTesp dhtSensor;
LCD_I2C lcd(0x27, 16, 2);


void setup() {
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT11);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LEDR, OUTPUT);
  lcd.begin();
  lcd.backlight();
}

void activateLamp(char lampCode) {
  switch (lampCode) {
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

void setLampUsingSonar(float value) {
  Serial.println("======================");
  Serial.println("Value of Sonar Sensor Given");
  Serial.println(value);
  Serial.println("======================");
  char str[10];
  dtostrf(value, 6, 2, str);
  lcd.setCursor(0, 1);
  lcd.printf("Sonar: %s", str);

  if (value <= 5) {
    activateLamp('r');
  } else if (value > 5 && value <= 10) {
    activateLamp('g');
  } else {
    activateLamp('b');
  }
}


void setLampUsingDHT(float value) {
  Serial.println("======================");
  Serial.println("Value of DHT Sensor Given");
  Serial.println(value);
  Serial.println("======================");
  char str[10];
  dtostrf(value, 6, 2, str);
  lcd.setCursor(0, 0);
  lcd.printf("DHT: %s", str);

  if (value <= 36) {
    activateLamp('g');
  } else if (value >= 36 && value <= 40) {
    activateLamp('b');
  } else {
    activateLamp('r');
  }
}

void loopOfDHT() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  if ((temperature != data.temperature) || (humidity != data.humidity)) {
    Serial.println("DHT Change Lamp");
    Serial.println("Temp: " + String(data.temperature, 2) + "°C");
    Serial.println("Humidity: " + String(data.humidity, 1) + "%");
    Serial.println("---");
    temperature = data.temperature;
    humidity = data.humidity;
    setLampUsingDHT(data.temperature);
  }
  delay(1000);
}

void loopOfSonar() {
  float localDuration = 0;
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  localDuration = pulseIn(echoPin, HIGH);
  if (duration != localDuration) {
    Serial.println("Sonar Change Lamp");
    duration = localDuration;
    jarak = duration * 0.034 / 2;
    Serial.print(jarak);
    Serial.println(" cm");
    setLampUsingSonar(jarak);
  }
  delay(1000);
}

void loop() {
  loopOfSonar();
  loopOfDHT();
}