int joystickX = A3;
int joystickY = A2;

/*
 *         1023 x
 *           |
 *           |
 * 0 y-------+-------1023 y                
 *           |
 *           |
 *          0 x
 * GND 5+ VRx VRy SW Pins
 */




void setup() {
  // put your setup code here, to run once:
  pinMode(joystickX, INPUT);
  pinMode(joystickY, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(analogRead(joystickX));
  Serial.print("  ");
  Serial.println(analogRead(joystickY));

  //delay(100);
}
