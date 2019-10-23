#define washingMotorThermistor 14
#define washingAmbientThermistor 15
#define blenderThermistor 16
#define controlBoxThermistor 17

// temperature thresholds - arbitrarily set to just above ambient (~500)
int wThreshold = 700;
int aThreshold = 700;
int bThreshold = 700;
int cThreshold = 700;

float lastWTherm;
float lastATherm;
float lastBTherm;
float lastCTherm;
float smooth = 0.001;

void thermoControl() {
  //smoothing
  float wTherm = ((1 - smooth) * lastWTherm) + (smooth * analogRead(washingMotorThermistor));
  float aTherm = ((1 - smooth) * lastATherm) + (smooth * analogRead(washingAmbientThermistor));
  float bTherm = ((1 - smooth) * lastBTherm) + (smooth * analogRead(blenderThermistor));
  float cTherm = ((1 - smooth) * lastCTherm) + (smooth * analogRead(controlBoxThermistor));
  lastWTherm = wTherm;
  lastATherm = aTherm;
  lastBTherm = bTherm;
  lastCTherm = cTherm;

  //  Serial print thermistor values
  Serial.print(int(wTherm));
  Serial.print(", ");
  Serial.print(int(aTherm));
  Serial.print(", ");
  Serial.print(int(bTherm));
  Serial.print(", ");
  Serial.print(int(cTherm));
  Serial.println(". ");


  //need to update threshold values.
  if ((wTherm > wThreshold) || (aTherm > aThreshold)) { //both housed inside washing machine
    //flip relay disconnect power to machine
    digitalWrite(relayInput01, HIGH);
  }

  if (bTherm > bThreshold) {
    //flip relay disconnect power to machine
    digitalWrite(relayInput02, HIGH);
  }

  if (cTherm > cThreshold) {
    //flip relay disconnect power to control box and machines
    digitalWrite(relayInput01, HIGH);
    digitalWrite(relayInput02, HIGH);
    digitalWrite(relayInput03, HIGH);
  }
}
