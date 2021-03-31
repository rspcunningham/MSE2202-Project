#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "_Pinout.h"

static boolean running = false;
static boolean climbing = false;

const int resolution = 10;

int robotSequence = 0;
int robotSequenceCounter=0;
double prevDistance;
bool firstTime=true;
int counter=0;


/*
struct mapPoint {
    unsigned long time;
    int angle;
    double distance;
};
*/

static double distMapActive[180]; //map that currently has values being added
static double distMapFull[180]; //most recent mapping that has been completed

Adafruit_NeoPixel SmartLEDs(2, pinSmartLED, NEO_GRB + NEO_KHZ400);


void setServo(const int angle) {
    long dutyCycle = map(angle, 0, 180, 1675, 8050);
    ledcWrite(6, dutyCycle);
}

#include "Climbing.h"
#include "Drive.h"
#include "Sequence.h"
#include "Encoder.h"
#include "Navigation.h"
#include "Utilities.h"



void setup() {
    // Define inputs and outputs:
    pinMode(pinUStrig, OUTPUT);
    pinMode(pinUSecho, INPUT);
    pinMode(pinStatusLED, OUTPUT);
    pinMode(pinButton, INPUT_PULLUP);
    pinMode(pinWinch, OUTPUT);
    pinMode(pinEncLeftA, INPUT_PULLUP);
    pinMode(pinEncLeftB, INPUT_PULLUP);
    pinMode(pinEncRightA, INPUT_PULLUP);
    pinMode(pinEncRightB, INPUT_PULLUP);

    //Begin Serial communication at a baudrate of 9600:
    Serial.begin(115200);
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

    // setup encoder interrupts
    attachInterrupt(pinEncLeftA, ENC_isrLeftA, CHANGE);
    attachInterrupt(pinEncLeftB, ENC_isrLeftB, CHANGE);
    attachInterrupt(pinEncRightA, ENC_isrRightA, CHANGE);
    attachInterrupt(pinEncRightB, ENC_isrRightB, CHANGE);

    ENC_btLeftMotorRunningFlag = false;
    ENC_btRightMotorRunningFlag = false;


    ledcAttachPin(pinSonarServo, 6);
    ledcSetup(6, 50, 16);

    setServo(0);

    SmartLEDs.begin();
    SmartLEDs.clear();
    SmartLEDs.show();
}
