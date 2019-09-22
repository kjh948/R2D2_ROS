#import <Arduino.h>
#include "printf.h"
#include <SoftwareSerial.h>
//#include <PinChangeInt.h>
/*#include "motor.h"//234,567
#include "piezo.h"//8
#include "led.h"//13
#include "ir.h"//9,10
#include "sonar.h"//?,?*/
#include "brain.h"
int testModule=0;

//SoftwareSerial btSerial(9,10);

void testRun() {

  // Initialize the Serial interface:
  Serial.println("testModule");
  Serial.println(testModule);
  if(testModule==1)
  {
    testMotors();   
  }
  else if(testModule==3)
  {
    testPiezo();
    
  }
  else if(testModule==4)
  {
    testIr();
    
  }  
  else if(testModule==5)
  {
    testSonar();
    
  }  
  else if(testModule==6)
  {
    testSonarDrive();
    
  }
}
int status;

void setup(void)
{
  Serial.begin(38400);      //Set Baud Rate
  //btSerial.begin(115200);
  printf_begin();
  Serial.println("Init Started");
  initMotors();motorStop();
  initPiezo();
  initLed();
  //initIr();
  initSonar();

  randomSeed(analogRead(0));

  
  Serial.println("Init Completed");  
  //r2D2();
  beep(speakerPin, note_C7,100);
  testRun();
  
}
typedef void (*SoundTable) ();
SoundTable soundTable[] = {squeak,waka,r2D2};
int inByte = 0;
void loop() {
  
  if (Serial.available() > 0) {
    inByte = Serial.read();
    
    determineAction(inByte);
  }
  /*if (btSerial.available() > 0) {
    inByte = btSerial.read();
    Serial.println(inByte);
    determineAction(inByte);
  }*/
  
  //else motorStop();
  getEnv();
  if(gEnv.valSonar<10 && inByte)
  {
    //int sRes = random(sizeof(soundTable));
    //soundTable[sRes]();
    beep(speakerPin, note_D8,50);
    moveBackward();
    delay(500);
    //if(random(1)) turnRight();
    //else 
    turnLeft();
    delay(500);
    inByte = 'F';
    determineAction(inByte);
    //moveForward();
  }
  
}

