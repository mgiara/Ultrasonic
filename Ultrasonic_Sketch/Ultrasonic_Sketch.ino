
/**
  Mesa Robotics Organization
  Last Revised by Michael Giaramtio on May 10, 2016
  
  **Note: This sketch has been Over-commented for easier understanding**

  Sketch: HC-SR04 Ultrasonic Sensor Demonstration

  Wiring: Sensor pins are found on the ultrasonic sensor,
          Arduino pins are location on the Arduino board

  (Sensor pin)      (Arduino pin)
     VCC        to        5v
     GND        to       GND
     Echo       to      pin 13
     Trig       to      pin 12



//--------- I'm not familiar with this stuff but it was in this sketch
  Red POS to Arduino pin 11
  Green POS to Arduino pin 10
  560 ohm resistor to both LED NEG and GRD power rail
  More info at: http://goo.gl/kJ8Gl
  Original code improvements to the Ping sketch sourced from Trollmaker.com
  Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
//---------

*/

/**
*      Definitions
*
*  The following section of code referred to as "definitions" associates
*  names, referred to as variables, to specific pins on the Arduino board.
*
*  That is, when we assign 'trigPin' to pin 13 on the Arduino board,
*  every place in the sketch where we send a signal to 'trigPin',
*  that signal will be sent through pin 13.
*/

#define trigPin 13

#define echoPin 12

#define led 11

#define led2 10

/**
*      Setup code
*
*  Setup code runs once, as soon as the Arduino board receives power,
*  before the loop runs.
*/

void setup() {

  /**
  *  The serial object's begin method starts a serial stream
  *  (in this case with the computer the Arduino is attached to)
  *
  *  You can open this duplex (two-way) serial stream by clicking the
  *  "Serial Monitor" magnifying glass in the upper right corner of the
  *  Arduino IDE.
  */
  Serial.begin (9600);

  /**
  *  The pinMode method assigns each pin to either input or output.
  *  ie: pinMode(trigPin, OUTPUT); pre-establishes that the pin assigned
  *  to trigPin (pin 13 from above) will have signals transmitted to it.
  */
  pinMode(trigPin, OUTPUT);
  /**
  *  Converseley to the above trigPin, echoPin (pin 12) will be used
  *  for receiving data From the sensor.
  */
  pinMode(echoPin, INPUT);

  pinMode(led, OUTPUT);

  pinMode(led2, OUTPUT);

}

/**
*      Main loop
*
*  Loop code runs repeatedly until power is removed from the
*  Arduino.
*
*/

void loop() {
  /**
  *  Declaration of two variables of long precision
  *
  *  duration to store the amount of time between 
  *  signal transmission and echo reception.
  *
  *  distance of the object the sound wave is bouncing off of
  *  calculated using the amount of time it takes for the sound 
  *  wave to bounce back.
  */
  long duration, distance;
  
  /**
  *  This method sends DC ground to trigPin.
  */
  digitalWrite(trigPin, LOW);  // Added this line
  
  /**
  *  Pause for 1 500,000th of a second
  */
  delayMicroseconds(2); // Added this line
  
  /**
  *  Send +5v to trigPin (13)
  */
  digitalWrite(trigPin, HIGH);
  
  //--------- Not sure what this is doing here
  //  delayMicroseconds(1000); - Removed this line
  //---------

  /**
  *  pause for 1 100,000th of a second
  */
  delayMicroseconds(10); // Added this line
  
  /**
  *  Send ground to trigPin (13)
  */
  digitalWrite(trigPin, LOW);
  
  /**
  *  The pulseIn method reads a pulse (either HIGH or LOW) 
  *  on a pin. For example, if value is HIGH, pulseIn() waits 
  *  for the pin to go HIGH, starts timing, then waits for 
  *  the pin to go LOW and stops timing. Returns the length 
  *  of the pulse in microseconds or 0 if no complete pulse 
  *  was received within the timeout.
  */
  duration = pulseIn(echoPin, HIGH);

  /**
  *  Calculate the distance of the obstruction based on the 
  *  amount of time it takes to recieve the sound wave back.
  */
  distance = (duration / 2) / 29.1;

  /**
  *  If the obstruction is less than 4 units of measure away,
  */
  if (distance < 4) {  // This is where the LED On/Off happens
  
    /**
    *  Send voltage to pin "led" (the anode of the LED)
    */
    digitalWrite(led, HIGH); // When the Red condition is met, the Green LED should turn off
    /**
    *  Send ground to the cathod of the LED
    */
    digitalWrite(led2, LOW);

  }
  /**
  *  We'll reach this point in the code if the distance measure is Not 
  *  less than 4 units of measure.
  */
  else {
    /**
    *  Sends ground to the LED
    */
    digitalWrite(led, LOW);

    digitalWrite(led2, HIGH);

  }
  /**
  *  The limits of the ultrasonic sensor involve not being able
  *  to read greater than a certain distance, as well as if the 
  *  object is in contact with the sensor.
  *
  *  If the distance measured is in that range (outside of the 
  *  readable limites of the sensor, we'll print "Out of range"
  *  to the serial monitor.
  */
  if (distance >= 200 || distance <= 0) {

    Serial.println("Out of range");

  }
  /**
  *  If the distance is in the appropriate range, print the 
  *  distance to the serial monitor.
  */
  else {

    Serial.print(distance);

    Serial.println(" cm");

  }
  /**
  *  Pause for half of one second.
  */
  delay(500);

}
