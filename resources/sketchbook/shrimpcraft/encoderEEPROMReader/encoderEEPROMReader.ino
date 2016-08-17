// Read an LDR on analog pin 5, write the value to EEPROM memory,
// Then 'playback' the data in EEPROM using a rotary encoder
// Rotary encoder push button triggers a read
#include <EEPROM.h>


// initialise a reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;
//From bildr article: http://bildr.org/2012/08/rotary-encoder-arduino/

//these pins can not be changed 2/3 are special interrupt pins
int encoderPin1 = 2;
int encoderPin2 = 3;

// setup the encoder push button
int encoderSwitchPin = 4;
// variables for the interrupts
volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;
// handy int
int lednum = 0;
// bitwise variables
int lastMSB = 0;
int lastLSB = 0;

//set led pins
int led5 = 13;
int led4 = 12;
int led3 = 11;
int led2 = 10;
int led1 = 9;

int sensorPin = A5;    // select the input pin for the LDR
//int ledPin = 13;      // redundant select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

int eeAddress = 0; //Location in EEPROM for the data to be put


void setup() {
  Serial.begin (9600);
//setup interrupts
  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);
  pinMode(encoderSwitchPin, INPUT);

//  pinMode(buttonPin, INPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on
  digitalWrite(encoderSwitchPin, HIGH); //turn pullup resistor on
  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);

// set initial LED state
//  digitalWrite(ledPin, ledState);
// setup LEDs
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  //digitalWrite(led1, LOW);
  //digitalWrite(led2, LOW);
  //digitalWrite(led3, LOW);

  //Serial.println("Starting, lets turn All LED's off");
  //start with no LEDs
  numberOfLEDS(0);
}




void loop(){
  if (digitalRead(encoderSwitchPin)){
    //button is not being pushed
    //So do stuff here
    // Much debugging info for serial
    Serial.print("encoderValue = ");
    Serial.println(encoderValue);
    Serial.print("lastEncoded = ");
    Serial.println(lastEncoded);
  //Serial.println(encoderValue);

  //delay(500);
  //Serial.println(encoderValue);
  //lednum = 0;
  if (encoderValue == lastEncoded){
    Serial.println("Same");
    //Serial.println("Turn all LED's off");
    numberOfLEDS(5);
    delay(50);
    numberOfLEDS(0);
    delay(50);
    numberOfLEDS(5);
    delay(50);
    value = EEPROM.read(address);
    Serial.println("Reading EEPROM at address ");
    Serial.print(address);
    Serial.print("\t");
    Serial.print(value, DEC);
    Serial.println();
    if (value >= 150){
      numberOfLEDS(5);
      delay(200);
      numberOfLEDS(0);
      delay(200);
      numberOfLEDS(5);
      delay(1000);
    } else if (value >= 139){
      numberOfLEDS(4);
      delay(1000);
    } else if (value >= 136){
      numberOfLEDS(3);
      delay(1000);
    }
    address = address;
    Serial.println("Address is now ");
    Serial.print("\t");
    Serial.println(address);
   } else if (encoderValue > lastEncoded){
    Serial.println("More");
    //for (int num = 1; num <= 3; num ++){
    //  numberOfLEDS(3);
    //}
    
    delay(100);
    numberOfLEDS(1);
    delay(150);
    numberOfLEDS(2);
    delay(150);
    numberOfLEDS(3);
    delay(150);
    numberOfLEDS(4);
    delay(150);
    numberOfLEDS(5);
    delay(200);
    numberOfLEDS(0);
    value = EEPROM.read(address);
    Serial.println("Reading EEPROM at address ");
    Serial.print(address);
    Serial.print("\t");
    Serial.print(value, DEC);
    Serial.println();
    if (value >= 150){
      numberOfLEDS(5);
      delay(200);
      numberOfLEDS(0);
      delay(200);
      numberOfLEDS(5);
      delay(1000);
    } else if (value >= 139){
      numberOfLEDS(4);
      delay(1000);
    } else if (value >= 136){
      numberOfLEDS(3);
      delay(1000);
    }
    //address ++;
    address = address + 1;
    encoderValue = lastEncoded;
   } else if (encoderValue < lastEncoded){
    Serial.println("Less");
    
    delay(100);
    numberOfLEDS(5);
    delay(150);
    numberOfLEDS(4);
    delay(150);
    numberOfLEDS(3);
    delay(150);
    numberOfLEDS(2);
    delay(150);
    numberOfLEDS(1);
    delay(200);
    numberOfLEDS(0);
    value = EEPROM.read(address);    
    Serial.println("Reading EEPROM at address ");
    Serial.print(address);
    Serial.print("\t");
    Serial.print(value, DEC);
    Serial.println();
    if (value >= 150){
      numberOfLEDS(5);
      delay(200);
      numberOfLEDS(0);
      delay(200);
      numberOfLEDS(5);
      delay(1000);
    } else if (value >= 139){
      numberOfLEDS(4);
      delay(1000);
    } else if (value >= 136){
      numberOfLEDS(3);
      delay(1000);
    }
    //address --;
    address = address - 1;
    encoderValue= lastEncoded;
 }
  //readEncoders();
  delay(1000);
//  updateEncoder();
}
 else {
  //button is being pushed 
  Serial.println("Button Pushed! Recording!");
  //delay(500);
    int sensorValue = analogRead(sensorPin)/4;
    int liveSensor = analogRead(sensorPin);
  //divide by 4 because analog inputs range from
  //0 to 1023 and each byte of the EEPROM can only hold a
  //value from 0 to 255
  // turn the ledPin on
  Serial.print("Sensor Value:");
  Serial.print("\t");
  Serial.println(sensorValue);
  EEPROM.write(eeAddress, sensorValue);
  Serial.print("Written to EEPROM address ");
  Serial.print("\t");
  Serial.print(eeAddress);
  eeAddress = eeAddress + 1;
  if (eeAddress == EEPROM.length()) {
    eeAddress = 0;
  }
  // wait a bit
  //delay(1000);
  // Flash all LEDS
 digitalWrite(led1, HIGH);
 delay(liveSensor);
 digitalWrite(led1, LOW);
 delay(liveSensor);
 }
    
    
}

//all the bitwise stuff to work out which direction encoder moving

void updateEncoder() {
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
 
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
