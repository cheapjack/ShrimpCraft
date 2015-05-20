from pyfirmata import Arduino, util, INPUT

import mcpi.minecraft as minecraft
#import minecraft block module
import mcpi.block as block
#import time, so delays can be used
import time
import server

lastVal = 0
lastVal2 = 0

#leds
HIGH = 1
LOW = 0


mc = minecraft.Minecraft.create(server.address)
#Post a message to the minecraft chat window 
mc.postToChat("Barcharter")
# Set up the connection to the Arduino/Shrimp
PORT = "/dev/tty.SLAB_USBtoUART4"

shrimp = Arduino(PORT)

# And the connection to the server: original
# mc_server = ServerConnection(MINECRAFT_SERVER, MINECRAFT_RCON_PASSWORD, 25566)
# mc_server = ServerConnection(MINECRAFT_SERVER, MINECRAFT_RCON_PASSWORD, 25568)

# If we get here things should be ready to go
print("Everything is connected up.")
    
it = util.Iterator(shrimp)
it.start()
print "Iterator started"

# Start reporting for defined pins
shrimp.analog[0].enable_reporting()
shrimp.analog[1].enable_reporting()
ana0 = shrimp.analog[0]
ana1 = shrimp.analog[1]
#ana0 = shrimp.analog[0]
#ana1 = shrimp.analog[1]

#setup LED
turbidled1 = shrimp.digital[9]
led1 = shrimp.digital[11]
led2 = shrimp.digital[12]
led3 = shrimp.digital[13]
#switchin = shrimp.digital[10]



# define the function to read the pin and translate to the blocks


def drawblocks(xpos, ypos, zpos, xpos1, ypos1, zpos1, blocktype):
    mc.setBlocks(xpos, ypos, zpos, xpos1, ypos1, zpos1, blocktype)

def drawblock(xpos, ypos, zpos, blocktype):
    mc.setBlock(xpos, ypos, zpos, blocktype)



def barchart1():
    #setup pins
    ana1reading = ana1.read()
    read = ana1reading * 100
    reading = read
    global lastVal
    level = 74
    

#    mc.postToChat("lastVal " + str(lastVal))
#    mc.postToChat("Reading " + str(reading))
    
    
    #lastBar = starty + lastVal
    #drawblocks(startx, starty, startz, startx+2, lastBar, startz+2, 89)

   # valnow = lastVal + Reading
    if reading > lastVal + 10 or reading < lastVal - 10:
#        mc.postToChat("its changed!")
        if reading > lastVal:
            valNow = reading - lastVal
#            mc.postToChat("Reading is bigger than lastval by " + str(valNow))
            bar = lastVal + valNow
            barchart = bar - level
#            led1.write(HIGH)
#            led2.write(HIGH)
#            led3.write(HIGH)
#            mc.postToChat("Bar is now this big " + str(bar) + "we draw it")

            drawblocks(startx, starty, startz, startx+2, starty+barchart, startz+2, 89)
            
        elif reading < lastVal:
         valNow = reading - lastVal
#            mc.postToChat("Reading is less than lastval by " + str(valNow))
 #           mc.postToChat("ValNow " + str(valNow))
         bar = lastVal + valNow
         barchart = bar - level
 #        led1.write(HIGH)
 #        led2.write(LOW)
#         led3.write(LOW)

#            mc.postToChat("Bar is now this big " + str(bar) + " so we draw air blocks from Bar to 200")
         drawblocks(startx, starty+barchart , startz, startx+2, 200, startz+2, 0)
            #mc.postToChat("valNow "+ valNow)
            #mc.postToChat("bar "+ bar)
    else:
         valNow = lastVal
         bar = lastVal + valNow
         barchart = bar - level
#         led1.write(HIGH)
#         led2.write(HIGH)
#         led3.write(LOW)
         drawblocks(startx, lastVal, startz, startx+2, barchart, startz+2, 0)

    lastVal = valNow
#    mc.postToChat("Turbid reading = " + str(read))

def barchart2():
    #setup pins
    ana0reading = ana0.read()
    read2 = ana0reading * 100
    reading2 = read2
    global lastVal2
    level = 74

    if reading2 > lastVal2 + 20 or reading2 < lastVal2 - 20:
        if reading2 > lastVal2:
            valNow = reading2 - lastVal2
            bar = lastVal2 + valNow
            barchart = bar - level
            drawblocks(startx2, starty2, startz2, startx2+2, starty2+barchart, startz2+2, 57)
        elif reading2 < lastVal2:
            valNow = reading2 - lastVal2
            bar = lastVal2 + valNow
            barchart = bar - level
            drawblocks(startx2, starty2+barchart , startz2, startx2+2, 200, startz2+2, 0)

    else:
        valNow = lastVal2
        bar = lastVal2 + valNow
        barchart = bar - level
        drawblocks(startx2, lastVal2, startz2, startx2+2, barchart, startz2+2, 0)

    lastVal2 = valNow
#    mc.postToChat("Temp " + str(valNow))



# setup the player position
playerPos = mc.player.getPos()
#startx = playerPos.x + 5
startx = 4
#starty = playerPos.y + 5
starty = 0
#startz = playerPos.z + 5
startz = 8
startx2 = 1
starty2 = 0
startz2 = 8
mc.postToChat("Player Position ")
mc.postToChat("x = " + str(startx))
mc.postToChat("y = " + str(starty))
mc.postToChat("z = " + str(startz))
#ana1reading = ana1.read()
#mult = ana1reading * 100
#apr1 = mult


while True:
    turbidled1.write(HIGH)
    time.sleep(0.5)
#   barchart1()
    barchart2()

    #analogbarcharter2()
    #mc.postToChat("Walk forward, backward, left, right to control the snake")
    #drawblock(96, 67, 153, 89 )
    #newblock = True
    
