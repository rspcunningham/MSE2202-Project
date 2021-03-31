double averageSpeed = 0.2;  //in ticks/ms

double gainP = 0.1;      // % per ticks/ms
double gainI = 0.1;    // % per ticks
double gainD = 1;    // % per ticks/ms^2
double gainA = 0.005;  // ticks/ms per degree

int maxPower = 255;
int rightStallPower = 120;
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

double getRightSpeed() {
    double speed = 0;

    for (int i = 1; i < samples; i++) {
        int d = rightEncHist[i] - rightEncHist[i - 1];
        int t = timeHist[i] - timeHist[i - 1];
        if (t == 0) continue;
        speed += (double)d / t;
    }

    return speed / samples;
}

double getLeftSpeed() {
    double speed = 0;

    for (int i = 1; i < samples; i++) {
        int d = leftEncHist[i] - leftEncHist[i - 1];
        int t = timeHist[i] - timeHist[i - 1];
        if (t == 0) continue;
        speed += (double)d / t;
    }

    return speed / samples;
}

//Pass value from -1 to 1 to go from full reverse to full forwards
void runRightMotor(double power) {
    if (power < -1) power = -1;
    if (power > 1) power = 1;

    double pwmPower = (double)(rightStallPower + power * (maxPower - rightStallPower));

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

void runLeftMotor(double power) {
    if (power < -1) power = -1;
    if (power > 1) power = 1;

    double pwmPower = (double)(leftStallPower + power * (maxPower - leftStallPower));

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

    double powerRight = deltaRight * gainP + deltaRegisterRight * gainI;// + deltaDeltaRight * gainD;  //power should be between 0 and 1
    double powerLeft = deltaLeft * gainP + deltaRegisterLeft * gainI;// + deltaDeltaLeft * gainD;

    //anti-windup

    if (abs(powerRight) > 1) {
        powerRight = powerRight / abs(powerRight);
        deltaRegisterRight -= deltaRight;
    }

    if (abs(powerLeft) > 1) {
        powerLeft = powerLeft/ abs(powerLeft);
        deltaRegisterLeft -= deltaLeft;
    }

    //call left and right motors at those speeds
/*
    Serial.print("Left: ");
    Serial.print(powerLeft);
    Serial.print(" Right: ");
    Serial.println(powerRight);
*/
    runRightMotor(powerRight);
    runLeftMotor(powerLeft);
}


//runs motors at appropriate speed differential given an angle
//angle should be between -90 and +90; positive angles to the right of centre, negative angles to the left
// angle of 0 indicates straight on. left and right speeds the same
void runMotors2(double angle,double distance) {
    //Calculate desired speed delta
    double speedDelta = angle * gainA;

    double targetRight = averageSpeed - speedDelta / 2;
    double targetLeft = averageSpeed + speedDelta / 2;

    //Calculate power needed to get to those speeds (feedback)

    double currentRight = getRightSpeed();
    double currentLeft = getLeftSpeed();
    

    /*
    double deltaRight = targetRight - currentRight;
    double deltaLeft = targetLeft - currentLeft;


    deltaDeltaRight = deltaRight - deltaLastRight;
    deltaDeltaLeft = deltaLeft - deltaLastLeft;

    deltaRegisterRight += deltaRight;
    deltaRegisterLeft += deltaLeft;

    deltaLastRight = deltaRight;
    deltaLastLeft = deltaLeft;

    double powerRight = deltaRight * gainP + deltaRegisterRight * gainI;// + deltaDeltaRight * gainD;  //power should be between 0 and 1
    double powerLeft = deltaLeft * gainP + deltaRegisterLeft * gainI;// + deltaDeltaLeft * gainD;
    */

    //anti-windup
/*
    if (abs(powerRight) > 1) {
        powerRight = powerRight / abs(powerRight);
        deltaRegisterRight -= deltaRight;
    }

    if (abs(powerLeft) > 1) {
        powerLeft = powerLeft/ abs(powerLeft);
        deltaRegisterLeft -= deltaLeft;
    }
*/
    //call left and right motors at those speeds
/*
    Serial.print("Left: ");
    Serial.print(powerLeft);
    Serial.print(" Right: ");
    Serial.println(powerRight);
*/  

    double powerRight=5;
    double powerLeft=5;

    if(distance==prevDistance){
        firstTime=true;
        counter=0;
    }
    else{
        if(firstTime==false){
            if(distance>(1.15*prevDistance)){
                counter++;
                powerRight=powerRight -(counter*5);
                powerLeft=1;
            }
            else if((0.85*prevDistance)>distance){
                counter++;
                powerLeft=powerLeft -(counter*5);
                powerRight=1;
            }
            else{
                counter=0;
            }
        }
        counter=0;
        firstTime=false;
    }
    /*
    Serial.print(distance);
    Serial.print(" --- Right ");
    Serial.print(powerRight);
    Serial.print(" --- Left ");
    Serial.println(powerLeft);
    */

    if(angle==0){
        //Serial.println("FORWARD");
    }
    if(angle==1){//Turn Right
        powerRight=-1;
        powerLeft=1;
        //Serial.println("RIGHT");
    }
    if(angle==2){
        powerLeft=-3;
        powerRight=2;
        //Serial.println("LEFT");
    }
    if(angle==3){
        powerRight=-0.9;
        powerLeft=-1;
        //Serial.println("BACKWARD");
    }
    if(angle==4){
        powerLeft=0;
        powerRight=0;
    }
    if(angle==5){
        powerRight=9;
        powerLeft=10;
    }


    //Serial.print(distance);
    //Serial.print(" --- Right ");
    //Serial.print(powerRight);
    //Serial.print(" --- Left ");
    //Serial.println(powerLeft);

    runRightMotor(powerRight);
    runLeftMotor(powerLeft);
}