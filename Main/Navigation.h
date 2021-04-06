//Set the position of the sonar servo
void setServo(const int angle) {
    long dutyCycle = map(angle, 0, 180, 1675, 8050);
    ledcWrite(10, dutyCycle);
}

// the main function to be run to call the ultrasound
void Navigation() {
    long currentTime;
    static long lastTime;
    const int USinterval = 100;  //how often does the ultrasound make a measurement (in ms)

    currentTime = millis();

    //If the specified interval has not elapsed, just return now
    if (currentTime < lastTime + USinterval) return;
    lastTime = currentTime;

    //ping the ultrasound and save the pulse time-of-flight
    long duration = sonar.ping();

    //calculate the distance travelled by the sound wave based on speed of sound in air at 20 C
    //dividing by 2 since the pulse travels to the wall and back
    wallDist = duration * 0.0343 / 2;
}
