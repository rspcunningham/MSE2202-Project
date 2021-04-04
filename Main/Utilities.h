
void flashStatusLED() {
    long currentTime = millis();
    static long lastTime;
    static boolean state;
    int interval = 500;

    if (currentTime - lastTime >= interval) {
        lastTime = currentTime;
        state = !state;
        digitalWrite(pinStatusLED, state);
    }
}

void flashSmartLED() {
    long currentTime = millis();
    static long lastTime;
    static boolean state;
    int interval = 100;
    int brightness = 25;

    if (currentTime < lastTime + interval) return;
    lastTime = currentTime;
    state = !state;

    if (state) {
        SmartLEDs.setPixelColor(0, brightness, brightness, brightness);
        SmartLEDs.setPixelColor(1, 0, 0, 0);
        SmartLEDs.show();
    } else {
        SmartLEDs.setPixelColor(0, 0, 0, 0);
        SmartLEDs.setPixelColor(1, brightness, brightness, brightness);
        SmartLEDs.show();
    }
}

void buttonHandler() {
    int value = digitalRead(pinButton);  // read value of push button 1
    static int lastState;
    static int currentState;
    static long lastTime;
    int delayLength = 50;

    if (value != lastState) {  // if value has changed
        lastTime = millis();   // reset the debouncing timer
    }

    if ((millis() - lastTime) > delayLength) {
        if (value != currentState) {  // if the button state has changed
            currentState = value;     // update current button state

            if (currentState == LOW) {
                ENC_ClearLeftOdometer();
                ENC_ClearRightOdometer();
                running = !running;
            }
        }
    }
    lastState = value;  // store button state
}
