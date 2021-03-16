int maxPower = 255;
int rightStallPower = 120;
int leftStallPower = 120;

//Pass value from -1 to 1 to go from full reverse to full forwards
void runRightMotor(double power) { 
    int pwmPower = (int)(rightStallPower + power * (maxPower - rightStallPower));

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
    int pwmPower = (int)(leftStallPower + power * (maxPower - leftStallPower));

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