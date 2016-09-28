__author__ = 'Hank'

#http://timgolden.me.uk/pywin32-docs/contents.html
#https://msdn.microsoft.com/en-us/library/windows/desktop/ms646260%28v=vs.85%29.aspx?f=255&MSPPError=-2147217396
#top left is 0, 0
#bottom right is 1920, 1080
#it takes about 200 y displacement to go from fully up to fully down

#x and y are RELATIVE.
#0, 0 = don't move mouse from current location
#win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,x,y,0,0)

print("Hello")

import win32api, win32con
import serial

from time import sleep


def MouseMove(x,y):
    win32api.SetCursorPos((x,y))
    win32api.mouse_event(win32con.MOUSEEVENTF_MOVE,x,y,0,0)
    #win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,x,y,0,0)
    #win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,x,y,0,0)

def LeftClickMethod():
    #win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,0,0,0,0)
    #win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,0,0,0,0)
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,10,0,0,0)
    #win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,1,0,0,0)
    print("Left Click")

x = 0
y = 0
arduino = serial.Serial('COM4', 250000, timeout=.1)

leftClickState = "off"

isArduinoConnected = False
isArduinoMoved = False
lastArduinoPitch = 999 #-90 to 90
lastArduinoYaw = 999 #0 to 360

arduinoPitchGain = 20
arduinoYawGain = 20

deltaYaw = 0
deltaPitch = 0

while (True):
    #csv
    #0,3,3,3,3,331.06,18.56
    data = arduino.readline()[:-2] #the last bit gets rid of the new-line chars
    #formatting
    dataString = str(data)
    dataString = dataString[2:-1]
    #print(dataString)

    if "," in dataString:
        if not (isArduinoConnected):
            print("Arduino Message Received")
            isArduinoConnected = True

        csvArray = dataString.split(',')
        arduinoLeftClick = csvArray[0]
        arduinoYaw = float(csvArray[5])
        arduinoPitch = float(csvArray[6])
        #print(arduinoYaw)

    #csvArray = data.split(',')


    if isArduinoConnected:
        if ("1" in arduinoLeftClick):
            if (leftClickState == "off"):
                win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,0,0,0,0)
                leftClickState = "on"
                print("Left Down")
        elif ("0" in arduinoLeftClick):
            if (leftClickState == "on"):
                win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,0,0,0,0)
                leftClickState = "off"
                print("Left Up")

        if (lastArduinoPitch != arduinoPitch):
            if (lastArduinoPitch == 999):
                lastArduinoPitch = arduinoPitch
            else:
                deltaPitch = lastArduinoPitch - arduinoPitch
                deltaPitch = int(deltaPitch*arduinoPitchGain)
                isArduinoMoved = True
                #print(arduinoPitch)

                lastArduinoPitch = arduinoPitch

        if (lastArduinoYaw != arduinoYaw):
            if (lastArduinoYaw == 999):
                lastArduinoYaw = arduinoYaw
            else:
                deltaYaw = lastArduinoYaw - arduinoYaw
                deltaYaw = int(deltaYaw*arduinoYawGain)
                isArduinoMoved = True
                lastArduinoYaw = arduinoYaw


        if isArduinoMoved:
            MouseMove(-deltaYaw, deltaPitch)
            isArduinoMoved = False
    '''
    print (x)
    print (" ")
    print (y)
    '''

    #sleep(0.5)

print ("End")