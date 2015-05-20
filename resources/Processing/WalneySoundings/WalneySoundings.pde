/*
arduino_input

Demonstrates the reading of digital and analog pins of an Arduino board
running the StandardFirmata firmware.

To use:
* Using the Arduino software, upload the StandardFirmata example (located
  in Examples > Firmata > StandardFirmata) to your Arduino board.
* Run this sketch and look at the list of serial ports printed in the
  message area below. Note the index of the port corresponding to your
  Arduino board (the numbering starts at 0).  (Unless your Arduino board
  happens to be at index 0 in the list, the sketch probably won't work.
  Stop it and proceed with the instructions.)
* Modify the "arduino = new Arduino(...)" line below, changing the number
  in Arduino.list()[0] to the number corresponding to the serial port of
  your Arduino board.  Alternatively, you can replace Arduino.list()[0]
  with the name of the serial port, in double quotes, e.g. "COM5" on Windows
  or "/dev/tty.usbmodem621" on Mac.
* Run this sketch. The squares show the values of the digital inputs (HIGH
  pins are filled, LOW pins are not). The circles show the values of the
  analog inputs (the bigger the circle, the higher the reading on the
  corresponding analog input pin). The pins are laid out as if the Arduino
  were held with the logo upright (i.e. pin 13 is at the upper left). Note
  that the readings from unconnected pins will fluctuate randomly. 
  
For more information, see: http://playground.arduino.cc/Interfacing/Processing
*/
// import serial and arduino comm stuff for firmata
import processing.serial.*;
import cc.arduino.*;
// import the map images
PFont f;
PImage mapImage;


import ddf.minim.*;
import ddf.minim.signals.*;

Minim minim;
AudioOutput out;
Oscillator osc;
//WaveformRenderer waveform;

//setup arduino
Arduino arduino;
color off = color(4, 79, 111);
color on = color(84, 145, 158);
String resultString;           // string for the results
//setup a multiplier for the analog ins
int factor = 4;
  float myFreq;
  float myAmp;
//float analog1 = arduino.analogRead(1);



void setup() {
  mapImage = loadImage("map.png");

  size(1061, 975);
 f = createFont("Georgia", 24);
  textFont(f);
  // Prints out the available serial ports.
//  println(Arduino.list());
  
  // Modify this line, by changing the "0" to the index of the serial
  // port corresponding to your Arduino board (as it appears in the list
  // printed by the line above).
 arduino = new Arduino(this, Arduino.list()[0], 57600);
//arduino = new Arduino(this, "tty.SLAB_USBtoUART", 57600);
  
  // Alternatively, use the name of the serial port corresponding to your
  // Arduino (in double-quotes), as in the following line.
  //arduino = new Arduino(this, "/dev/tty.usbmodem621", 57600);
  
  // Set the Arduino digital pins as inputs.
  for (int i = 0; i <= 13; i++)
    arduino.pinMode(i, Arduino.INPUT);



  minim = new Minim(this);
  // use the getLineOut method of the Minim object to get an AudioOutput object
  out = minim.getLineOut();


  // see the example AudioOutput >> SawWaveSignal for more about this class
  osc = new SawWave(100, 0.2, out.sampleRate());
  // see the example Polyphonic >> addSignal for more about this
  out.addSignal(osc);
  
  //waveform = new WaveformRenderer();
  // see the example Recordable >> addListener for more about this
  //out.addListener(waveform); 



}

void draw() {
  background(off);
  image(mapImage, 0, 0);
  noStroke();


 // play
    myFreq = arduino.analogRead(1);
    myAmp = arduino.analogRead(0);
    float normAmp = norm(myAmp, 0, 1);

 if ( out.hasControl(Controller.PAN) )
  {
    // map the mouse position to the range of the pan
    float val = map(myFreq, 0, 1000, out.pan().getMinimum(), out.pan().getMaximum());
    out.pan().setValue(val);
  }
/*  

  // Draw a filled box for each digital pin that's HIGH (5 volts).
  for (int i = 0; i <= 13; i++) {
    if (arduino.digitalRead(i) == Arduino.HIGH)
      fill(on);
    else
      fill(off);
      
    rect(420 - i * 30, 30, 20, 20);
  }
  
  */

textSize(32);
text("Left", 350, 430); 
text("Right", 180, 180); 




  // Draw a circle whose size corresponds to the value of an analog input.
//  noFill();
//  for (int i = 1; i <= 2; i++) {
    ellipse(440, 500, arduino.analogRead(1) / factor, arduino.analogRead(1) / factor);
    ellipse(300, 350, arduino.analogRead(0) / factor, arduino.analogRead(0) / factor);





  //}
}

