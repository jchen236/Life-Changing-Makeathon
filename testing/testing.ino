/*
 * A0 = Motion Senser
 * A1 = Light Senser Outside
 * A2 = Light Senser Insde
 */
int stagnant = 0; // amount of time with no activity
int desiredBrightness = 70; // desired brightness (set by user)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(1,OUTPUT); //MOTOR
  pinMode(2, OUTPUT);  // MOTOR 2
  pinMode (3, OUTPUT); //LED
}

void loop() {
  // put your main code here, to run repeatedly:
  bool motion = false; 
  int motionValue = analogRead(A0); // Pin for motion
  if (motionValue > 600) {
    motion = true; //If motion is detected, set motion to true
  }
 

  if(stagnant >= 300000) {
    Turnoff(); //Stop the processes if there is no movement in the room
    break;
  }
  else if(motion) {
    stagnant = 0;
    int lightOutside = analogRead(A1); // Measure of Light outside
    int lightInside = analogRead(A2); //Measure of Light inside
    if (desiredBrightness < lightInside + 80) {
      StartBrighten(lightOutside,lightInside); //Brighten the light inside the house
    }
    else if (desiredBrightness > lightInside - 80) {
      StartUnbrighten(lightOutside,lightInside); //Lower brightness in the house 
    }
      
    
  }
  else {
    delay(20000);
    stagnant+=20000;
  }

}
/*
 * Brighten the House
 * Parameters: Brightness Outside
 */

int StartBrighten(int outside) {
  
  spinningClockwise = BlindAdjustmentClockwise(outside); //Adjust the blinds and keep track of how much time they spun clockwise
  if (desiredBrightness < lightInside + 80)
  {
    LightAdjustment(); //Adjust Light if desired threshold has not been reached
  }
  return spinningBrighten;
}
/*
 * This method will adjust the light in the house to reach the desired threshold if the light outside was not enough 
 * No Parameters
 */
void LightAdjustment() {
  int brightness;
  int sensorValue  = analogRead (A2);
  insideLight = sensorValue;
  brightnessIncrease = 1; //Increase brightness by 1 every iteration
  while (insideLight  < desiredBrigthness) {
    int sensorValue  = analogRead (A2);
    insideLight = sensorValue;
    // set the speed of pin 9:

       analogWrite(3, light); //change brightness of light

       // change the turnings for next time through the loop:

       light= light + brightnessIncrease; //increase brightness if still needed

       // stops the speed of the motor from growing, need to determine which speed is most optimal still

       if (brightnessIncrease == 200) { 
           brightnessIncrease = 0;
       }
  
  
}
/*
 * Open the Blinds and keep track of the time the motors are spinning
 * Paramters: outside Brigtness
 * Returns: Time motor is spinning
 */
int BlindAdjustmentClockwise (int outsideBrightness)
{
  if (outsideBrightness < 30){
    return 0; //if not enough light outside to substantially brighten up room, no point in opening blinds
  }

  int sensorValue  = analogRead (A2);
  insideLight = sensorValue;
  turnAmount = 1; //increment to incrase rotation every iteration
  currentTime = millis(); //Keep Track of time spinning clockwise
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
  postLoopTime = millis(); //Keep track of time that actually spun
  return postLoopTime - currentTime; //Returns a positive number to represent time spent spinning clockwise

}
  
  
