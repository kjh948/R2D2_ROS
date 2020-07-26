

int knockSensor = A8;               
int THRESHOLD = 100;
int sensorReading;

void initKnock()
{}

bool checkKnock(void)
{
  sensorReading = analogRead(knockSensor);

  // if the sensor reading is greater than the threshold:
  if (sensorReading >= THRESHOLD) return true;
  else return false;
  
}

void testKnock(void)
{
    if(checkKnock()) Serial.println("Knock");
    delay(100);  
}
