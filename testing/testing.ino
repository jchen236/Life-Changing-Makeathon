/*
 * A0 = Motion Senser
 * A1 = Light Senser Outside
 * A2 = Light Senser Insde
 */
int stagnant = 0;
int desiredBrightness = 70;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(1,OUTPUT); //MOTOR
  pinMode(2, OUTPUT);   // LED
}

void loop() {
  // put your main code here, to run repeatedly:
  bool motion = false;
  int motionValue = analogRead(A0); // Pin for motion
  if (motionValue > 600) {
    motion = true; 
  }
 

  if(stagnant >= 300000) {
    Turnoff();
    break;
  }
  else if(motion) {
    stagnant = 0;
    int lightOutside = analogRead(A1);
    int lightInside = analogRead(A2);
    if (desiredBrightness < lightInside + 80) {
      StartBrighten(lightOutside,lightInside);
    }
    else if (desiredBrightness > lightInside - 80) {
      StartUnbrighten(lightOutside,lightInside);
    }
      
    }
  }
  else {
    delay(20000);
    stagnant+=20000;
  }

}

int StartBrighten(outside, inside) {
  
  spinningClockwise = BlindAdjustmentClockwise(int inBrightness, int outBrightness);
  if (desiredBrightness < lightInside + 80)
  {
    LightAdjustment(int inBrightness, int outBrightness);
  }
  
  return spinningBrighten;
}

void LightAdjustment(int inBrightness, int outBrightness) {
  byte brightness;
  int sensorValue  = analogRead (A2);
  insideLight = sensorValue
  turnsAmount = 0; 
  currentTime = millis();
  while (insideLight  < desiredBrigthness) {
    int sensorValue  = analogRead (A2);
    insideLight = sensorValue;
    // set the speed of pin 9:

       analogWrite(4, turns);
       analogWrite (2,turns);

       // change the turnings for next time through the loop:

       turns = turns + turnAmount;

       // stops the speed of the motor from growing, need to determine which speed is most optimal still

       if (turns == 200) { 
           turnAmount = 0;
       }
  
  
}
int BlindAdjustmentClockwise (int insideBrightness, int outsideBrightness)
{
  if (outsideBrightness < 30){
    return 0; 
  }

  int sensorValue  = analogRead (A2);
  insideLight = sensorValue
  turnsAmount = 0; 
  currentTime = millis();
  while (insideLight  < desiredBrigthness) {
    int sensorValue  = analogRead (A2);
    insideLight = sensorValue;
    // set the speed of pin 4 and 2:

       analogWrite(4, turns);
       analogWrite (2,turns);

       // change the turnings for next time through the loop:

       turns = turns + turnAmount;

       // stops the speed of the motor from growing, need to determine which speed is most optimal still

       if (turns == 200) { 
           turnAmount = 0;
       }
  }
}
  postLoopTime = millis();
  return postLoopTime - currentTime; //Returns a positive number to represent time spent spinning clockwise

  
