#include "Mouse.h"
#include "Keyboard.h"
//https://www.arduino.cc/en/Tutorial/KeyboardAndMouseControl

const int killSwitchPin = 3;
const int leftClickPin = 4;
const int rightClickPin = 5;
const int reloadClickPin = 6;
const int shiftClickPin = 7;


int lastKillSwitchState = 0;
int currentKillSwitchState = 0;
int lastLeftClickState = 0;
int currentLeftClickState = 0;
int lastRightClickState = 0;
int currentRightClickState = 0;
int lastReloadClickState = 0;
int currentReloadClickState = 0;
int lastShiftClickState =  0;
int currentShiftClickState = 0;

void setup() {
  // put your setup code here, to run once:

  //INPUT_PULLUP will pull the pin to high by default, instead of floating
  //so pull to ground to activate the pin.
  pinMode(killSwitchPin, INPUT_PULLUP); 
  pinMode(leftClickPin, INPUT_PULLUP);
  pinMode(rightClickPin, INPUT_PULLUP);
  pinMode(reloadClickPin, INPUT_PULLUP);
  pinMode(shiftClickPin, INPUT_PULLUP);

  Serial.begin(9600);
  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  currentKillSwitchState = digitalRead(killSwitchPin)? 0 : 1;
  //Start the MouseKeyboard control if the kill switch is one
  if (currentKillSwitchState)
  {
    if (lastKillSwitchState != currentKillSwitchState)
    {
      lastKillSwitchState = currentKillSwitchState;
      Serial.println("Kill Switch Engaged");
    }

    //Press or Release depending on the state
    //Make sure you have a kill switch function for each button
    LeftClickCheck();
    RightClickCheck();
    ReloadClickCheck();
    ShiftClickCheck();
    
  }
  else
  {
    if (lastKillSwitchState != currentKillSwitchState)
    {
      lastKillSwitchState = currentKillSwitchState;
      Serial.println("Kill Switch Disengaged");
    }

    //unpress the buttons
    if (currentLeftClickState)
    {
      currentLeftClickState = 0;
      lastLeftClickState = currentLeftClickState;
      Mouse.release(MOUSE_LEFT);
    }
    if (currentRightClickState)
    {
      currentRightClickState = 0;
      lastRightClickState = currentRightClickState;
      Mouse.release(MOUSE_RIGHT);
    }
    //Release all the keyboards at once
    if (currentReloadClickState || currentShiftClickState)
    {
      currentReloadClickState = 0;
      lastReloadClickState = currentReloadClickState;
      currentShiftClickState = 0;
      lastShiftClickState = currentShiftClickState;
      
      Keyboard.releaseAll();
    }
  }
}

void LeftClickCheck()
{
  currentLeftClickState = digitalRead(leftClickPin) ? 0 : 1;
    //if it's just pressed, mouse press. vice versa
  if (lastLeftClickState != currentLeftClickState)
  {
    lastLeftClickState = currentLeftClickState;
     
    if (currentLeftClickState)
    {
      Mouse.press(MOUSE_LEFT);
    }
    else
    {
      Mouse.release(MOUSE_LEFT);
    }
  }
}

void RightClickCheck()
{
  currentRightClickState = digitalRead(rightClickPin) ? 0 : 1;
    //if it's just pressed, mouse press. vice versa
  if (lastRightClickState != currentRightClickState)
  {
    lastRightClickState = currentRightClickState;
      
    if (currentRightClickState)
    {
      Mouse.press(MOUSE_RIGHT);
    }
    else
    {
      Mouse.release(MOUSE_RIGHT);
    }
  }
}

void ReloadClickCheck()
{
  currentReloadClickState = digitalRead(reloadClickPin) ? 0 : 1;
    //if it's just pressed, mouse press. vice versa
  if (lastReloadClickState != currentReloadClickState)
  {
    lastReloadClickState = currentReloadClickState;
      
    if (currentReloadClickState)
    {
      Keyboard.press('r');
    }
    else
    {
      Keyboard.release('r');
    }
  }
}

void ShiftClickCheck()
{
  currentShiftClickState = digitalRead(shiftClickPin) ? 0 : 1;
    //if it's just pressed, mouse press. vice versa
  if (lastReloadClickState != currentReloadClickState)
  {
    lastShiftClickState = currentShiftClickState;
      
    if (currentShiftClickState)
    {
      Keyboard.press(KEY_LEFT_SHIFT);
    }
    else
    {
      Keyboard.release(KEY_LEFT_SHIFT);
    }
  }
}

