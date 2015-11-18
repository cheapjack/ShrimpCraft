##Useage

#Basics

There are 2 Arduino sketches included here that correspond to 2 Shrimp kits:
 * `WalneyTemperatureListener.ino` - **CompleteTemperatureSensorBoard**
 * `WalneyTurbiditySensor.ino` - **CompleteTurbiditySensorBoard**

Each kit flashes 3 LEDs in sequence to indicate temperature and turbidity


###CompleteTurbiditySensorBoard

Indicates how much light can travel through a sample of water. The code can be changed to trigger LED events at particular readings. This does not represent whether water is clean but it could be used as an indicator of how much material is suspended in water, not what that material is. 'Healthy' water could be high in particulates, and clear water could still have sewage. Its worth noting this is a highly simplified sensor and not accurate. The description of each LED flash is arbitrary in this sense, but as an indicator its a first step. 

 * **1 LED flash** - Water with relatively high levels of particulates: **'dirty'** 
 * **2 LED flash** - Water with relatively mid levels of particulates: **'acceptable'** 
 * **3 LED flash** - Water with relatively low levels of particulates: **'clean'**

Upload the Arduino sketch `WalneyTurbiditySensor.ino` to your assembled Turbidity shrimp. Read the comments in the Arduino sketch for instructions. It reads ANALOG pin 0 and flashes accordingly

####Minecraft

Currently to visualise these analog readings in minecraft you must upload the Standard Firmata library to the shrimp from the Arduino IDE Examples folder.

Running `python ShrimpCraft/resources/minecraft/HelloTurbidity.py` with `Python 2.7.10` and `pyfirmata` installed will use the mcpi protocol to send messages to the FACT CloudMaker minecraft server providing you have everything correctly installed. You can change the settings in `server.py` to send messages to other minecraft servers either on the raspberry pi or running the Raspberry Juice plugin. 


###CompleteTemperatureSensorBoard

Uses a Dallas DS18S20B Waterproof `OneWire` sensor to flash LEDs to indicate changes in temperature. The code can be changed to trigger LED events at particular readings. This is a relatively accurate reading of air and water temperature. Ideally a 4.7KOhm pull-up Resistor should be placed between the sensor pin and 5V. There are some occasional noisy readings but this can be fixed on re-setting the shrimp.


 * **1 LED flash** - Water with relatively low temperature: **'cold'** 
 * **2 LED flash** - Water with relatively mid temperature: **'room temperature'** 
 * **3 LED flash** - Water with relatively high temperature: **'warm'**

####Minecraft

Currently to visualise these digital readings in minecraft HelloTemperature.py reads the temperature from Serial with the CP2102 USB serial connector 

Running `python ShrimpCraft/resources/minecraft/HelloTurbidity.py` with `Python 2.7.10` installed will use the mcpi protocol to send messages to the FACT CloudMaker minecraft server providing you have everything correctly installed. You can change the settings in `server.py` to send messages to other minecraft servers either on the raspberry pi or running the Raspberry Juice plugin. 


###Requirements

 * Protected Shrimp with additional resistors and parts
 * Python 2.7.10
 * pyfirmata installed with `pip install pyfirmata`
 * A raspberry Pi running a MinecraftPi server or a Minecraft server running the RaspberryJuice plugin
 * Dallas DS18S20B Waterproof sensor
 * Arduino OneWire Library included in this Repo from [Paul Stoffregen](http://www.pjrc.com/teensy/td_libs_OneWire.html)
 * [CP2102 USB drivers](http://shrimping.it/drivers/cp2102/) 


