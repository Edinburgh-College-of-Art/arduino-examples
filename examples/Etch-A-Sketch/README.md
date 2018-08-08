# Etch-A-Sketch with Arduino and Processing

This example demonstrates how to communicate between an Arduino and a Processing.org script
over Serial.

Inside are two folders, one for Processing and one for Arduino.

### Requirements

* an Arduino
* Processing
* two potentiometers

### Method
Hook up the potentiometers with GND and VCC on the outside pins and the middle
pin connected to an analog input on the Arduino. In the Arduino Sketch, pins A0 and A1 have been used.

Flash the sketch onto the Arduino then run the Processing sketch.

### Further tinkering
Have a play with the averaging of the input read on the Arduino.
In the Processing script there are some fairly basic conditions to avoid erratic input.
Have a think about possible improvements to these.

Could it be a smoother, more efficient application if Processing asked for values instead
of checking if there are any new ones?
