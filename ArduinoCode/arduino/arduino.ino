int voltOutPin = 3;
int leftClickPin = 4;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(voltOutPin, OUTPUT);
  pinMode(leftClickPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(voltOutPin, HIGH);
  //csv of states
  //leftClick, 
  String outputLine = "";

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

  Serial.println(outputLine);
  
  //delay(10000);
}
