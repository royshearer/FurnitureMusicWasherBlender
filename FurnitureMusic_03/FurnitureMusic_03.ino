// Furniture Music washing machine and blender control box
// by Jen Sykes and Roy Shearer for Yuri Suzuki
// based on existing hardware design, rebuilt by James Gaffney
// Glasgow, October 2019
//
// for Teensy 3.2 as Serial+MIDIx16 and AccelStepper library
// Receives MIDI note on and note off messages and translates them into stepper movements
// to control variable AC voltage to washing machine and blender motors. Thermistors serve
// as thermal safety cutouts in machines and control box (ensure sensors are enabled in the
// Therm tab). For some reason the enable pins for the stepper motors work in reverse: calling
// stepper.enableOutputs() actually disables the motor, and stepper.disableOutputs() actually
// enables the motor.
// Washing machine notes: 43,48,55,60
// Blender notes: 67, 72, 79, 84
// Zero the washing machine stepper: 40
// Zero the blender stepper: 64 (do this periodically in the composition in case the blender motor drifts)

//global variables
//washer stepper M1
#define stepPinM1 4
#define dirPinM1 5
#define enablePinM1 23
//blender stepper M2
#define stepPinM2 6
#define dirPinM2 7
#define enablePinM2 22
#define relayInput01 2 // washing machine power
#define relayInput02 1 // blender power - note pin/numbering discrepeancy, this is correct
#define relayInput03 3 // stepper power - note pin/numbering discrepeancy, this is correct
boolean stepperMotor01Enable = false; // stepper1 enable flag
boolean stepperMotor02Enable = false; // stepper2 enable flag
int posW = 0; //washer positions
int posB = 0; //blender positions

#include <AccelStepper.h> // stepper lib import

//stepper lib defines
//washing machine
AccelStepper stepperMotor01(1, stepPinM1, dirPinM1);

//blender
AccelStepper stepperMotor02(1, stepPinM2, dirPinM2);

boolean washerTriggered = false;
boolean blenderTriggered = false;


void setup() {
  Serial.println("SETUP");
  //Teensy visual output
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  Serial.begin(115200);
  midiSetup();
  relaySetup();
  stepperSetup();
}

void loop() {
//  Serial.println("LOOP");
  usbMIDI.read(); //read MIDI messages
  thermoControl(); //thermo control safety  backup.
//  pollLimitSwitches();
  pollMotorFinished();
  setAppliancePower();
  updateSteppers();
  delay(1); // Wait 1 milliseconds for next reading as control CPU
}

void pollMotorFinished() {
  // if motor finishes moving and appliance is not yet powered on, set flag to power it on.
  if (washerTriggered == false && abs(stepperMotor01.distanceToGo()) == 1) {
    washerTriggered = true;
    Serial.println("WASHER TRIGGER");
    stepperMotor01Enable = false; // disable the stepper flag
  }
  if (blenderTriggered == false && abs(stepperMotor02.distanceToGo()) == 1) {
    blenderTriggered = true;
    Serial.println("BLENDER TRIGGER");
    stepperMotor02Enable = false; // disable the stepper flag
  }
}

void setAppliancePower() {
  if (washerTriggered) { //if trigger flag is TRUE
    //close relay and start voltage control of motor
    digitalWrite(relayInput01, LOW);
  }
  else {
    digitalWrite(relayInput01, HIGH); // open relay
//    stepperMotor01Enable = false; // disable the stepper flag
  }

  if (blenderTriggered) { //if zeroing finished execute loop!
    //release relay and start voltage control of motor
    digitalWrite(relayInput02, LOW);
  }
  else {
    digitalWrite(relayInput02, HIGH); // open relay
//    stepperMotor02Enable = false; // disable the stepper flag
  }
}
