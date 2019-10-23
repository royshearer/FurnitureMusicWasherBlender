/*
  STEPPER MOTOR INFO
  power current rating 1.2amp Vref should be set to 0.84
  1.8° per step
  360º  = 200 STEPSPERREVOLUTION(SPR) WHEN FULL STEPS
*/


#define maxRotation_switch01 8
#define maxRotation_switch02 9

void stepperSetup() {
  Serial.println("STEPPER SETUP");
  pinMode(maxRotation_switch01, INPUT_PULLUP);//this is pin 8
  pinMode(maxRotation_switch02, INPUT_PULLUP);//this is pin 9
  pinMode(stepPinM1, OUTPUT);
  pinMode(dirPinM1, OUTPUT);
  pinMode(stepPinM2, OUTPUT);
  pinMode(dirPinM2, OUTPUT);
  stepperMotor01.setEnablePin(enablePinM1);
  stepperMotor02.setEnablePin(enablePinM2);

  //Zeroing
  zeroPositioningWasher(); //check if washing machine  stepper at zero
  zeroPositioningBlender(); //check if blender stepper at zero
}

void updateSteppers() {
    //set speed, accel , startPos
  //washer
  stepperMotor01.setMaxSpeed(1000.0); //over 1000 unreliable
  stepperMotor01.setAcceleration(5000.0);
  //blender
  stepperMotor02.setMaxSpeed(1000.0); //over 1000 unreliable
  stepperMotor02.setAcceleration(3000.0);
  
  //run motors keep outside of relay triggers so can see running even when power not going to amchines.
  //washer
  if (stepperMotor01Enable == true) { // if stepper flag is set
    stepperMotor01.disableOutputs(); // enable stepper
//    Serial.println("motor01 On");
    stepperMotor01.moveTo(posW); // update position //moveTo takes into account absolute last position so will know a lower number is backwards etc
  }
  else {
    stepperMotor01.enableOutputs(); // else disable the stepper
//    Serial.println("motor01 Off");
  }
  stepperMotor01.run(); // move stepper

  //blender
  if (stepperMotor02Enable == true) { // if stepper flag is set
    stepperMotor02.disableOutputs(); // enable stepper
//    Serial.println("motor02 On");
    stepperMotor02.moveTo(posB); // update position //moveTo takes into account absolute last position so will know a lower number is backwards etc
  }
  else {
    stepperMotor02.enableOutputs(); // else disable the stepper
//    Serial.println("motor02 Off");
  }
  stepperMotor02.run(); // move stepper
}
