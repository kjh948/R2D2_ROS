#import <Arduino.h>
#include "printf.h"

int leftIr = 0;
int rightIr = 1;


void initIr()
{
  pinMode(leftIr,INPUT);
  pinMode(rightIr,INPUT);

  
}
int readIr()
{
  return (digitalRead(leftIr)<<1) + digitalRead(rightIr);
}

int testIr()
{
  int status;
  printf("Ir test started");
  while(1){
    status = readIr();
    printf("status = %d\n",status);
    delay(50);   
  }
  
}
