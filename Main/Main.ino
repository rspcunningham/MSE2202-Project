#include "Setup.h"

void loop() {
    long currentTime = millis();
    static long lastTime;
    int interval = 1;
    int targetAngle;

    flashStatusLED();
    buttonHandler();
    ENC_Averaging();
    prevDistance=50;
    //Serial.println(distance());

    if (currentTime < lastTime + interval) return;

    moveRobotSequence(distance());
    updateEncoder(currentTime);

    /*
    if (running) {
        flashSmartLED();

        if (climbing) {
            runRightMotor(0);
            runLeftMotor(0);
            Climb();
            return;
        }

        Navigation();

        //Calculate target angle
        switch (robotSequence) {
            case 0:  //getting to first corner of obstacle
                targetAngle = findEdge();
                //some kind of end condition to know it has passed the edge
                break;
            case 1:  //getting to second corner of obstacle
                targetAngle = findEdge();
                //some kind of end condition to know it has passed the edge
                break;
            case 2:  //getting to the wall where the rope is
                if (distMapFull[90] < 5) climbing = true; //once the wall is within 5 cm, start to climb
                else if (distMapFull[0] < 5) targetAngle = 5; // if the obstacle is too close to the left, turn right a bit
                else if (distMapFull[0] > 10) targetAngle = -5; //if the obstacle is too far from the left, turn left a bit
                break;
        }

        runMotors(targetAngle);

    } else {
        runRightMotor(0);
        runLeftMotor(0);
        deltaRegisterRight = 0;
        deltaRegisterLeft = 0;
        SmartLEDs.clear();
        SmartLEDs.show();
    }
    */
}

//test
