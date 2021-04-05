
void setLock(const int angle) { //To set the angle of the servo that will hold the rope in the winch
    long dutyCycle = map(angle, 0, 180, 1675, 8050);
    ledcWrite(8, dutyCycle);
}


void Climb() {
    long currentTime = millis();
    static long lastTime = currentTime;
    int power;
    int upTime = 3000;      //How long for the robot to climb the rope for 
    int holdTime = 10000;   //How long for the robot to stop at the top

    if (currentTime < lastTime + upTime)
        power = 255;
    else if (currentTime < lastTime + upTime + holdTime)
        power = 170;
    else
        power = 100;

    ledcWrite(7, power);    //Giving the motor power(the NFET)
}