#include "Mouse.h"

//overwatch. about 1800 for up and down
//moving - in vertical is going up
//horizontal. about 3600 (just a bit more) to 360 turn
/+ is to the right

long startNum = 0;
int endNum = 40;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Mouse.begin();

  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (startNum < endNum)
  {
    Mouse.move(100, 0, 0);
    //Mouse.click();
    Serial.print("Mouse move ");
    Serial.println(startNum);
    delay(1000);
  }
  startNum++;
}
