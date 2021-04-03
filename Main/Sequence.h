void moveRobotSequence()
{
    int targetAngle;
    switch (robotDriveSequence)
    {
    case 0://Drive forward until edge of box
        targetAngle = 0; //Drive forward
        runMotors(targetAngle); //Run motors forward
        Serial.println(getDistance());
        if(getDistance()>=500){ //Does the US has a large distance input
            Serial.println("YESSSSSSSSSS");
            double pastBoxTimer=millis(); //Start timer for how long US has had a large distance
            if((millis()-pastBoxTimer)>=100){ //Has 100ms passed with the US having a large distance
                robotDriveSequence++; //Go to next step in the drive sequence
            }
        }
        break;
    case 1:
        stopMotors();
        if((millis()-stopTimer)>=200){
            robotDriveSequence++;
        }
        break;
    case 2:
        //runRightMotor
        break;
    }
}
