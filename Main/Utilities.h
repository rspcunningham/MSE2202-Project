
//USed to flash the blue LED on the esp32 to indicate that the code is on (but the bot may or may not be "running")
void flashStatusLED() {
    long currentTime = millis();    
    static long lastTime;   
    static boolean state;  
    int interval = 500; 

    if (currentTime - lastTime >= interval) {
        lastTime = currentTime;
        state = !state; //change between light on or off
        digitalWrite(pinStatusLED, state);
    }
}

//Used to flicker between the two smart LEDs when the bot is running
void flashSmartLED() {
    long currentTime = millis();
    static long lastTime;
    static boolean state;
    int interval = 100; //how often do the lights switch in ms
    int brightness = 25; //brightness level between 0 and 255

    if (currentTime < lastTime + interval) return; 
    lastTime = currentTime;
    state = !state; //change state between true and false to controll which LED is on

    if (state) {
        SmartLEDs.setPixelColor(0, brightness, brightness, brightness); //turn on all 3 pixels to produce white light
        SmartLEDs.setPixelColor(1, 0, 0, 0);   //turn off the other light
        SmartLEDs.show();
    } else {
        SmartLEDs.setPixelColor(0, 0, 0, 0); //turn off the LED
        SmartLEDs.setPixelColor(1, brightness, brightness, brightness); //turn on all 3 pixels to produce white on the other light
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
