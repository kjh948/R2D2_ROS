//#include <Encoder.h>


enum PinAssignments {
  encoderPinA = 19,
  encoderPinB = 18,
  clearButton = 20
};

volatile int encoderPos = 0;
unsigned int lastReportedPos = 1;

boolean A_set = false;
boolean B_set = false;


void setup() {

  pinMode(encoderPinA, INPUT); 
  pinMode(encoderPinB, INPUT); 
  pinMode(clearButton, INPUT);
  
  digitalWrite(encoderPinA, HIGH);  // turn on pullup resistor
  digitalWrite(encoderPinB, HIGH);  // turn on pullup resistor
  digitalWrite(clearButton, HIGH);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(clearButton, INPUT_PULLUP);

// encoder pin on interrupt 0 (pin 19)
  attachInterrupt(4, doEncoderA, CHANGE);
// encoder pin on interrupt 1 (pin 18)
  attachInterrupt(5, doEncoderB, CHANGE);
//  attachInterrupt(3, homePos, CHANGE);

  Serial.begin(115200);
}


void loop(){ 
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
// Interrupt on B changing state
void homePos(){
  // Test transition
  /H_set = digitalRead(clearButton) == HIGH;
  encoderPos = 0;
}

