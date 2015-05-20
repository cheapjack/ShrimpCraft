
// Simple Walney Listener

//TMP36 Pin Variables
//int sensorPin = 0; //the analog pin the TMP36's Vout (sense) pin is connected to
//the resolution is 10 mV / degree centigrade with a
//500 mV offset to allow for negative temperatures
int turbidPin = A1;

//set led pins
int led = 13;
int led2 = 12;
int led3 = 11;
int turbidLED = 9;



/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
void setup()
{
  Serial.begin(9600);  //Start the serial connection with the computer
  //to view the result open the serial monitor 
  pinMode(led, OUTPUT);  
  pinMode(led2, OUTPUT); 
  pinMode(led3, OUTPUT);  
  pinMode(turbidLED, OUTPUT);
  }


int NumberofLEDS(int num) {
  for (int thisPin = 11; thisPin <= num + 10; thisPin++) {
    digitalWrite(thisPin, HIGH);
    delay(250);               // wait for a second
    digitalWrite(thisPin, LOW);    // turn the LED off by making the voltage LOW
    delay(250); 

  }
}

void loop()                     // run over and over again
{
  /*
  //getting the voltage reading from the temperature sensor
  int reading = analogRead(sensorPin);  
  
  // get the reading from the LDR

  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * 5.0;
  voltage /= 1024.0; 

  // print out the voltage
  Serial.print(voltage); 
  Serial.println(" volts");

  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
  //to degrees ((voltage - 500mV) times 100)
  Serial.print(temperatureC); 
  Serial.println(" degrees C");

  // now convert to Fahrenheit
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print(temperatureF); 
  Serial.println(" degrees F");


  int x = temperatureC;
*/

digitalWrite(turbidLED, HIGH);

 int x = analogRead(turbidPin);
 Serial.println(x);
 
 if (x < 10){
   NumberofLEDS(3); 
 } else if (x < 20){
   NumberofLEDS(2);
   
 } else if (x > 20){
   NumberofLEDS(1); 
   
 } else {
      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(250);    // wait for a second
    digitalWrite(led2, LOW);    // turn the LED off by making the voltage LOW
    delay(250); 
    digitalWrite(led2, LOW);
 }



/*
  switch (x){
  case 675:
    NumberofLEDS(1); 
    break;
  case 700: 
    NumberofLEDS(2);
    break;
  case 800:
    NumberofLEDS(3);
    break;
  default:  
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(250);    // wait for a second
    digitalWrite(led2, LOW);    // turn the LED off by making the voltage LOW
    delay(250); 
    digitalWrite(led2, LOW);    // turn the LED off by making the voltage LOW
  }
*/





  delay(500);                                     //waiting a second
}


