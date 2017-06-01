# Useage

![turbids](https://cloud.githubusercontent.com/assets/128456/11256612/c9be04be-8e44-11e5-80ba-bb4769f943f6.png)

## Basics

There are 2 Arduino sketches included here that correspond to 2 Shrimp kits:

 * `WalneyTemperatureListener.ino` - **CompleteTemperatureSensorBoard**
 * `WalneyTurbiditySensor.ino` - **CompleteTurbiditySensorBoard**

Each kit flashes 3 LEDs in sequence to indicate temperature and turbidity

Each kit also prints to serial at 9600 baudrate the Temperature in Celsius and an analog reading from the Turbidity Light Dependent Resistor (LDR)

Once uploaded to the assembled shrimps and connected to a computer the Python modules `HelloTurbidityReady.py` `HelloTemperatureReady.py` read the serial values from the shrimps and build bar graphs at specific points in the CloudMaker minecraft server using the `RaspberryJuice` plugin.

### CompleteTurbiditySensorBoard

Indicates how much light can travel through a sample of water. The code can be changed to trigger LED events at particular readings. This does not represent whether water is clean but it could be used as an indicator of how much material is suspended in water, not what that material is. 'Healthy' water could be high in particulates, and clear water could still have sewage. Its worth noting this is a highly simplified sensor and not accurate. The description of each LED flash is arbitrary in this sense, but as an indicator its a first step.

There’s a more advanced turbidity sensor at [Hackteria](http://hackteria.org/wiki/index.php/DIY_turbidity_meters) 

 * **1 LED flash** - Water with relatively high levels of particulates: **'dirty'** 
 * **2 LED flash** - Water with relatively mid levels of particulates: **'acceptable'** 
 * **3 LED flash** - Water with relatively low levels of particulates: **'clean'**

Upload the Arduino sketch `WalneyTurbiditySensor.ino` to your assembled Turbidity shrimp. Read the comments in the Arduino sketch for instructions. It reads ANALOG pin 0 and flashes accordingly

#### Turbdity in Minecraft

To visualise these analog LDR/turbidity readings in minecraft you run the python module below which reads serial input from the CP2102 USB serial connector. 

Running `python ShrimpCraft/resources/minecraft/HelloTurbidityReady.py` with `Python 2.7.10` will use the mcpi protocol to send messages to the FACT [CloudMaker minecraft server](http://89.34.96.47:8125/) providing you have everything correctly installed. You can change the settings in `server.py` to send messages to other minecraft servers either on the raspberry pi or CraftBukkit/CanaryMod minecraft servers running the Raspberry Juice plugin. 

You can also change where and what minecraft draws in response to the serial inputs in each `.py` module. Explore more at [Stuff About Code](http://www.stuffaboutcode.com/p/minecraft.html)

### CompleteTemperatureSensorBoard

Uses a **Dallas DS18S20B** Waterproof `OneWire` sensor to flash LEDs to indicate changes in temperature. The code can be changed to trigger LED events at particular readings. This is a relatively accurate reading of air and water temperature. Ideally a 4.7KOhm pull-up Resistor should be placed between the sensor pin and 5V. There are some occasional noisy readings but this can be fixed on re-setting the shrimp.

There's a great [tutorial at Bldr](http://bildr.org/2011/07/ds18b20-arduino/) to help with getting started with these powerful sensors.

 * **1 LED flash** - Water with relatively low temperature: **'cold'** 
 * **2 LED flash** - Water with relatively mid temperature: **'room temperature'** 
 * **3 LED flash** - Water with relatively high temperature: **'warm'**

#### Temperature in Minecraft

To visualise these digital readings in minecraft HelloTemperatureReady.py reads the temperature from Serial with the CP2102 USB serial connector 

Running `python ShrimpCraft/resources/minecraft/HelloTemperatureReady.py` with `Python 2.7.10` installed will use the mcpi protocol to send messages to the FACT CloudMaker minecraft server providing you have everything correctly installed. You can change the settings in `server.py` to send messages to other minecraft servers either on the raspberry pi or running CraftBukkit/CanaryMod minecraft servers running the Raspberry Juice plugin. 

You can also change where and what minecraft draws in response to the serial inputs in each `.py` module. Explore more at [Stuff About Code](http://www.stuffaboutcode.com/p/minecraft.html)

### Requirements

 * Protected Shrimp with additional resistors and parts from [Shrimping.it Here](http://start.shrimping.it/kit/shrimp.html)
 * `Python 2.7.10`
 * Optional `pyfirmata` installed with `pip install pyfirmata`
 * A raspberry Pi running a MinecraftPi server or a Minecraft server running the `RaspberryJuice` plugin to receive python `mcpi` commands
 * Dallas DS18S20B Waterproof sensor
 * Arduino `OneWire` Library included in this Repo from [Paul Stoffregen](http://www.pjrc.com/teensy/td_libs_OneWire.html) also available from [here](http://playground.arduino.cc/Learning/OneWire)
 * [CP2102 USB drivers](http://shrimping.it/drivers/cp2102/) for the Shrimping.It flavoured USB to UART interfaces 


