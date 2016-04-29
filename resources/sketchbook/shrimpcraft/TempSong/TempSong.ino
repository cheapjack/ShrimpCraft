// Load up the OneWire Library
// This needs to go
// Mac In ~/Documents/Arduino/libraries
// Or in our case ~/ShrimpingIt/projects/sketchbook/libraries
// Linux ~/sketchbook/libraries
// PC My Documents -> Arduino -> libraries
// Wiring from http://bildr.org/2011/07/ds18b20-arduino/
// 
#include <OneWire.h> 
#include <rtttl.h>

//#define COMMANDMAX 19

// RTTTL Programming
//See more RTTTL songs at https://github.com/cefn/non-blocking-rtttl-arduino/blob/master/rtttl/examples/ProgmemSong/ProgmemSong.ino
//or look online for your favourite chimes, being careful to remove unnecessary spaces
//const char song_P[] PROGMEM = "Wham- Wake Me Up:d=4,o=5,b=300:f#5,2a5,2b5.,p,f#5,2a5,b5,2f#5,2d5,p,d5,e5,2f#5,2g5,f#5,e5,d5,2f#5,a5,2f#5,d5,2p";

const char song_P[] PROGMEM = "NellyHot:d=4,o=6,b=225:32p,32a5,8p,32e,16g5,p,32g5,32g_5,8a.5,32e5,8g.5,32p,32g_5,8a.5,32a5,16a.5,32e,16p.,32g_5,8g5,32e,32f_5,16p,32e,16p.,32a5,8p,32e,16g.5,8p,32g_5,8a5,32f_5,16g5,p,32e,32g_5,8a.5,32a5,32a_5,32b5,32p,32e,16p.,32g_5,g5,8p,32a5,32b";

//Define the Piezo player from the rtttl library and define the control pin (6) 
ProgmemPlayer player(6);


int DS18S20_Pin = 8; //DS18S20 Signal pin on digital 8

//Temperature chip i/o Library
OneWire ds(DS18S20_Pin); // on digital pin 8

//set led pins
int led3 = 13;
int led2 = 12;
int led1 = 11;


void setup(void) {
  //Start the serial connection with the computer
  //to view the result open the serial monitor 
  pinMode(led1, OUTPUT);  
  pinMode(led2, OUTPUT); 
  pinMode(led3, OUTPUT);
  Serial.begin(9600);
  player.setSong(song_P);
}

// function to easily assign LEDs
int NumberofLEDS(int num) {
  for (int thisPin = 11; thisPin <= num + 10; thisPin++) {
    digitalWrite(thisPin, HIGH);
    delay(250);               // wait for a second
    digitalWrite(thisPin, LOW);    // turn the LED off by making the voltage LOW
    delay(250); 

  }
}
// Main Loop

void loop(void) {
 float temperature = getTemp();
 Serial.println(temperature);

// LED ligthing according to trigger values
// Change the temperature trigger points below to alter what LEDs light up 
// based on temperature


  if (temperature < 22.0){
   NumberofLEDS(1); 
 } else if (temperature < 28.0){
   NumberofLEDS(2);
   
 } else if (temperature >= 28.0){
   NumberofLEDS(3);
   Serial.println("Playing Wham");
   player.finishSong();
   delay(1000);
   
 } else {
      digitalWrite(led1, LOW);    // turn the LED off by making the voltage LOW
    delay(100);    // wait for a second
    digitalWrite(led2, LOW);    // turn the LED off by making the voltage LOW
    delay(100); 
    digitalWrite(led2, LOW);
 }
 delay(100); //just here to slow down the output so it is easier to read
}



float getTemp(){
 //returns the temperature from one DS18S20 in DEG Celsius

 byte data[12];
 byte addr[8];

 if ( !ds.search(addr)) {
   //no more sensors on chain, reset search
   ds.reset_search();
   return -1000;
 }

 if ( OneWire::crc8( addr, 7) != addr[7]) {
   Serial.println("CRC is not valid!");
   return -1000;
 }

 if ( addr[0] != 0x10 && addr[0] != 0x28) {
   Serial.print("Device is not recognized");
   return -1000;
 }

 ds.reset();
 ds.select(addr);
 ds.write(0x44,1); // start conversion, with parasite power on at the end

 byte present = ds.reset();
 ds.select(addr);  
 ds.write(0xBE); // Read Scratchpad

 
 for (int i = 0; i < 9; i++) { // we need 9 bytes
  data[i] = ds.read();
 }
 
 ds.reset_search();
 
 byte MSB = data[1];
 byte LSB = data[0];

 float tempRead = ((MSB << 8) | LSB); //using two's compliment
 float TemperatureSum = tempRead / 16;
 
 return TemperatureSum;
 
}
