#define triggerPin D6
#define echoPin D5

#define LEDG D3
#define LEDB D4
#define LEDR D2

void setup() {
  Serial.begin(115200);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LEDR, OUTPUT);
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
  Serial.println("======================")
  Serial.println("Value of Sonar Sensor Given")
  Serial.println(value);
  Serial.println("======================")

  if (value <= 5) {
    activateLamp('r');
  } else if (value > 5 && value <= 10) {
    activateLamp('g');
  } else {
    activateLamp('b');
  }
}


void setLampUsingDHT(float value) {
  Serial.println("======================")
  Serial.println("Value of DHT Sensor Given")
  Serial.println(value);
  Serial.println("======================")

  if (value <= 36 ) {
    activateLamp('g');
  }else if (value >= 36 && value <= 40) {
    activateLamp('b');
  }else{
    activateLamp('r');
  }
}


void loop() {
  long duration, jarak;
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  jarak = duration * 0.034 / 2;
  Serial.print(jarak);
  Serial.println(" cm");
  setLamp(jarak);
  delay(1000);
}