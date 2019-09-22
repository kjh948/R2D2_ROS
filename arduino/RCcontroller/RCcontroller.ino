/*
Written by: Mujahed Altahle
 
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ 
or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 */
 
/* A simple Project for Remote Controlling with nRF24L01+ radios. 
 We have 2 nodes, the transmitter (this one) and the receiver which is attached to the Car.
 The idea is to transmit  2 parameters , one is Direction (Backward, or Forward with the speed) the other is the Steering (Left, or Right with the degree of rotation).
 The nRF24L01 transmit values in type of "uint8_t" with maximum of 256 for each packet, so the values of direction is divided by (10) at the Tx side,
 then it is multiplied by 10 again at the Rx side.
 The Rx rules is to output the received parameters to port 3 and 6 where the Servo and the ESC are are attached
 a condition is required to prevent the controller from transmitting values that is not useful (like 1480-1530 for ESC and 88-92 for Servo) to save more power as much as we can
 */
 
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
//
// Hardware configuration
//
// Set up nRF24L01 radio on SPI bus plus pins 9 & 10
RF24 radio(9,10);

uint8_t data[3] ; //buffer to store received data
const uint8_t buffer_size = sizeof(data);
//pins that used for the Joystick
const int analogInPinX= A0; // 
const int analogInPinY = A1;// 
const int analogInPinZ = A2;//
 
const int tx_led=2;// transmission indicator
int Y_value = 0;        // values read from the pot 
int X_value = 0; 
int Z_value = 0; 
int outputValue = 0; 
/*
const int transmit_pin=6;
 int transmit_enable;
 int ForwrdButton=2;
 int BackwrdButton=3;
 */
//
// Topology
//

// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;


//
// Setup
//

void setup(void)
{

  Serial.begin(57600);
  printf_begin();

  //
  // Setup and configure rf radio
  //

  radio.begin();
  radio.setPayloadSize(24);

  radio.openWritingPipe(pipe);
  //
  // Dump the configuration of the rf unit for debugging
  //

  radio.printDetails();
  printf("init done\n");
  //
  // Set up buttons
  //

  /*to be used later
   pinMode(ForwrdButton,INPUT );
   pinMode(BackwrdButton,INPUT);
   pinMode(transmit_enable,INPUT);
   */
  pinMode(tx_led,OUTPUT);
  digitalWrite(tx_led,LOW);

}

//
// Loop
//

void loop(void)
{

  X_value = analogRead(analogInPinX); 
  data[0] = map(X_value, 0, 1023,0 , 255); 
  Y_value = analogRead(analogInPinY); 
  data[1] = map(Y_value, 0, 1023, 0, 255); 
  Z_value = analogRead(analogInPinZ); 
  data[2] = map(Z_value, 0, 1023, 0, 255); 

  //printf("%d\t%d\t%d\n",data[0],data[1],data[2]);
  
  bool ok = radio.write( data, buffer_size );
  if(ok)
  {
    digitalWrite(tx_led,HIGH); //turn led on after transmission
    
    //printf("ok\n\r");
  }
  else
  {
    digitalWrite(tx_led,LOW); //turn led on after transmission
    //printf("fail\n\r");
  }
}
