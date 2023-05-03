#define LEDG D4
#define LEDY D5
#define LEDR D8
#define LED0 D2
#define LED1 D0
#define LED2 D1

void setup() {
  pinMode(LEDG, OUTPUT);
  pinMode(LEDY, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  rgbOneLamp();
}

void rgbOneLamp(){
  digitalWrite(LEDR, HIGH);
  digitalWrite(LED0, HIGH);
  delay(500);
  digitalWrite(LED1, HIGH);
  digitalWrite(LEDY, HIGH);
  digitalWrite(LED0, LOW);
  digitalWrite(LEDR, LOW);
  delay(500);
  digitalWrite(LED2, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LED1, LOW);
  digitalWrite(LEDY, LOW);
  delay(500);
  digitalWrite(LEDG, LOW);
  digitalWrite(LED2, LOW);
  delay(500);
}

void rgbThreeLamps(){
  digitalWrite(LEDR, HIGH);
  delay(500);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDY, HIGH);
  delay(500);
  digitalWrite(LEDY, LOW);
  digitalWrite(LEDG, HIGH);
  delay(500);
  digitalWrite(LEDG, LOW);
  delay(500);
}
