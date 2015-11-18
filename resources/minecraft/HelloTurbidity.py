#!/usr/bin/python
# Upload Standard Firmata to the Arduino Board from the Examples Menu


#Install the modules we need
from pyfirmata import Arduino, util, INPUT
from mcpi import minecraft
from mcpi import minecraftstuff
from time import sleep
import server

#led on values
HIGH = 1
LOW = 0

# Use the command /getpos to find out where you are then use those
# x, y, z coordinates to build things
# translate mc coords for mcpi ones
# add this to x
mcx = 177
# - this from y
mcy = 64
# - this from z
mcz = 135
# Connect to the server we use server.py imported to make it work with CloudMaker
mc = minecraft.Minecraft.create(server.address)
#Post a message to the minecraft chat window 
mc.postToChat("Ready to read Turbidity")

# Set up the connection to the Arduino/Shrimp
# This may appear differently in Windows as COM0 or COM1 but in Unix like systems it's likely
# to be like this:
PORT = "/dev/tty.SLAB_USBtoUART"
shrimp = Arduino(PORT)

# If we get here things should be ready to go
print("Everything is connected up.")
    
it = util.Iterator(shrimp)
it.start()
print "Iterator started"

# Start reporting for defined pins
#shrimp.analog[0].enable_reporting()
shrimp.analog[1].enable_reporting()
#note we've swapped to ana1

#ana0 = shrimp.analog[0]
ana1 = shrimp.analog[1]
#ana0 = shrimp.analog[0]
#ana1 = shrimp.analog[1]

#setup LED
turbidled1 = shrimp.digital[9]
led1 = shrimp.digital[11]
led2 = shrimp.digital[12]
led3 = shrimp.digital[13]

NotListening = False


# define the function to draw the blocks

def drawblocks(xpos, ypos, zpos, xpos1, ypos1, zpos1, blocktype):
    mc.setBlocks(xpos, ypos, zpos, xpos1, ypos1, zpos1, blocktype)

def drawblock(xpos, ypos, zpos, blocktype):
    mc.setBlock(xpos, ypos, zpos, blocktype)
# make an arbitrary start value for lastVal
lastVal = 1

# define a barchart function 



def barchart1(triggerled1, triggerled2, triggerled3, startx, starty, startz, blocktype, maxchartwidth, maxchartheight):
	global lastVal
	ana1reading = ana1.read()
	#readnow = int(ana1reading * 10)
	readnow = ana1reading * 10
	#print ana1reading
	#print readnow
	read_range = translate(readnow, 6, 10, 0, 20)
	reading = int(read_range)
	#print reading
# light LEDS based on reading
	if ana1reading > triggerled1:
		led1.write(HIGH)
	elif ana1reading > triggerled2:
		led1.write(HIGH)
		led2.write(HIGH)
	elif ana1reading > triggerled3:
		led1.write(HIGH)
		led2.write(HIGH)
		led3.wrie(HIGH)
	
	elif readnow > lastVal:
		#barheight = lastVal + readnow
		barheight = lastVal + reading
		drawblocks((startx + mcx), (starty-mcy), (startz-mcz), (startx + mcx) + maxchartwidth, (starty-mcy) + barheight, (startz - mcz) + maxchartwidth, blocktype)
		drawblocks((startx + mcx), (starty-mcy) + barheight, (startz-mcz), (startx + mcx) + maxchartwidth, maxchartheight, (startz - mcz) + maxchartwidth, 0)
	elif readnow < lastVal:
		#barheight = lastVal - readnow
		barheight = lastVal - reading
		drawblocks((startx+mcx), (starty-mcy) + lastVal, (startz-mcz), (startx+mcx)+maxchartwidth, (starty-mcy) + maxchartheight, (startz-mcz) + maxchartwidth, 0)
	else:
		#barheight = readnow
		#drawblocks((startx+mcx), (starty-mcy), (startz-mcz), (startx + mcx) + maxchartwidth, (starty-mcy) + readnow, (startz-mcz)+maxchartwidth, blocktype)
		readnow = lastVal
		led1.write(LOW)
		led2.write(LOW)
		led3.write(LOW)
	#mc.postToChat("Temp " + str(reading2))
	sleep(0.5)
#lastVal = readnow
# setup the player position
#playerPos = mc.player.getPos()

# a function to map values of one range to another

def translate(value, leftMin, leftMax, rightMin, rightMax):
    # Figure out how 'wide' each range is
    leftSpan = leftMax - leftMin
    rightSpan = rightMax - rightMin

    # Convert the left range into a 0-1 range (float)
    valueScaled = float(value - leftMin) / float(leftSpan)

    # Convert the 0-1 range into a value in the right range.
    return rightMin + (valueScaled * rightSpan)

#Main Loop
	
try:
	while not NotListening:
		turbidled1.write(HIGH)
		sleep(0.25)
		# change this for size, location etc of chart
		barchart1(2, 4, 6, -475, 89, -1379, 89,  2, 100)
except KeyboardInterrupt:
	print "stopped"
	#NotListening = True
finally:
	NotListening = True
	print "stopped finally now"
