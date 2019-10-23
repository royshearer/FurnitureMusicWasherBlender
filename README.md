# FurnitureMusicWasherBlender
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

# Thermal cutouts
these thresholds are set in the Therm tab - deafult is 700, ambient is 500.

# midi notes and voltages/washer and blender speeds
These are set in the swtich case statements in the midi tab. the values in the note on routine and note off routine must match.
adjusting the posW and posB values will adjust the positions the motor moves to and thus the voltage sent to the washer and blender motors

# 
