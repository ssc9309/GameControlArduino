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


def click(x,y):
    win32api.SetCursorPos((x,y))
    win32api.mouse_event(win32con.MOUSEEVENTF_WHEEL,x,y,0,0)
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
arduino = serial.Serial('COM6', 115200, timeout=.1)

leftClickState = "off"

#while (x <= 500):
while (True):

    '''
    if (x < 200):
        y = 0

    #elif (x < 300):
        #y = 500
    else:
        #y = 1000
        y += 10
        #print (y)

    #click(x,y)
    x += 10
    '''

    data = arduino.readline()[:-2] #the last bit gets rid of the new-line chars
    if data:
        #print (data)

        if ("1" in str(data)):
            if (leftClickState == "off"):
                win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,0,0,0,0)
                win32api.mouse_event(win32con.MOUSEEVENTF_MOVE,10,0,0,0)

                leftClickState = "on"
                print("Left Down")
        elif ("0" in str(data)):
            if (leftClickState == "on"):
                win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,0,0,0,0)
                leftClickState = "off"
                print("Left Up")

    '''
    print (x)
    print (" ")
    print (y)
    '''

    #sleep(0.5)

print ("End")