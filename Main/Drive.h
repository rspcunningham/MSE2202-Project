double averageSpeed = 0.2; //in ticks/ms

double gainP = 1;      // % per ticks/ms
double gainI = 1;    // % per ticks
double gainD = 1;    // % `per ticks/ms^2

double gainA = 0.005;  // ticks/ms per degree

int maxPower = 255;
int rightStallPower = 120;  //Lowest speed the motors will run at
int leftStallPower = 120;

const int samples = 5;
uint32_t leftEncHist[samples + 1] = {0};
uint32_t rightEncHist[samples + 1] = {0};
long timeHist[samples + 1] = {0};

double deltaRegisterRight;
double deltaRegisterLeft;
double deltaLastRight;
double deltaLastLeft;
double deltaDeltaRight;
double deltaDeltaLeft;

double getRightSpeed()
{
    double speed = 0;

    for (int i = 1; i < samples; i++)
    {
        int d = rightEncHist[i] - rightEncHist[i - 1];
        int t = timeHist[i] - timeHist[i - 1];
        if (t == 0)
            continue;
        speed += (double)d / t;
    }

    return speed / samples;
}

double getLeftSpeed()
{
    double speed = 0;

    for (int i = 1; i < samples; i++)
    {
        int d = leftEncHist[i] - leftEncHist[i - 1];
        int t = timeHist[i] - timeHist[i - 1];
        if (t == 0)
            continue;
        speed += (double)d / t;
    }

    return speed / samples;
}

double getRightDistance()   //Getting the Right distance of the encoder
{
    double distance = 0;

    for (int i = 1; i < samples; i++)   
    {
        int d = rightEncHist[i] - rightEncHist[i - 1];  //Get each of the distance changes for each sample
        distance += (double)d;  //Store each of the distance changes for each sample
    }
    return distance;
}

double getLeftDistance() //Getting the Left distance of the encoder
{
    double distance = 0;

    for (int i = 1; i < samples; i++) 
    {
        int d = leftEncHist[i] - leftEncHist[i - 1];    //Get each of the distance changes for each sample
        distance += (double)d; //Store each of the distance changes for each sample
    }

    return distance;
}

//Pass value from -1 to 1 to go from full reverse to full forwards
void runRightMotor(double power)
{
    if (power < -1)
        power = -1;
    if (power > 1)
        power = 1;

    double pwmPower = (double)(rightStallPower + power * (maxPower - rightStallPower));

    if (power > 0)
    {
        ledcWrite(3, 0);
        ledcWrite(4, pwmPower);
    }
    else if (power < 0)
    {
        ledcWrite(3, pwmPower);
        ledcWrite(4, 0);
    }
    else
    {
        ledcWrite(3, 0);
        ledcWrite(4, 0);
    }
}

void runLeftMotor(double power)
{
    if (power < -1)
        power = -1;
    if (power > 1)
        power = 1;

    double pwmPower = (double)(leftStallPower + power * (maxPower - leftStallPower));

    if (power > 0)
    {
        ledcWrite(1, pwmPower);
        ledcWrite(2, 0);
    }
    else if (power < 0)
    {
        ledcWrite(1, 0);
        ledcWrite(2, pwmPower);
    }
    else
    {
        ledcWrite(1, 0);
        ledcWrite(2, 0);
    }
}

//runs motors at appropriate speed differential given an angle
//angle should be between -90 and +90; positive angles to the right of centre, negative angles to the left
// angle of 0 indicates straight on. left and right speeds the same
void runMotors(double angle)
{
    //Calculate desired speed delta
    double speedDelta = angle * gainA;

    double targetRight = averageSpeed - speedDelta / 2;
    double targetLeft = averageSpeed + speedDelta / 2;

    //Calculate power needed to get to those speeds (feedback)

    double currentRight = getRightSpeed();
    double currentLeft = getLeftSpeed();

    double deltaRight = targetRight - currentRight;
    double deltaLeft = targetLeft - currentLeft;

    deltaDeltaRight = deltaRight - deltaLastRight;
    deltaDeltaLeft = deltaLeft - deltaLastLeft;

    deltaRegisterRight += deltaRight;
    deltaRegisterLeft += deltaLeft;

    deltaLastRight = deltaRight;
    deltaLastLeft = deltaLeft;

    double powerRight = deltaRight * gainP + deltaRegisterRight * gainI + deltaDeltaRight * gainD;  //power should be between 0 and 1
    double powerLeft = deltaLeft * gainP + deltaRegisterLeft * gainI + deltaDeltaLeft * gainD;

/*
    double error = getLeftDistance() - getRightDistance();
    double c = 0.75;

    powerRight = 100 - (error * c);
    powerLeft = 100 + (error * c);

    */
    //anti-windup

    if (abs(powerRight) > 1)
    {
        powerRight = powerRight / abs(powerRight);
        deltaRegisterRight -= deltaRight;
    }

    if (abs(powerLeft) > 1)
    {
        powerLeft = powerLeft / abs(powerLeft);
        deltaRegisterLeft -= deltaLeft;
    }

    //call left and right motors at those speeds
    runRightMotor(powerRight);
    runLeftMotor(powerLeft);
}

void stopMotors() //Stoping the motors with power (ie no coasting)
{
    ledcWrite(1, 255);
    ledcWrite(2, 255);
    ledcWrite(3, 255);
    ledcWrite(4, 255);
    stopTimer=millis(); //Saving the time it's called
}

void rightTurn(){   
    ledcWrite(1, 255);
    ledcWrite(2, 0);
    ledcWrite(3, 0);
    ledcWrite(4, 0);
}
