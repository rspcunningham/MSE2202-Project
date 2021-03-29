#include "Setup.h"

void loop() {
    long currentTime = millis();
    static long lastTime;
    int interval = 1;

    flashStatusLED();
    buttonHandler();
    ENC_Averaging();

    if (currentTime < lastTime + interval) return;

    updateEncoder(currentTime);

    if (running) {
        flashSmartLED();

        runMotors(0);
    
        Serial.print("Left: ");
        Serial.print(getLeftSpeed());
        Serial.print(" Right: ");
        Serial.println(getRightSpeed());
        

    } else {
        runRightMotor(0);
        runLeftMotor(0);
        deltaRegisterRight = 0;
        deltaRegisterLeft = 0;
        SmartLEDs.clear();
        SmartLEDs.show();
    }

    /*
    if (running)
        Navigation();
    else if (printReady) {
        for (int i = 0; i < 180; i++) {
            char buf[256];
            sprintf(buf, "Angle: %f, Time: %f, Distance: %f", distMap[i].angle, distMap[i].time, distMap[i].distance);
            //Serial.println(buf);
        }
        printReady = false;
    }
    */
}

//test
