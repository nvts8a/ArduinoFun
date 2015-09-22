// Light Switch Reg Config
int  clckPin = 2;
int  ltchPin = 3;
int  dataPin = 4;
byte regData = 0;

void setup() {
  // Debug
  Serial.begin(9600);

  // Light Switch Reg
  pinMode(dataPin, OUTPUT);
  pinMode(clckPin, OUTPUT);
  pinMode(ltchPin, OUTPUT);

  // Temp Meters
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  int lightSensorVal = analogRead(0);
  float tempSensorVal = ( (analogRead(1) * 0.004882814) - 0.5 ) * 180.0 + 32.0;
  
  Serial.print("L: ");
  Serial.print(lightSensorVal);

  Serial.print("  |  T: ");
  Serial.println(tempSensorVal);

  setLightMeter(lightSensorVal);
  setTempMeter(tempSensorVal);
}

void setTempMeter( float tempLevel ) {
  int offset = 8;
  
  if( tempLevel > 100.0 ) {
    setLed(5, offset);
  }
  else if( tempLevel > 87.5 ) {
    setLed(4, offset);
  }
  else if( tempLevel > 80.0 ) {
    setLed(3, offset);
  }
  else if( tempLevel > 77.5 ) {
    setLed(2, offset);
  }
  else {
    setLed(1, offset);
  }
}

void setLightMeter( int lightLevel ) {

  if( lightLevel > 700 )      { setLeds(7); }
  else if( lightLevel > 600 ) { setLeds(6); }
  else if( lightLevel > 500 ) { setLeds(5); }
  else if( lightLevel > 400 ) { setLeds(4); }
  else if( lightLevel > 300 ) { setLeds(3); }
  else if( lightLevel > 200 ) { setLeds(2); }
  else if( lightLevel > 100 ) { setLeds(1); }
  else                        { setLeds(0); } 
}

void shiftWrite(int desiredPin, boolean desiredState) {
  bitWrite(regData, desiredPin, desiredState);
  shiftOut(dataPin, clckPin, MSBFIRST, regData);
  digitalWrite(ltchPin, HIGH);
  digitalWrite(ltchPin, LOW);
}

void setLeds( int level ) {
  for( int i = 0; i <= level; i++ ) {
    shiftWrite( i, HIGH );
  }
  for( int i = 7; i > level; i-- ) {
    shiftWrite( i, LOW );
  }
}

void setLed( int level, int offset ) {
  for( int i = 1 + offset; i <= 5 + offset; i++ ) {
    digitalWrite( i, LOW );
  }
  digitalWrite( level + offset, HIGH );
}

