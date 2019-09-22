#import <Arduino.h>
#include "printf.h"

#include <PS2X_lib.h>  //for v1.6

PS2X ps2x; // create PS2 Controller Class 
 
byte type = 0;
byte vibrate = 0;
int RX=0,RY=0,LX=0,LY=0;

int initPS2X(void)
{
 int error; 
 error = ps2x.config_gamepad(22,23,24,25, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
        return 0;
       break;
       case 1:
        Serial.println("DualShock Controller Found");
        return 1;
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
         return 2;
       break;
     }
}

void testPS2X()
{
   ps2x.read_gamepad(false, vibrate);   /* read controller and set large motor to spin at 'vibrate' speed */
   //Serial.println("Stick values:   ");       /* Display analog stick values */
   LY = ps2x.Analog(PSS_LY);          /* Reading Left stick Y axis */
   LX = ps2x.Analog(PSS_LX);          /* Reading Left stick X axis */
   RY = ps2x.Analog(PSS_RY);          /* Reading Right stick Y axis */
   RX = ps2x.Analog(PSS_RX);          /* Reading Right stick X axis */
   //if((LY <= 9))                      /* standardize to 3 digit by checking less than 10 */
   //   Serial.println("00");                /* eg: if LY= 5 then it display as "005" in lcd */
   //if((LY >= 9 &&LY <= 99))           /* standardize to 3 digit by checking between 10-99 */
   //   Serial.println("0");                 /* eg: if LY= 55 then it display as "055" in lcd */     
   /*if(ps2x.NewButtonState()) {       
      Serial.println("pressed  "); 
      delay(700);
   }
   else;*/  
  Serial.println(LY);
  delay(100);
}



bool checkUp()
{
  return ps2x.Button(PSB_PAD_UP);   
}
bool checkDown()
{
  return ps2x.Button(PSB_PAD_DOWN);   
}
bool checkLeft()
{
  return ps2x.Button(PSAB_PAD_LEFT);   
}
bool checkRight()
{
  return ps2x.Button(PSAB_PAD_RIGHT);   
}
bool checkSelect()
{
  return ps2x.Button(PSB_SELECT);   
}
bool checkStart()
{
  return ps2x.Button(PSB_START);   
}

#if 1
typedef struct {
  bool up;
  bool down;
  bool left;
  bool right;
  bool select;
  bool start; 
  bool circle;
  bool square;
  bool cross;
} dataPS2X;
dataPS2X & readPS2X(dataPS2X & data)
{
  ps2x.read_gamepad(false, vibrate);
  
  data.up = ps2x.Button(PSB_PAD_UP);
  data.down = ps2x.Button(PSB_PAD_DOWN);
  data.left = ps2x.Button(PSB_PAD_LEFT);
  data.right = ps2x.Button(PSB_PAD_RIGHT);

  data.select = ps2x.Button(PSB_SELECT);
  data.start = ps2x.Button(PSB_START);
  data.circle = ps2x.Button(PSB_CIRCLE);
  data.square = ps2x.Button(PSB_SQUARE);
  data.cross = ps2x.Button(PSB_CROSS);
  return data;
}
#endif


