int getDistance() {  // Call every 50 ms

    long duration;
    int distance;

    digitalWrite(pinUStrig, LOW);
    delayMicroseconds(5);

    // Trigger the sensor by setting the trigPin high for 10 microseconds:
    digitalWrite(pinUStrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinUStrig, LOW);

    // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
    duration = pulseIn(pinUSecho, HIGH);
    // Calculate the distance:
    distance = duration * 0.034 / 2;

    return distance;
}

boolean getIRData() {
    static uint8_t valPulled = 0;
    const uint8_t valTarget = 0x55;
    const long timeout = 220;
    static long lastTime;
    static long currentTime;

    currentTime = millis();

    if (Serial2.available() > 0) {   // check for incoming data
        valPulled = Serial2.read();  // read the incoming byte
        lastTime = currentTime;      // capture time last byte was received
    } else {
        // check to see if elapsed time exceeds allowable timeout
        if (currentTime - lastTime > timeout) {
            valPulled = 0;  // if so, clear incoming byte
        }
    }

    if (valPulled == valTarget)
        return true;
    else
        return false;
}

void Navigation() {
    static long currentTime;
    static long lastTime;
    const int USinterval = 50;  //how often does the ultrasound make a measurement (in ms)
    boolean collision = getIRData();

    if (collision) {
        //Will run if TSOP sensor goes off
    }

    if (currentTime < lastTime + USinterval) return;

    int distance = getDistance();
}
