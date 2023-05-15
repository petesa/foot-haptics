/* Simple example code for Force Sensitive Resistor (FSR) with Arduino. More info: https://www.makerguides.com */
#include <Wire.h>
#include "Adafruit_DRV2605.h"

// Define FSR pin:
#define fsrpin1 A5
#define fsrpin1 A6

Adafruit_DRV2605 drv;

//Define variable to store sensor readings:
uint8_t effect = 3;
int sensorState = 0;        // current state of the button
int lastSensorState = 0;    // previous state of the button
int threshold = 580;        // The sensitivity threshold: the lower, the more sensitive

void setup() {
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);
  if (! drv.begin()) {
    Serial.println("Could not find DRV2605");
    while (1) delay(10);
  }
  drv.selectLibrary(1);
  
  // I2C trigger by sending 'go' command 
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG);
}

void loop() {
  // Read the FSR pin and store the output as fsrreading:
  // sensorState = analogRead(fsrpin) - 580; // Magic number, the resistance we get from the circuit
  if (analogRead(fsrpin1) > threshold || analogRead(fsrpin2) > threshold) {
    sensorState = 1;
  } else {
    sensorState = 0;
  }

  // Print the fsrreading in the serial monitor:
  // Print the string "Analog reading = ".
  Serial.print("Analog reading = ");
  // Print the fsrreading:
  Serial.print(sensorState);


    if (sensorState == 1) {
      if (sensorState != lastSensorState) {
        // set the effect to play
        effect = 1; 
      }
      else {
        effect = 1; 
      }
      drv.setWaveform(0, effect);
      drv.setWaveform(1, 0);       // end waveform

      // play the effect!
      drv.go();
    }
  

  lastSensorState = sensorState;

  Serial.println();

  delay(500); //Delay 500 ms.
}