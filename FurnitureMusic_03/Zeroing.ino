//zeroing variables
int move_finished = 1; // Used to check if move is completed
long initial_zeroing = -1; // Used to Home Stepper at startup
long initial_zeroing02 = -1; // Used to Home Stepper at startup

//zero positioning at beginning of turn ON.
void zeroPositioningWasher() {
  //set speed, accel , startPos
  //washer
  stepperMotor01.setMaxSpeed(800.0); //over 1000 unreliable
  stepperMotor01.setAcceleration(1000.0);
  stepperMotor01.disableOutputs();
  Serial.println("motor01 On");

  // Start Zeroing procedure of Stepper Motor at startup
  Serial.println("Stepper 1 is Zeroing . . . . . . . . . . . ");//might not print if in while loop quickly
  while (digitalRead(maxRotation_switch01)) {  // Make the Stepper move CCW until the switch is activated
    stepperMotor01.moveTo(initial_zeroing);  // Set the position to move to
    initial_zeroing -= 10; // Decrease by 1 for next move if needed //move 10 steps a time
    stepperMotor01.run();  // Start moving the stepper
    delay(5);
  }

  Serial.println("Switch 1 Hit . . . . . . . . . . . ");
  //reset speed ,accel etc variables slow down a bit as it moves off the switch
  //washer
  stepperMotor01.setCurrentPosition(0);  // Set the current position as zero for now
  initial_zeroing = 1;

  while (!digitalRead(maxRotation_switch01)) { // Make the Stepper move CW until the switch is deactivated
    stepperMotor01.moveTo(initial_zeroing);
    stepperMotor01.run();
    initial_zeroing += 1; //move 10 steps a time
    delay(1);
  }

  stepperMotor01.setCurrentPosition(0);
  Serial.println("Motor 1 Zeroing Completed");
  Serial.println("");
  stepperMotor01.enableOutputs();
  Serial.println("motor01 Off");
}

//zero positioning at beginning of turn ON.
void zeroPositioningBlender() {
  //blender
  stepperMotor02.setMaxSpeed(800.0); //over 1000 unreliable
  stepperMotor02.setAcceleration(1000.0);
  stepperMotor02.disableOutputs();
  Serial.println("motor02 On");

  // Start Zeroing procedure of Stepper Motor at startup
  Serial.println("Stepper 2 is Zeroing . . . . . . . . . . . ");//might not print if in while loop quickly
  while (digitalRead(maxRotation_switch02)) {  // Make the Stepper move CCW until the switch is activated
    stepperMotor02.moveTo(initial_zeroing02);  // Set the position to move to
    initial_zeroing02 -= 10; // Decrease by 1 for next move if needed //move 10 steps a time
    stepperMotor02.run();  // Start moving the stepper
    delay(5);
  }

  Serial.println("Switch 2 Hit . . . . . . . . . . . ");
  //reset speed ,accel etc variables slow down a bit as it moves off the switch
  //washer
  stepperMotor02.setCurrentPosition(0);  // Set the current position as zero for now
  initial_zeroing02 = 1;

  while (!digitalRead(maxRotation_switch02)) { // Make the Stepper move CW until the switch is deactivated
    stepperMotor02.moveTo(initial_zeroing02);
    stepperMotor02.run();
    initial_zeroing02 += 1; //move 10 steps a time
    delay(1);
  }

  stepperMotor02.setCurrentPosition(0);
  Serial.println("Motor 2 Zeroing Completed");
  Serial.println("");
  stepperMotor02.disableOutputs();
  Serial.println("motor02 Off");
}

void pollLimitSwitches() {
  if (!digitalRead(maxRotation_switch01)) {
  stepperMotor01.setCurrentPosition(0);
    Serial.println("Motor 1 Zeroing Completed");
  }
  if (!digitalRead(maxRotation_switch02)) {
  stepperMotor02.setCurrentPosition(0);
    Serial.println("Motor 2 Zeroing Completed");
  }

}
