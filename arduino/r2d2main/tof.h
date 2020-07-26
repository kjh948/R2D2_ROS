
#include "Adafruit_VL53L0X.h"
 
Adafruit_VL53L0X TOF = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measure;

///////////////////////////////////////////////////////////////
void initToF()
{
  TOF.begin();
}

int16_t measureToF()
{
  TOF.rangingTest(&measure, false);
  if(measure.RangeStatus != 4) {  
    return measure.RangeMilliMeter;
  } 
  else {
    return -1;
  } 
}
void testToF()
{
  while(1){
    Serial.println("Distance: ");
    Serial.println(measureToF());
    Serial.println("   ");
    delay(100);    
  }
}
