#include <Arduino.h> //need to include this so visual studio IDE knows I am writing in arduino and not just c++
#include <Adafruit_NeoPixel.h> //library to run the smart LEDs
#include <NewPing.h> //Library to run the ultrasound sensor with pin interrupts (no delay functions)
#include "_Pinout.h" //contains pin definitions for every pin number used

static boolean running = false;     
static boolean climbing = false;

volatile int32_t ENC_vi32LeftOdometer;  //Given to us from Naish - Left Encoder Value
volatile int32_t ENC_vi32RightOdometer; //Given to us from Naish - Right Encoder Value

int robotSequence = 0;  //Used to know where in the overall sequence the robot is
int robotDriveSequence = 0;   // Used to know where in the the drive sequence we are which is apart of the overall sequence
double stopTimer = 0; //Used to time parts of the drive sequence
double wallDist = 0;    //How far are we from the wall

Adafruit_NeoPixel SmartLEDs(2, pinSmartLED, NEO_GRB + NEO_KHZ400);  //Adding the Smart LED's
NewPing sonar(pinUStrig, pinUSecho, 100); //Add the sonar object, max distance 100 cm

#include "Climbing.h"   //Addng all our header files (Used to make the code easier to read (Better Practice))
#include "Drive.h"
#include "Encoder.h"
#include "Navigation.h"
#include "Utilities.h"
#include "Sequence.h"

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

    //Begin Serial communication at a baudrate of 115200:
    Serial.begin(115200);

    //setup PWM for driving motors
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

    //setup servos
    ledcAttachPin(pinSonarServo, 10);
    ledcSetup(10, 50, 16);
    setServo(10);

    ledcAttachPin(pinLockServo, 8);
    ledcSetup(8, 50, 16);
    setLock(90);

    //setup climbing motor
    ledcAttachPin(pinWinch, 7);
    ledcSetup(7, 20000, 8);

    //set up the smart LEDS, dont turn them on to start
    SmartLEDs.begin();  
    SmartLEDs.clear();
    SmartLEDs.show();
}
