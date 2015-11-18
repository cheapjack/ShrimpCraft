#!/usr/bin/python
# Upload Standard Firmata to the Arduino Board from the Examples Menu

#Install the modules we need
#from pyfirmata import Arduino, util, INPUT
from mcpi import minecraft
from mcpi import minecraftstuff
from time import sleep
import server
import serial


#led on values
HIGH = 1
LOW = 0

# Set up the connection to the Arduino/Shrimp
# This may appear differently in Windows as COM0 or COM1 but in Unix like systems it's likely
# to be like this:
PORT = "/dev/tty.SLAB_USBtoUART"
ser = serial.Serial(PORT, 9600)
#shrimp = Arduino(PORT)

# If we get here things should be ready to go
print("Everything is connected up.")
sleep(0.5)
print("Reading from Serial...")
sleep(0.5)
# Use the command /getpos or F3 in Minecraft client to find out where you are then use those
# x, y, z coordinates to build things
# translate mc coords for mcpi ones
# add this to x
mcx = 177
# - this from y
mcy = 64
# - this from z
mcz = 135
# Connect to the server we use the imported server.py to make it work with CloudMaker
mc = minecraft.Minecraft.create(server.address)
#Post a message to the minecraft chat window 
mc.postToChat("Ready to read Temperature")

#NotListening = False


# Define a translate function that maps one value range to another:
def translate(value, leftMin, leftMax, rightMin, rightMax):
    # Figure out how 'wide' each range is
    leftSpan = leftMax - leftMin
    rightSpan = rightMax - rightMin

    # Convert the left range into a 0-1 range (float)
    valueScaled = float(value - leftMin) / float(leftSpan)

    # Convert the 0-1 range into a value in the right range.
    return rightMin + (valueScaled * rightSpan)

# make an arbitrary start value for lastVal
lastVal = 1

# define a barchart function 

def TemperatureChart1(startx, starty, startz, blocktype, maxchartwidth, maxchartheight):
	global lastVal
	# An array to store the temperature from the arduino over serial
	tempstring = []
	tempread = ser.readline()
	# Add the serial message to tempstring
	tempstring.append(tempread)
	reading = tempstring.pop()
	tempreading = reading[0:2]
	# Option to read temperature for debugging
	print "Temperature is ", tempreading
	# Our main reading:
	tempreadingint = int(tempreading)
	# use the translate function to map temperature range to a defined block range
	read_ranged = translate(tempreadingint, 19, 30, 0, maxchartheight)
	# Wait a while
	sleep(0.25)
	# our ranged reading	
	readnow = int(read_ranged)
	# print "Readnow is ranged to ", readnow
	# compare if value has changed
	if tempreadingint > lastVal:
		barheight = readnow + lastVal
		mc.setBlocks((startx + mcx), (starty-mcy), (startz-mcz), (startx + mcx) + maxchartwidth, (starty-mcy) + barheight, (startz - mcz) + maxchartwidth, blocktype)
		
		mc.setBlocks((startx + mcx), (starty-mcy) + barheight, (startz-mcz), (startx + mcx) + maxchartwidth, maxchartheight, (startz - mcz) + maxchartwidth, 0)
	elif tempreadingint < lastVal:
		mc.setBlocks((startx+mcx), (starty-mcy) + lastVal, (startz-mcz), (startx+mcx)+maxchartwidth, (starty-mcy) + maxchartheight, (startz-mcz) + maxchartwidth, 0)
	else:
		lastVal = tempreadingint
	sleep(0.25)

#Main Loop

while True:
	TemperatureChart1(-455, 89, -1379, 89, 2, 40)

print "stopped"
