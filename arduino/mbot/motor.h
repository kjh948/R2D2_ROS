//Motor 1
int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 4; // Needs to be a PWM pin to be able to control motor speed
// Motor 2
int dir1PinB = 5;
int dir2PinB = 6;
int speedPinB = 7; // Needs to be a PWM pin to be able to control motor speed

int motorSpeed = 128;



///////////////////////////////////////////////////////////////
void initMotors()
{
  pinMode(dir1PinA,OUTPUT);
  pinMode(dir2PinA,OUTPUT);
  pinMode(speedPinA,OUTPUT);
  pinMode(dir1PinB,OUTPUT);
  pinMode(dir2PinB,OUTPUT);
  pinMode(speedPinB,OUTPUT);
  

}
void moveBackward()
{
  analogWrite(speedPinA, motorSpeed);//Sets speed variable via PWM 
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);

  analogWrite(speedPinB, motorSpeed);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);

}
void moveForward()
{
  analogWrite(speedPinA, motorSpeed);//Sets speed variable via PWM 
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);

  analogWrite(speedPinB, motorSpeed);
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);
}
void turnLeft()
{
  analogWrite(speedPinA, motorSpeed>>1);//Sets speed variable via PWM 
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);

  analogWrite(speedPinB, motorSpeed);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
}

void turnRight()
{
  analogWrite(speedPinA, motorSpeed);//Sets speed variable via PWM 
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);

  analogWrite(speedPinB, motorSpeed>>1);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
}
void turnLeftBack()
{
  analogWrite(speedPinA, motorSpeed>>1);//Sets speed variable via PWM 
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);

  analogWrite(speedPinB, motorSpeed);
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);
}

void turnRightBack()
{
  analogWrite(speedPinA, motorSpeed);//Sets speed variable via PWM 
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);

  analogWrite(speedPinB, motorSpeed>>1);
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);
}

void motorStop()
{
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, LOW);

  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, LOW);
}

void testMotors()
{
  while(1){
    if (Serial.available() > 0) {
      int inByte = Serial.read();
      int speed; // Local variable
  
      switch (inByte) {
  
        //______________Motor 1______________
  
      case '1': // Motor 1 Forward
        analogWrite(speedPinA, motorSpeed);//Sets speed variable via PWM 
        digitalWrite(dir1PinA, LOW);
        digitalWrite(dir2PinA, HIGH);
        Serial.println("Motor 1 Forward");
        Serial.println("   ");
        break;
  
      case '2': // Motor 1 Stop (Freespin)
        analogWrite(speedPinA, 0);
        digitalWrite(dir1PinA, LOW);
        digitalWrite(dir2PinA, HIGH);
        Serial.println("Motor 1 Stop");
        Serial.println("   ");
        break;
  
      case '3': // Motor 1 Reverse
        analogWrite(speedPinA, motorSpeed);
        digitalWrite(dir1PinA, HIGH);
        digitalWrite(dir2PinA, LOW);
        Serial.println("Motor 1 Reverse");
        Serial.println("   ");
        break;
  
        //______________Motor 2______________
  
      case '4': // Motor 2 Forward
        analogWrite(speedPinB, motorSpeed);
        //analogWrite(dir1PinB, motorSpeed);
        digitalWrite(dir1PinB, LOW);
        digitalWrite(dir2PinB, HIGH);
        Serial.println("Motor 2 Forward");
        Serial.println("   ");
        break;
  
      case '5': // Motor 1 Stop (Freespin)
        //analogWrite(speedPinB, 0);
        //analogWrite(dir1PinB, 0);
        digitalWrite(dir1PinB, LOW);
        digitalWrite(dir2PinB, LOW);
        Serial.println("Motor 2 Stop");
        Serial.println("   ");
        break;
  
      case '6': // Motor 2 Reverse
        analogWrite(speedPinB, motorSpeed);
        //analogWrite(dir1PinB, motorSpeed);
        digitalWrite(dir1PinB, HIGH);
        digitalWrite(dir2PinB, LOW);
        Serial.println("Motor 2 Reverse");
        Serial.println("   ");
        break;
  
  
      default:
        // turn all the connections off if an unmapped key is pressed:
        for (int thisPin = 2; thisPin < 11; thisPin++) {
          digitalWrite(thisPin, LOW);
        }
      }
    }
  }
}
