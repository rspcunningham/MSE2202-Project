void setServo(const int angle) {
    long dutyCycle = map(angle, 0, 180, 1675, 8050);
    ledcWrite(6, dutyCycle);
}

int getTOF() {  // Call every 50 ms

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

    return duration;
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
    static int dir;
    static int angle;

    if (dir == 0) dir = 1;  //set initial value

    currentTime = millis();

    if (collision) {
        //Will run if TSOP sensor goes off
    }

    if (currentTime < lastTime + USinterval) return;
    lastTime = currentTime;
    setServo(angle);

    long duration = getTOF();
    double distance = duration * 0.0343 / 2;

    Serial.println(distance);
    /*
    distMap[angle].time = currentTime;
    distMap[angle].angle = angle;
    distMap[angle].distance = distance;
*/
    //angle += resolution * dir;
    moveRobotSequence(&angle);
    if (angle > 180) dir = -1;
    //if (angle > 180) running = false;
    if (angle < 0) dir = 1;
}
