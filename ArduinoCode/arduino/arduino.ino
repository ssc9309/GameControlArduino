#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

int voltOutPin = 3;
int leftClickPin = 4;

Adafruit_BNO055 bno = Adafruit_BNO055(55);


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
  Serial.begin(250000);
  pinMode(voltOutPin, OUTPUT);
  pinMode(leftClickPin, INPUT);

  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  /* Display some basic information on this sensor */
  displaySensorDetails();
}


  /* Board layout:
         +----------+
         |         *| RST   PITCH  ROLL  HEADING
     ADR |*        *| SCL
     INT |*        *| SDA     ^            /->
     PS1 |*        *| GND     |            |
     PS0 |*        *| 3VO     Y    Z-->    \-X
         |         *| VIN
         +----------+
  */

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(voltOutPin, HIGH);
  //csv of states
  //leftClick, cal, cal, cal, cal, yaw [x], pitch, [y]
  String outputLine = "";

  sensors_event_t event;
  bno.getEvent(&event);

  int leftClickValue = digitalRead(leftClickPin);
  //Serial.println(leftClickValue);
  
  if (digitalRead(leftClickPin))
  {
    //Serial.println("LClick");
    outputLine += "1,";
  }
  else
  {
    outputLine += "0,";
  }

  uint8_t sys, gyro, accel, mag = 0;
  bno.getCalibration(&sys, &gyro, &accel, &mag);
  outputLine += sys;
  outputLine += ",";
  outputLine += gyro;
  outputLine += ",";
  outputLine += sys;
  outputLine += ",";
  outputLine += mag;
  outputLine += ",";
  outputLine += (float)event.orientation.x;
  outputLine += ",";
  outputLine += (float)event.orientation.y;

  Serial.println(outputLine);
  
  //delay(10000);
}
