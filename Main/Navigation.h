void setServo(const int angle) {
    long dutyCycle = map(angle, 0, 180, 1675, 8050);
    ledcWrite(6, dutyCycle);
}

void copyFullMap() {
    for (int i = 0; i < 180; i += resolution) {
        distMapFull[i] = distMapActive[i];
    }
}

int findEdge() {
    double gap;
    int angle;

    for (int i = 0; i < 180 - resolution; i += resolution) {
        double tempGap = distMapFull[i] - distMapFull[i + 1];
        if (abs(tempGap) > abs(gap)) {
            gap = tempGap;
            angle = i + 1;
        }
    }

    return angle;
}

double getTOF() {  // Call every 50 ms

    long duration;
    int distance;

    digitalWrite(pinUStrig, LOW);
    delayMicroseconds(5);

    // Trigger the sensor by setting the trigPin high for 10 microseconds:
    digitalWrite(pinUStrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinUStrig, LOW);

    // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
    duration = pulseIn(pinUSecho, HIGH, 3000);
    // Calculate the distance:

    return duration;
}

double getDistance(){
    //double distance = getTOF() * 0.0343 / 2;
    //return distance;
    return wallDist;
}

boolean getIRData() {
    static uint8_t valPulled = 0;
    const uint8_t valTarget = 0x55;
    const long timeout = 220;
    static long lastTime;
    long currentTime;

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
    long currentTime;
    static long lastTime;
    const int USinterval = 100;  //how often does the ultrasound make a measurement (in ms)
    //boolean collision = getIRData();
    static int dir;
    static int angle;

    if (dir == 0) dir = 1;  //set initial value

    currentTime = millis();

    //if (collision) {
    //Will run if TSOP sensor goes off
    //}

    if (currentTime < lastTime + USinterval) return;
    lastTime = currentTime;
    //setServo(angle);

    //Serial.println(angle);

    long duration = getTOF();
    double distance = duration * 0.0343 / 2;

    wallDist = distance;

    Serial.println(wallDist);
    //distMapActive[angle] = distance;

    //angle += resolution * dir;
    //moveRobotSequence(&angle);
/*
    if (angle >= 180) {
        running = true;
        dir = -1;
        //copyFullMap();
    } else if (angle <= 0) {
        dir = 1;
        //copyFullMap();
    }*/
}
