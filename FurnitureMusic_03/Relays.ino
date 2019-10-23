void relaySetup(){
  Serial.println("RELAY SETUP");
  pinMode(relayInput01, OUTPUT); //relay pin configs.
  pinMode(relayInput02, OUTPUT);
  pinMode(relayInput03, OUTPUT);
  
  //initial relay states.
  digitalWrite(relayInput01, HIGH);
  digitalWrite(relayInput02, HIGH);
  digitalWrite(relayInput03, LOW);
}
