void midiSetup() {
  Serial.println("MIDI SETUP");
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OffNoteOff);
  //usbMIDI.setHandleControlChange(myControlChange);
}

//Midi controls
void OnNoteOn(byte channel, byte note, byte velocity) //MIDI Note ON Command
{
  Serial.print("Note On");
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.println();

  //shift motor position (voltage and therefore speed)
  switch (note) {
    //washer
    case 40:
      zeroPositioningWasher();
      break;
    case 43:
      posW = 150;
      stepperMotor01Enable = true;
      break;
    case 48:
      posW = 110;
      stepperMotor01Enable = true;
      break;
    case 55:
      posW = 80;
      stepperMotor01Enable = true;
      break;
    case 60:
      posW = 50;
      stepperMotor01Enable = true;
      break;


    //blender
    case 64:
      zeroPositioningBlender();
      break;
    case 67:
      posB = 70;
      stepperMotor02Enable = true;
      break;
    case 72:
      posB = 60;
      stepperMotor02Enable = true;
      break;
    case 79:
      posB = 50;
      stepperMotor02Enable = true;
      break;
    case 84:
      posB = 40;
      stepperMotor02Enable = true;
      break;
    default://all other notes
      break;

  }
  Serial.print("motorWasherPos");
  Serial.println(posW);

  Serial.print("motorBlenderPos");
  Serial.println(posB);

}

void OffNoteOff(byte channel, byte note, byte velocity) //MIDI Note OFF Command
{
  Serial.print("Note Off");
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.println();
  switch (note) {
    //washer
    case 43:
      washerTriggered = false;//start loop of positions
      break;
    case 48:
      washerTriggered = false;//start loop of positions
      break;
    case 55:
      washerTriggered = false;//start loop of positions
      break;
    case 60:
      washerTriggered = false;//start loop of positions
      break;


    //blender
    case 67:
      blenderTriggered = false;//start loop of positions
      break;
    case 72:
      blenderTriggered = false;//start loop of positions
      break;
    case 79:
      blenderTriggered = false;//start loop of positions
    case 84:
      blenderTriggered = false;//start loop of positions
      break;
    default://all other notes
      break;

      //pos=0; //may not  need this if constant psotions changes.
  }
}
