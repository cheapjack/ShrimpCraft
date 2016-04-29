
// Simple Walney Listener


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
 

digitalWrite(turbidLED, HIGH);

 int x = analogRead(turbidPin);
 Serial.println(x);
 
 if (x < 200){
   NumberofLEDS(3); 
 } else if (x < 600){
   NumberofLEDS(2);
   
 } else if (x > 600){
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





  delay(250);                                     //waiting a second
}


