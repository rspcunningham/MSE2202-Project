#include "Setup.h"

void loop() {
    long currentTime = millis();
    updateEncoder(currentTime);

    Navigation();
    Drive();
}