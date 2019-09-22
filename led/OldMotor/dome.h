
// Motor Dome
int dir1PinDome = 22;
int dir2PinDome = 24;
int speedPinDome = 44; // Needs to be a PWM pin to be able to control motor speed

int motorSpeedDome = 80;

enum PinAssignments {
  encoderPinA = 19,
  encoderPinB = 18,
  clearButton = 20
};

volatile int encoderPos = 0;
unsigned int lastReportedPos = 1;

boolean A_set = false;
boolean B_set = false;

// Interrupt on A changing state
void doEncoderA(){
  // Test transition
  A_set = digitalRead(encoderPinA) == HIGH;
  // and adjust counter + if A leads B
  encoderPos += (A_set != B_set) ? +1 : -1;
}

// Interrupt on B changing state
void doEncoderB(){
  // Test transition
  B_set = digitalRead(encoderPinB) == HIGH;
  // and adjust counter + if B follows A
  encoderPos += (A_set == B_set) ? +1 : -1;
}

void enableDomeEncoder()
{
// encoder pin on interrupt 0 (pin 19)
  attachInterrupt(4, doEncoderA, CHANGE);
// encoder pin on interrupt 1 (pin 18)
  attachInterrupt(5, doEncoderB, CHANGE);
}
void disableDomeEncoder()
{
// encoder pin on interrupt 0 (pin 19)
  detachInterrupt(4);
// encoder pin on interrupt 1 (pin 18)
  detachInterrupt(5);
}

void domeCW()
{
  analogWrite(speedPinDome, motorSpeedDome);

  digitalWrite(dir1PinDome, LOW);
  digitalWrite(dir2PinDome, HIGH);  
}
void domeCCW()
{
  analogWrite(speedPinDome, motorSpeedDome);
  digitalWrite(dir1PinDome, HIGH);
  digitalWrite(dir2PinDome, LOW);
}
void domeBreak()
{
  digitalWrite(dir1PinDome, LOW);
  digitalWrite(dir2PinDome, LOW);
}

void domeSetPos(int pos)
{
  enableDomeEncoder();
  if(encoderPos<pos)
  {
    domeCW();
    Serial.println(encoderPos-pos, DEC);
    while(abs(encoderPos-pos)>1)
      Serial.println(encoderPos);
    domeBreak();    
  }
  else
  {
    domeCCW();
    Serial.println(encoderPos-pos, DEC);
    while(abs(encoderPos-pos)>1)
      Serial.println(encoderPos);
    domeBreak();  
  }
  Serial.print("  #### Reached target  ===>  ");
  Serial.println(encoderPos-pos, DEC);
  disableDomeEncoder();

}
void domeSetPosHome(int pos)
{
  enableDomeEncoder();
  if(encoderPos<0)
  {
    domeCW();
    while(digitalRead(clearButton) != HIGH)
      Serial.println(encoderPos);
    encoderPos = 0;
  }
  else
  {
    domeCCW();
    while(digitalRead(clearButton) != HIGH)
      Serial.println(encoderPos);
    encoderPos = 0;
  }
  
  if(pos>0)
  {
    domeCW();
    Serial.println(encoderPos-pos, DEC);
    while(abs(encoderPos-pos)>1)
      Serial.println(encoderPos);
    domeBreak();    
  }
  else
  {
    domeCCW();
    Serial.println(encoderPos-pos, DEC);
    while(abs(encoderPos-pos)>1)
      Serial.println(encoderPos);
    domeBreak();  
  }
  Serial.print("  #### Reached target  ===>  ");
  Serial.println(encoderPos-pos, DEC);
  disableDomeEncoder();

}

void domeEncoderTest(){ 
  if (lastReportedPos != encoderPos) {
    Serial.print("Index: ");
    Serial.print(encoderPos, DEC);
    Serial.println();
    lastReportedPos = encoderPos;
  }
  if (digitalRead(clearButton) == HIGH)  {
    encoderPos = 0;
  }
}

void domeMotorTest()
{
  domeSetPosHome(3);
  delay(1000);
  domeSetPosHome(-3);
  delay(1000);
  domeSetPosHome(0);
  delay(1000);
  /*if (Serial.available() > 0) {
    int pos = Serial.read();
    Serial.println("SetPose");
    Serial.println(pos,DEC);
    domeSetPos(pos);
  }*/

  /*domeCW();
  Serial.println("Motor Dome Left");
  Serial.println("   ");
  delay(500);
  domeBreak();
  Serial.println("Motor Dome Stop");
  Serial.println("   ");
  delay(500);
  domeCCW();
  Serial.println("Motor Dome Right");
  Serial.println("   ");
  delay(500);
  domeBreak();
  Serial.println("Motor Dome Stop");
  Serial.println("   ");*/
}

void domeHoming()
{  
  domeCW();
  delay(1000);
  domeCCW();  
  while(digitalRead(clearButton) != HIGH)
      Serial.println(encoderPos);
  encoderPos = 0;
  domeBreak();
}

void initDome()
{
  pinMode(dir1PinDome,OUTPUT);
  pinMode(dir2PinDome,OUTPUT);
  pinMode(speedPinDome,OUTPUT);

  pinMode(encoderPinA, INPUT); 
  pinMode(encoderPinB, INPUT); 
  pinMode(clearButton, INPUT);
  
  digitalWrite(encoderPinA, HIGH);  // turn on pullup resistor
  digitalWrite(encoderPinB, HIGH);  // turn on pullup resistor
  digitalWrite(clearButton, HIGH);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(clearButton, INPUT_PULLUP);

  enableDomeEncoder();
  domeHoming();
}



