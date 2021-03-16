#include <Arduino.h>

#include "Pinout.h"

#include "Climbing.h"
#include "Drive.h"
#include "Navigation.h"

/* Example code for HC-SR04 ultrasonic distance sensor with Arduino. No library required. More info: https://www.makerguides.com */

// Define variables:

void setup() {
    // Define inputs and outputs:
    pinMode(pinUStrig, OUTPUT);
    pinMode(pinUSecho, INPUT);

    //Begin Serial communication at a baudrate of 9600:
    Serial.begin(9600);
    Serial2.begin(2400, SERIAL_8N1, pinIR);
}
