void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (4, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(0);
  int aValue = analogRead(2);
  int pValue = analogRead(3);
  Serial.println(pValue);
  if (pValue > 300)
  {
    digitalWrite(4,HIGH);
  }
  else
  {
    digitalWrite(4,LOW);
  }
  // wait for next reading to make it more readable
  delay(100);

}
