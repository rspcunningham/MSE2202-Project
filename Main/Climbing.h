
void setLock(const int angle) {
    long dutyCycle = map(angle, 0, 180, 1675, 8050);
    ledcWrite(8, dutyCycle);
}


void Climb() {
    long currentTime = millis();
    static long lastTime = currentTime;
    int power;
    int upTime = 3000;
    int holdTime = 10000;

    if (currentTime < lastTime + upTime)
        power = 255;
    else if (currentTime < lastTime + upTime + holdTime)
        power = 170;
    else
        power = 100;

    ledcWrite(7, power);
}