#import <Arduino.h>
#include "printf.h"

#include "motor.h"
#include "piezo.h"
#include "dome.h"
#include "led.h"
#include "ps2x.h"
#include "knock.h"
//#include "cognition.h"
//#include "action.h"

//#define TEST

#ifdef TEST
int testModule=4;
void testsuite()
{
  // Initialize the Serial interface:

  if(testModule==1)
  {
    testMotors();
    return;    
  }
  else if(testModule==2)
  {
    domeMotorTest();
    //domeEncoderTest();
    return;
  }
  else if(testModule==3)
  {
      squeak();
      delay(500);
      catcall();
      delay(500);
      ohhh();
      delay(500);
      laugh();
      delay(500);
      closeEncounters();
      delay(500);
      laugh2);
      delay(500);
      waka();
      delay(500);  
      r2D2();
      delay(500);
      ariel();
      delay(3000);
  }
  else if(testModule==4)
  {
    testLed();    
  }
  else if(testModule==5)
  {
    //Serial.println("ps2 test"); 
    testPS2X();    
  } 
  else if(testModule==6)
  {
    testKnock();    
  }     
}
#endif


#define COMMAND_RATE 10 //hz
#define SENSOR_RATE 10 //hz
#define LED_RATE 30 //hz
#define DEBUG_RATE 5


dataPS2X dataps2x;
byte ledCmd=0;
byte ledRate=30;

void setup(void)
{
  Serial.begin(115200);      //Set Baud Rate
  printf_begin();
  Serial.println("Init Started");
  initMotors();
  initPiezo();
  initDome();
  initLed();
  initPS2X();
  Serial.println("Init Completed");  

  static bool isStart = false;
  while(1)
  {
    dataps2x = readPS2X(dataps2x);
    if (dataps2x.start)
    {
      laugh();
      ledCmd = 1;
      break;
    }
    delay(500);
  }
}




void loop() {
#ifdef TEST
  testsuite();
#else
  static unsigned long prev_sensor_time = 0;
  static unsigned long prev_command_time = 0;
  static unsigned long prev_led_time = 0;
  
  
  if ((millis() - prev_sensor_time) >= (1000 / SENSOR_RATE))
  {
      dataps2x = readPS2X(dataps2x);
      if( checkKnock() )
      {
        
        
        
      }
      prev_sensor_time = millis();
  }



  if ((millis() - prev_command_time) >= (1000 / COMMAND_RATE))
  {
      if(dataps2x.square) domeSetPosHome(3);
      if(dataps2x.circle) domeSetPosHome(-3);
      if(dataps2x.cross) domeSetPosHome(0);
    
    
      if(dataps2x.left) moveLeft();
      else if(dataps2x.right) moveRight();
      else if(dataps2x.up) moveForward();
      else if(dataps2x.down) moveBackward();
      else moveStop();
      prev_command_time = millis();
  }

  if ((millis() - prev_led_time) >= (1000 / ledRate))
  {
      if(ledCmd>0)
      {
        showLed(prev_led_time%256,(255-prev_led_time%256));
      }
      prev_led_time = millis();
  }
  
  

#endif  
}



