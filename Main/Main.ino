#include "Setup.h"

void loop() {
    long currentTime = millis();
    static long lastTime;
    static long lastTime2;
    static long lastTime3;
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

        switch (robotSequence) {
            case 0:  //2 second hold
                if (lastTime2 == 0) lastTime2 = currentTime;
                if (currentTime < lastTime2 + hold) return;
                robotSequence = 1;
                break;
            case 1:  //getting around obstacle
                //targetAngle = findEdge();
                moveRobotSequence(getDistance());
                break;
            case 2:
                setLock(40);
                if (lastTime3 == 0) lastTime3 = currentTime;
                if (currentTime < lastTime3 + hold) return;
                climbing = true;
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
