#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include "Mouse.h"

Adafruit_BNO055 bno = Adafruit_BNO055(55);

const int killSwitchPin = 12;

void displaySensorDetails(void)
{
  sensor_t sensor;
  bno.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" xxx");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" xxx");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" xxx");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  displaySensorDetails();

  Mouse.begin();
  pinMode(killSwitchPin, INPUT_PULLUP);
}

double lastYaw = 999;
double lastPitch = 999;
double currentYaw = 0;
double currentPitch = 0;
double deltaYaw = 0;
double deltaPitch = 0;

double gain = 10;

bool skipYawUpdate = false;
bool skipPitchUpdate = false;


void loop() {
  // put your main code here, to run repeatedly:
  sensors_event_t event;
  bno.getEvent(&event);

  currentYaw = (double)event.orientation.x;
  currentPitch = (double)event.orientation.y;

  if (lastYaw == 999)
  {    
  }
  else
  {
    deltaYaw = currentYaw - lastYaw;
    deltaPitch = currentPitch - lastPitch;
    

    if (!digitalRead(killSwitchPin))
    {
      if (abs(deltaYaw*gain) < 1)
      {
        skipYawUpdate = true;
      }
      if (abs(deltaPitch*gain) < 1)
      {
        skipPitchUpdate = true;
        Serial.println("Delta too small");
      }
      else
      {
        Serial.println("Delta significant");
      }

      if (skipPitchUpdate && skipYawUpdate)
      {
        //Serial.println("Where");
      }
      else if (skipPitchUpdate)
      {
        Mouse.move(0, -deltaPitch*gain, 0);
        //Serial.println("AM");
      }
      else if (skipYawUpdate)
      {
        Mouse.move(deltaYaw*gain, 0, 0);
        //Serial.println("I");
      }
      else
      {
        Mouse.move(deltaYaw*gain, -deltaPitch*gain, 0);
        //Serial.println("Alice?");
      }
    }
  }

  if (!skipYawUpdate)
  {
    lastYaw = currentYaw;
    
  }
  if (!skipPitchUpdate)
  {
    lastPitch = currentPitch;
    Serial.println("Pitch Update");
  }
  else
  {
    //Serial.println("Why am i here?");
  }

  skipYawUpdate = false;
  skipPitchUpdate = false;
  
  //Serial.print(currentPitch);
  //Serial.print(" ");
  //Serial.println(lastPitch);
}
