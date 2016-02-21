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
    Start();
  }
  else {
    delay(20000);
    stagnant+=20000;
  }

}

void start() {
  if (
  BlindAdjustment(int inBrightness, int outBrightness);
  LightAdjustment(int inBrightness, int outBrightness);
}

void BlindAdjustment(int inBrightness, int outBrightness) {
  //long currentTime = millis();
  for(
  
}


