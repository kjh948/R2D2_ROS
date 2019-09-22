// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor motor(1);

void setup() {
  Serial.begin(115200);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motor.setSpeed(90);
 
  motor.run(RELEASE);
}

void loop() {
  uint8_t i;
  
  Serial.print("tick");
  motor.run(RELEASE);
  delay(300);
  motor.run(FORWARD);
  delay(300);
  motor.run(BACKWARD);
  delay(300);
  motor.run(RELEASE);
  delay(1000);
  Serial.print("tech");
}
