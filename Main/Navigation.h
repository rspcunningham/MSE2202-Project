struct mapPoint {
    //time in micros that this data point was collected
    long time;
    //angle with respect to robot that this distance is measured
    double angle;
    //distance measurement
    double distance;
} mapPoint;

//sends ultrasound pulse, receives echo, calculates and returns time of flight
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

    currentTime = micros();

    boolean collision = getIRData();

    if (collision) {
        //Will run if TSOP sensor goes off
    }

    if (currentTime < lastTime + USinterval) return;

    //Move servo to new position

    //time of flight from ultrasound
    long duration = getTOF();
    double distance = duration * 0.0343 / 2;

    long measureTime = currentTime - duration;

    lastTime = currentTime; 
}
