

#include <AFMotor.h>

AF_DCMotor motorR(3, MOTOR34_64KHZ);
AF_DCMotor motorL(4, MOTOR34_64KHZ);


int motorSpeed = 96;



///////////////////////////////////////////////////////////////
void initMotors()
{
  motorL.setSpeed(motorSpeed);
  motorR.setSpeed(motorSpeed);
}

void moveLeft()
{
  motorL.run(FORWARD); 
  motorR.run(BACKWARD); 
}
void moveRight()
{
  motorL.run(BACKWARD); 
  motorR.run(FORWARD); 
}
void moveBackward()
{
  motorL.run(FORWARD); 
  motorR.run(FORWARD); 
}
void moveForward()
{
  motorL.run(BACKWARD); 
  motorR.run(BACKWARD); 
}
void moveStop()
{
  motorL.run(RELEASE); 
  motorR.run(RELEASE); 
}

void testMotors()
{

  if (Serial.available() > 0) {
    int inByte = Serial.read();
    int speed; // Local variable

    switch (inByte) {

      //______________Motor 1______________

    case '1': // Motor 1 Forward
      motorL.run(FORWARD); 
      Serial.println("Motor 1 Forward");
      Serial.println("   ");
      break;

    case '2': // Motor 1 Stop (Freespin)
      motorL.run(RELEASE); 
      Serial.println("Motor 1 Stop");
      Serial.println("   ");
      break;

    case '3': // Motor 1 Reverse
      motorL.run(BACKWARD); 
      Serial.println("Motor 1 Reverse");
      Serial.println("   ");
      break;

      //______________Motor 2______________

    case '4': // Motor 2 Forward
      motorR.run(FORWARD); 
      Serial.println("Motor 2 Forward");
      Serial.println("   ");
      break;

    case '5': // Motor 1 Stop (Freespin)
      motorR.run(RELEASE); 
      Serial.println("Motor 2 Stop");
      Serial.println("   ");
      break;

    case '6': // Motor 2 Reverse
      motorR.run(BACKWARD); 
      Serial.println("Motor 2 Reverse");
      Serial.println("   ");
      break;

    default:
      break;
    }
  }

}
