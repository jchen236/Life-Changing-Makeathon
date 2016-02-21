/*
 * A0 = Motion Senser
 * A1 = Light Senser Outside
 * A2 = Light Senser Insde
 */
int stagnant = 0; // amount of time with no activity
int desiredBrightness = 550; // desired brightness (set by user)
int spinningClockwise;
int light = 0;
int rotationCounter;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4,OUTPUT); //MOTOR
  pinMode(2, OUTPUT);  // MOTOR 2
  pinMode (6, OUTPUT); //LED
}

void loop() {
  // put your main code here, to run repeatedly:
  bool motion = false; 
  int motionValue = analogRead(A0); // Pin for motion
  Serial.println(motionValue);
  if (motionValue > 600) {
    motion = true; //If motion is detected, set motion to true
  }
 

  if(stagnant >= 300000) {
    Serial.end();
  }
  else if(motion) {
    stagnant = 0;
    int lightOutside = luxEquation(analogRead(A1)); // Measure of Light outside
    int lightInside = luxEquation(analogRead(A2)); //Measure of Light inside
    if (desiredBrightness > lightInside + 80) {
      StartBrighten(lightInside, lightOutside); //Brighten the light inside the house
    }
    else if (desiredBrightness < lightInside - 80) {
      //StartUnbrighten(lightInside, lightOutside); //Lower brightness in the house 
    }
      
    
  }
  else {
    delay(2000);
    stagnant+=20000;
  }

}
/*
 * Open the Blinds and keep track of the time the motors are spinning
 * Paramters: outside Brigtness
 * Returns: Time motor is spinning
 */
int BlindAdjustmentClockwise (int outsideBrightness)
{
  if (outsideBrightness > 30){
    Serial.println("eee");
    return 0; //if not enough light outside to substantially brighten up room, no point in opening blinds
  }
  Serial.println("in blindclockwise");

  int sensorValue  = analogRead (A2);
  int insideLight = luxEquation (sensorValue);
  int turns = 0;
  int turnAmount = 1; //increment to incrase rotation every iteration
  int currentTime = millis(); //Keep Track of time spinning clockwise
  while (insideLight  < desiredBrightness) {
    int sensorValue  = analogRead (A2);
    insideLight = luxEquation(sensorValue);
    // set the speed of pin 4 and 2:

       analogWrite(4, turns);
       analogWrite (2,turns);

       // change the turnings for next time through the loop:

       turns = turns + turnAmount;

       // stops the speed of the motor from growing, need to determine which speed is most optimal still

       if (turns == 200) { 
           delay(2000);
           turnAmount = -1;
       }
       if (turns == -1)
       {
        return 1;
       }
       
  }
  int postLoopTime = millis(); //Keep track of time that actually spun
  return postLoopTime - currentTime; //Returns a positive number to represent time spent spinning clockwise

}
/*
int BlindAdjustmentCounterclockwise (int outsideBrightness)
{
  if (outsideBrightness < 30){
    return 0; //if not enough light outside to substantially brighten up room, no point in opening blinds
  }

  int sensorValue  = analogRead (A2);
  int insideLight = luxEquation(sensorValue);
  int turns = 0;
  int turnAmount = -1; //increment to increase rotation every iteration
  int currentTime = millis(); //Keep Track of time spinning clockwise
  while (insideLight  < desiredBrightness) {
    int sensorValue  = analogRead (A2);
    insideLight = luxEquation(sensorValue);
    // set the speed of pin 4 and 2:

       analogWrite(4, turns);
       analogWrite (2,turns);

       // change the turnings for next time through the loop:

       turns = turns + turnAmount;

       // stops the speed of the motor from growing, need to determine which speed is most optimal still

       if (turns == -60) { 
           delay(3000);'
           return 1;
       }
       
  }
  int postLoopTime = millis(); //Keep track of time that actually spun
  return postLoopTime - currentTime; //Returns a positive number to represent time spent spinning clockwise

}
*/
/*
 * Brighten the House
 * Parameters: Brightness Outside
 */

int StartBrighten(int inside, int outside) {

  Serial.println("hi");
  spinningClockwise = BlindAdjustmentClockwise(outside); //Adjust the blinds and keep track of how much time they spun clockwise
  if (desiredBrightness > inside + 80)
  {
    IncreaseLight(); //Adjust Light if desired threshold has not been reached
  }
  return spinningClockwise;
}
/*
int StartUnbrighten(int inside, int outside) {

  int spinningCounterclockwise;
  DecreaseLight();  //Adjust the blinds and keep track of how much time they spun clockwise
  if (desiredBrightness < inside + 80)
  {
    spinningCounterclockwise = BlindAdjustmentCounterclockwise(outside); //Adjust Light if desired threshold has not been reached
  }
  return spinningCounterclockwise;
}
*/
/*
 * This method will adjust the light in the house to reach the desired threshold if the light outside was not enough 
 * No Parameters
 */
int IncreaseLight() {
  int sensorValue  = analogRead (A2);
  int insideLight = sensorValue;
  int brightnessIncrease = 1; //Increase brightness by 1 every iteration
  while (insideLight  < desiredBrightness) {
    sensorValue  = analogRead (A2);
    insideLight = sensorValue;
    // set the the brightness:

       analogWrite(6, light); //change brightness of light

       // change the turnings for next time through the loop:

       light= light + brightnessIncrease; //increase brightness if still needed
       delay(20);

       if (light == 250) {
           brightnessIncrease = -1;
       }

       if (light == -1)
       {
        return 1;
       }
  
  }
}
/*
int DecreaseLight() {
  int sensorValue  = analogRead (A2);
  int insideLight = sensorValue;
  int brightnessDecrease = -1; //Decrease brightness by 1 every iteration
  while (insideLight  > desiredBrightness) {
    sensorValue  = analogRead (A2);
    insideLight = sensorValue;
    // set the the brightness:

       analogWrite(6, light); //change brightness of light

       // change the turnings for next time through the loop:

       light= light + brightnessDecrease; //increase brightness if still needed
       delay(20);

       if (light == 0) {
           return 1;
       }
  }
}
*/

double luxEquation(int light)
{
  light*light*light*-.000002 + .004 * light * light + .2385 * light + 17.738;
}

  
  
