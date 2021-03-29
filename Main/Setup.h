#include <Arduino.h>

#include "_Pinout.h"

static boolean running = false;
static boolean printReady = true;

const int resolution = 5;

struct mapPoint {
    unsigned long time;
    int angle;
    double distance;
};

static mapPoint distMap[180];

#include "Utilities.h"
#include "Climbing.h"
#include "Drive.h"
#include "Encoder.h"
#include "Navigation.h"

void setup() {
    // Define inputs and outputs:
    pinMode(pinUStrig, OUTPUT);
    pinMode(pinUSecho, INPUT);

    //Begin Serial communication at a baudrate of 9600:
    Serial.begin(9600);
    Serial2.begin(2400, SERIAL_8N1, pinIR);

    //setup PWM for motors
    ledcAttachPin(pinMotorLeftA, 1);  // assign Motors pins to channels
    ledcAttachPin(pinMotorLeftB, 2);
    ledcAttachPin(pinMotorRightA, 3);
    ledcAttachPin(pinMotorRightB, 4);

    // Initialize channels
    // channels 0-15, resolution 1-16 bits, freq limits depend on resolution
    // ledcSetup(uint8_t channel, uint32_t freq, uint8_t resolution_bits);
    ledcSetup(1, 20000, 8);  // 20ms PWM, 8-bit resolution
    ledcSetup(2, 20000, 8);
    ledcSetup(3, 20000, 8);
    ledcSetup(4, 20000, 8);

    ledcAttachPin(pinSonarServo, 6);
    ledcSetup(6, 50, 16);

    setServo(0);
}
