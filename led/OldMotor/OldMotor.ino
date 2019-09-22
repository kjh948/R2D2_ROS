#include "dome.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);      //Set Baud Rate
  Serial.println("Init Started");
  initDome();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //domeEncoderTest();
  domeMotorTest();
}
