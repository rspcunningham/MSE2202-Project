//desired target speed for stragiht-line driving (max is about 0.35 ticks/ms)
double averageSpeed = 0.2;  //in ticks/ms

//gain values for the PID controller
double gainP = 0;  // % per ticks/ms
double gainI = 3;  // % per ticks
double gainD = 0;  // % per ticks/ms^2

double gainA = 0.005;  // ticks/ms per degree

//bounds for PWM values
int maxPower = 255;
int rightStallPower = 120;  //Lowest power that will still get the motor to barely turn
int leftStallPower = 120;

//set up values for first in last out stack
const int samples = 5;
uint32_t leftEncHist[samples + 1] = {0};
uint32_t rightEncHist[samples + 1] = {0};
long timeHist[samples + 1] = {0};

//setting up some variables for the PID controller
double deltaRegisterRight;
double deltaRegisterLeft;
double deltaLastRight;
double deltaLastLeft;
double deltaDeltaRight;
double deltaDeltaLeft;

//calculate right wheel speed based on FILO stack, averaged over 5 instacnes
double getRightSpeed() {
    double speed = 0;

    for (int i = 1; i < samples; i++) {
        int d = rightEncHist[i] - rightEncHist[i - 1];
        int t = timeHist[i] - timeHist[i - 1];
        if (t == 0)
            continue;
        speed += (double)d / t;
    }

    return speed / samples;
}

//calculate left wheel speed based on FILO stack, averaged over 5 instacnes
double getLeftSpeed() {
    double speed = 0;

    for (int i = 1; i < samples; i++) {
        int d = leftEncHist[i] - leftEncHist[i - 1];
        int t = timeHist[i] - timeHist[i - 1];
        if (t == 0)
            continue;
        speed += (double)d / t;
    }

    return speed / samples;
}

//Pass value from -1 to 1 to go from full reverse to full forwards
void runRightMotor(double power) {
    //Make sure values passed are legal
    if (power < -1)
        power = -1;
    if (power > 1)
        power = 1;

    double pwmPower = (double)(rightStallPower + power * (maxPower - rightStallPower));  //Calculate the pwm value to write to the motors between bounds

    //Writing to the motors
    if (power > 0) {
        ledcWrite(3, 0);
        ledcWrite(4, pwmPower);
    } else if (power < 0) {
        ledcWrite(3, pwmPower);
        ledcWrite(4, 0);
    } else {
        ledcWrite(3, 0);
        ledcWrite(4, 0);
    }
}

//Pass value from -1 to 1 to go from full reverse to full forwards
void runLeftMotor(double power) {
    //Make sure values passed are legal
    if (power < -1)
        power = -1;
    if (power > 1)
        power = 1;

    double pwmPower = (double)(leftStallPower + power * (maxPower - leftStallPower));  //Calculate the pwm value to write to the motors between bounds

    //Writing to the motors
    if (power > 0) {
        ledcWrite(1, pwmPower);
        ledcWrite(2, 0);
    } else if (power < 0) {
        ledcWrite(1, 0);
        ledcWrite(2, pwmPower);
    } else {
        ledcWrite(1, 0);
        ledcWrite(2, 0);
    }
}

//runs motors at appropriate speed differential given an angle
//angle should be between -90 and +90; positive angles to the right of centre, negative angles to the left
// angle of 0 indicates straight on. left and right speeds the same
void runMotors(double angle) {
    //Calculate target speeds (in encoder ticks/ms) for the left and right wheels
    double speedDelta = angle * gainA;  //desired difference in right and left wheel speeds (to dirve at a slight angle if needed)

    double targetRight = averageSpeed - speedDelta / 2;
    double targetLeft = averageSpeed + speedDelta / 2;

    //Calculate power needed to get to the target speeds based on speed delta (PID feedback controller)

    double currentRight = getRightSpeed();  //get current speeds from positions and times in first in last out stacks
    double currentLeft = getLeftSpeed();

    double deltaRight = targetRight - currentRight;  //calculate current speed error (P)
    double deltaLeft = targetLeft - currentLeft;

    deltaRegisterRight += deltaRight;  //calculate integrated error over time (I)
    deltaRegisterLeft += deltaLeft;

    deltaDeltaRight = deltaRight - deltaLastRight;  //calculate rate of error change (D)
    deltaDeltaLeft = deltaLeft - deltaLastLeft;

    deltaLastRight = deltaRight;
    deltaLastLeft = deltaLeft;

    //calculate the desired power to be sent to each wheel, from 0 to 1
    double powerRight = deltaRight * gainP + deltaRegisterRight * gainI + deltaDeltaRight * gainD;
    double powerLeft = deltaLeft * gainP + deltaRegisterLeft * gainI + deltaDeltaLeft * gainD;

    //anti-windup in case of motor saturation

    if (abs(powerRight) > 1) {
        powerRight = powerRight / abs(powerRight);
        deltaRegisterRight -= deltaRight;
    }

    if (abs(powerLeft) > 1) {
        powerLeft = powerLeft / abs(powerLeft);
        deltaRegisterLeft -= deltaLeft;
    }

    //call left and right motors at those power levels
    runRightMotor(powerRight);
    runLeftMotor(powerLeft);
}

//Stoping the motors with power (ie no coasting)
void stopMotors() {
    ledcWrite(1, 255);
    ledcWrite(2, 255);
    ledcWrite(3, 255);
    ledcWrite(4, 255);
}

//turn on only the left motor, at full power, to do a turn without moving forward
void rightTurn() {
    ledcWrite(1, 255);
    ledcWrite(2, 0);
    ledcWrite(3, 0);
    ledcWrite(4, 0);
}
