void moveRobotSequence(double distance) {
    int targetAngle;

    switch (robotDriveSequence) {
        case 0:                      //Drive forward until edge of box
            targetAngle = 0;         //Drive forward
            runMotors(targetAngle);  //Run motors forward
            if (distance <= 0) {     //Does the US has a large distance inpu
                if ((millis() - stopTimer) >= 300) {  //50 -> 200
                    //Has 100ms passed with the US having a large distance
                    robotDriveSequence++;            //Go to next step in the drive sequence
                    stopMotors();                    //Stop motors
                }
            } else {
                stopTimer = millis();
            }
            break;

        case 1:                                   //Stop (with motors)
            if ((millis() - stopTimer) >= 500) {  
                //Stop for 200ms
                robotDriveSequence++;             //Go to next step in the drive sequence
                stopTimer = millis();
            }
            break;

        case 2:                                   //Turn Right
            rightTurn();                          //Run Motors Rights
            if ((millis() - stopTimer) >= 500) {  //250 -> 400
                //Has 100ms passed with the US having a large distance
                robotDriveSequence++;             //Go to next step in the drive sequence
                stopMotors();                     //Stop motors
            }
            break;

        case 3:                                   //Stop (with motors)
            if ((millis() - stopTimer) >= 500) {  
                //Stop for 200ms
                robotDriveSequence++;             //Go to next step in the drive sequence
                stopTimer = millis();
            }
            break;

        case 4:                                 //Drive forward a little
            runMotors(targetAngle);             //Run motors forward
            if ((millis() - stopTimer) >= 500) { 
                //Hard code forward for 500ms
                robotDriveSequence++;  //Go to next step in the drive sequence
                stopMotors();          //Stop motors
            }

            break;

        case 5:                                   //Stop (with motors)
            if ((millis() - stopTimer) >= 500) {  
                //Stop for 200ms
                robotDriveSequence++;             //Go to next step in the drive sequence
                stopTimer = millis();
            }
            break;

        case 6:                                       //Drive forward until edge of box
            runMotors(targetAngle);                   //Run motors forward
            if (distance <= 0 || distance >= 40) {    
                //Does the US has a large distance input
                if ((millis() - stopTimer) >= 100) {  
                    //Has 100ms passed with the US having a large distance
                    robotDriveSequence++;             //Go to next step in the drive sequence
                    stopMotors();                     //Stop motors
                }
            }
            break;

        case 7:                                   //Stop (with motors)
            if ((millis() - stopTimer) >= 500) {  
                //Stop for 200ms
                robotDriveSequence++;             //Go to next step in the drive sequence
                stopTimer = millis();
            }
            break;

        case 8:                                   // Turn Right
            rightTurn();                          //Run Motors Rights
            if ((millis() - stopTimer) >= 400) {  
                //Has 100ms passed with the US having a large distance
                robotDriveSequence++;             //Go to next step in the drive sequence
                stopMotors();                     //Stop motors
            }
            break;

        case 9:  //Stop (with motors)
            setServo(90);
            if ((millis() - stopTimer) >= 500) {  
                //Stop for 200ms
                robotDriveSequence++;             //Go to next step in the drive sequence
                stopTimer = millis();
            }
            break;

        case 10:                                //Drive forward a little
            runMotors(targetAngle);             //Run motors forward
            if ((millis() - stopTimer) >= 400) { 
                //Hard code forward for 200ms
                robotDriveSequence++;  //Go to next step in the drive sequence
                stopMotors();          //Stop motors
            }

            break;

        case 11:                                  //Stop (with motors)
            if ((millis() - stopTimer) >= 500) {  
                //Stop for 500ms
                robotDriveSequence++;             //Go to next step in the drive sequence
                stopTimer = millis();
            }
            break;

        case 12:                     //Drive forward until wall
            runMotors(targetAngle);  //Run motors forward
            if (distance <= 10) {    
                //Does the US has a large distance input
                if ((millis() - stopTimer) >= 100) {  
                    //Has 100ms passed with the US having a large distance
                    robotDriveSequence++;             //Go to next step in the drive sequence
                    stopMotors();                     //Stop motors
                }
            }
            break;

        case 13:                                //Stop (with motors)
            if ((millis() - stopTimer) >= 200) { 
                //Stop for 200ms
                robotDriveSequence++;  //Go to next step in the drive sequence
            }
            break;
    }
}
