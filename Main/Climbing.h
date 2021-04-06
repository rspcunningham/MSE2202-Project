
//To set the angle of the servo that will hold the rope in the winch
void setLock(const int angle) { 
    long dutyCycle = map(angle, 0, 180, 1675, 8050);
    ledcWrite(8, dutyCycle);
}

//To run the winch motor
void Climb() {
    long currentTime = millis();
    static long lastTime = currentTime;
    int power;
    int upTime = 3000;      //How long for the robot to climb the rope for 
    int holdTime = 10000;   //How long for the robot to stop at the top

    if (currentTime < lastTime + upTime) //initally run at full power
        power = 255;
    else if (currentTime < lastTime + upTime + holdTime)   //once upTime has elapsed, reduce power to hold the robot in the air without winching up further
        power = 170;
    else    //once holdTime has elapsed, cut power to allow the winch to un-wind
        power = 100;

    ledcWrite(7, power);    //Provide power to the motor via PWM control with the nfet
}