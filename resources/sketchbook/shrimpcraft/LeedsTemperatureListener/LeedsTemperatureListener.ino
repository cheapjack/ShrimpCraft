// Load up the OneWire Library
// This needs to go
// Mac In ~/Documents/Arduino/libraries
// Linux ~/sketchbook/libraries
// PC My Documents -> Arduino -> libraries
// Wiring from http://bildr.org/2011/07/ds18b20-arduino/
// 
#include <OneWire.h> 


int DS18S20_Pin = 8; //DS18S20 Signal pin on digital 8

//Temperature chip i/o Library
OneWire ds(DS18S20_Pin); // on digital pin 8

//set led pins
int led5 = 13;
int led4 = 12;
int led3 = 11;
int led2 = 10;
int led1 = 9;


void setup(void) {
  //Start the serial connection with the computer
  //to view the result open the serial monitor 
  pinMode(led1, OUTPUT);  
  pinMode(led2, OUTPUT); 
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT); 
  pinMode(led5, OUTPUT);
  Serial.begin(9600);
}


// Main Loop

void loop(void) {
 float temperature = getTemp();
 Serial.println(temperature);

// LED ligthing according to trigger values
// Change the temperature trigger points below to alter what LEDs light up 
// based on temperature
//numberOfLEDS(5);
//delay(500);

  if (temperature < 16.0){
   numberOfLEDS(1); 
 } else if (temperature < 24.0 && temperature >= 16.0){
   numberOfLEDS(2);
   //delay(500);
 } else if (temperature > 24.0 && temperature <= 28.0){
   numberOfLEDS(3); 
   //delay(500);
 } else if (temperature > 28.0 && temperature <= 30.0){
   numberOfLEDS(4);
   //delay(500); 
 } else if (temperature > 30.0){
   numberOfLEDS(5);
   //delay(500);
 delay(500); //just here to slow down the output so it is easier to read
}
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

// function to easily assign LEDs
void numberOfLEDS(int num) {
  if (num == 1){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  } else if (num == 2){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  } else if (num == 3){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  } else if (num == 4){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
  } else if (num == 5){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
  } else if (num == 0){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }
}

