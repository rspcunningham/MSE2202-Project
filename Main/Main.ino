#include "Setup.h"

void loop() {
    long currentTime = millis();
    static long lastTime;
    static long lastTime2;
    int interval = 1;
    int hold = 2000;

    flashStatusLED();
    buttonHandler();
    ENC_Averaging();

    if (currentTime < lastTime + interval) return;
    lastTime = currentTime;

    //Serial.println(running);

    updateEncoder(currentTime);
    Navigation();  //dont comment this out anymore

    if (running) {
        flashSmartLED();

        //Serial.print(getLeftSpeed());
        //Serial.println(getRightSpeed());

        if (climbing) {
            runRightMotor(0);
            runLeftMotor(0);
            Climb();
            return;
        }

        //runRightMotor(1);
        //runLeftMotor(1);
        //runMotors(0);

        //Navigation();
        setLock(40);

        if (lastTime2 == 0) lastTime2 = currentTime;
        if (currentTime < lastTime2 + hold) return;
        climbing = true;

        //Serial.println(wallDist);

        //robotSequence = -1;

        //Calculate target angle
        /*
        switch (robotSequence) {
            case 0:  //2 second hold
                if (lastTime2 == 0) lastTime2 = currentTime;
                if (currentTime < lastTime2 + hold) return;
                robotSequence = 1;
                break;
            case 1:  //getting around obstacle
                //targetAngle = findEdge();
                moveRobotSequence(getDistance());
                //some kind of end condition to know it has passed the edge
                break;
            case 2:  //getting to the wall where the rope is
                     /*
                if (distMapFull[90] < 5){
                     climbing = true;  //once the wall is within 5 cm, start to climb
                }
                else if (distMapFull[0] < 5){
                    //targetAngle = 5;  // if the obstacle is too close to the left, turn right a bit
                }
                else if (distMapFull[0] > 10){
                    //targetAngle = -5;  //if the obstacle is too far from the left, turn left a bit
                }
            */
                break;
        }
        

    } else {
        runRightMotor(0);
        runLeftMotor(0);
        ledcWrite(7, 0);
        robotSequence = 0;
        robotDriveSequence = 0;
        lastTime2 = 0;
        climbing = false;
        deltaRegisterRight = 0;
        deltaRegisterLeft = 0;
        SmartLEDs.clear();
        SmartLEDs.show();
    }
}

//test
