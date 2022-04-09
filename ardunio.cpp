
#include "DHT.h"


#define DHTTYPE DHT11
#define DHTPOWER 7
#define DHTGROUND 4
#define DHTPIN 6
#define intpin 2
#define yellow 13
#define red 12
#define green 11
#define blue 10

#define limit_15 15
#define limit_20 20
float t = 0;
float h = 0;
void read_datas();

bool flag = false;

DHT dht(DHTPIN, DHTTYPE);


void isr_(){
  flag =  true ;
  }

void work_leds() {
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);

  if (t < limit_15) {
    digitalWrite(red, HIGH);
  }
  else if (t < limit_20) {
    digitalWrite(yellow, HIGH);
  }
  else {
    digitalWrite(green, HIGH);
  }
}

void read_datas() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  
  if (isnan(h) || isnan(t) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
}



void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  pinMode(DHTPOWER, OUTPUT);
  pinMode(DHTGROUND, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  dht.begin();
  attachInterrupt(digitalPinToInterrupt(intpin), isr_, RISING);
}


void loop() {

  if (flag){
    flag = false;
    digitalWrite(blue, HIGH);
    delay(1000);
    digitalWrite(blue, LOW);
  }
  read_datas();
  work_leds();
  delay(2000);


}