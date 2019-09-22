
#include "motor.h"//234,567
#include "piezo.h"//8
#include "led.h"//13
#include "ir.h"//9,10
#include "sonar.h"//?,?


typedef struct {
  int  valSonar;
  byte valIR;
} Env;
Env gEnv;
//byte motorSpeed = 128;
byte runMode = 0;//0:BT control, 1:Sonar mode, 2:line follower, 3:free mode
void getEnv(void)
{
  gEnv.valSonar = readSonar();
  gEnv.valIR = readIr();
  Serial.println(gEnv.valSonar);
  
}
void determineAction(int cmd)
{
  switch(cmd){
    case 'F':
      Serial.println("moveForward");
      moveForward();
      break;
    case 'B':
      moveBackward();
      Serial.println("moveBackward");
      break;
    case 'L':
      turnLeft();
      Serial.println("turnLeft");
      break;
    case 'R':
      turnRight();
      Serial.println("turnRight");
      break;
    case 'S':
      Serial.println("Stop");
      motorStop();
      break;
    default:
      break; 
      
  }
  
}

void testSonarDrive()
{
  while(1){
    getEnv();
    if(gEnv.valSonar<10)
    {
      //int sRes = random(sizeof(soundTable));
      //soundTable[sRes]();
      beep(speakerPin, note_D8,50);
      moveBackward();
      delay(500);
      if(random(1)) turnRight();
      else 
        turnLeft();
      delay(500);
    }
    else moveForward();
  }
  
  
}


