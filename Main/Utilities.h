
void flashStatusLED() {
    long currentTime = millis();    //Store the current time
    static long lastTime;   //what is the last time
    static boolean state;   //what is the button state
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

void buttonHandler() {  //Used for the Push Button
    int value = digitalRead(pinButton);  // read value of push button 1
    static int lastState;   //What is the last state of the push button
    static int currentState;    //What is the current state of the push button
    static long lastTime;   //What was the last time recorded
    int delayLength = 50;   //For how long to wait before checking

    if (value != lastState) {  // if value has changed
        lastTime = millis();   // reset the debouncing timer
    }

    if ((millis() - lastTime) > delayLength) {
        if (value != currentState) {  // if the button state has changed
            currentState = value;     // update current button state

            if (currentState == LOW) {  //If the button is pressed
                ENC_ClearLeftOdometer();    //Clear the encoder values
                ENC_ClearRightOdometer();   
                running = !running;        //Change running bool to opposite value
            }
        }
    }
    lastState = value;  // store button state
}
