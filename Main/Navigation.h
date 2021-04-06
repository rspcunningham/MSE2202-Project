//Set the position of the sonar servo
void setServo(const int angle) {
    long dutyCycle = map(angle, 0, 180, 1675, 8050);
    ledcWrite(10, dutyCycle);
}

//send a ping with the ultrasound and calculate the pulse's time of flight in ms
// do not call more than once per 50 ms
double getTOF() { 

    long duration;
    int distance;

    //hold the trigger pin low for 5 us
    digitalWrite(pinUStrig, LOW);
    delayMicroseconds(5);

    //Then set the trigger pin high for 10 us to send solic pulse
    digitalWrite(pinUStrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinUStrig, LOW);

    //the echo pin is set high by the sensor for the duration of the time of flight, pulseIn() gets that time
    duration = pulseIn(pinUSecho, HIGH, 5000); //if the delay is more than 5 ms then stop waiting (~ 1.4 m which is longer than distances we need to measure)

    return duration;
}

// the main function to be run to call the ultrasound
void Navigation() {
    long currentTime;
    static long lastTime;
    const int USinterval = 100;  //how often does the ultrasound make a measurement (in ms)

    currentTime = millis();

    if (currentTime < lastTime + USinterval) return; //If the specified interval has not elapsed, just return now
    lastTime = currentTime;

    long duration = getTOF(); //ping the ultrasound and save the time-of-flight
    
    //calculate the distance travelled by the sound wave based on speed of sound in air at 20 C
    //dividing by 2 since the pulse travels to the wall and back
    double distance = duration * 0.0343 / 2; 

    wallDist = distance; //set the global wallDist variable to this calculated distance
}
