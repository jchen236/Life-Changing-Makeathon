#include <math.h>
const int thresholdValue = 150;
const int ledPin = 4;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int LSValue = analogRead(0);
  if(LSValue < thresholdValue) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin,LOW);
  }
  Serial.println("the analog read data is ");
  Serial.println(LSValue);
 
}
