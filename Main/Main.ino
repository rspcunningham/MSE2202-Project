#include "Setup.h"

void loop() {
    if (running)
        Navigation();
    else if (printReady) {
        for (int i = 0; i < 180; i++) {
            char buf[256];
            sprintf(buf, "Angle: %f, Time: %f, Distance: %f", distMap[i].angle, distMap[i].time, distMap[i].distance);
            Serial.println(buf);
        }
        printReady = false;
    }
}

//test
