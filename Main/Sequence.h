void moveRobotSequence(double distance) {
    static int targetAngle;

    switch (robotDriveSequence) {
        case 0:                      //Drive forward until edge of box
            targetAngle = 0;         //Drive forward
            runMotors(targetAngle);  //Run motors forward
            if (distance <= 0) {     //Does the US has a large distance input(when the US has a really large distance we have it return 0)
                if ((millis() - stopTimer) >= 300) {  //50 -> 200 //Has enough time passed with the US having a large distance
                    robotDriveSequence++;            //Go to next step in the drive sequence
                    stopMotors();                    //Stops the motors and stores a time in stopTimer
                }
            } else {
                stopTimer = millis();   //Stops the motors and stores a time in stopTimer
            }
            break;

        case 1:                                   //Stop (with motors)
            if ((millis() - stopTimer) >= 500) {  //Stop for time(in milliseconds)
                robotDriveSequence++;             //Go to next step in the drive sequence
                stopTimer = millis();       //Stops the motors and stores a time in stopTimer
            }
            break;

        case 2:                                   //Turn Right
            rightTurn();                          //Run Motors Rights
            if ((millis() - stopTimer) >= 400) {  //250 -> 400  //Turn for time(in milliseconds)
                robotDriveSequence++;             //Go to next step in the drive sequence
                stopMotors();                     //Stops the motors and stores a time in stopTimer
                clearEncoders();
            }
            break;

        case 3:                                   //Stop (with motors)
            if ((millis() - stopTimer) >= 500) {  //Stop for time(in milliseconds)
                robotDriveSequence++;             //Go to next step in the drive sequence
                stopTimer = millis();           //Stops the motors and stores a time in stopTimer
                clearEncoders();
            }
            break;

        case 4:                                 //Drive forward a little
            runMotors(targetAngle);             //Run motors forward
            if ((millis() - stopTimer) >= 500) {    //Hard code forward for 500ms so it can get in front of box so US can get a reading then use that
                robotDriveSequence++;  //Go to next step in the drive sequence
                stopMotors();          //Stops the motors and stores a time in stopTimer
            }

            break;

        case 5:                                   //Stop (with motors)
            if ((millis() - stopTimer) >= 500) {  //Stop for time(in milliseconds)
                robotDriveSequence++;             //Go to next step in the drive sequence
                stopTimer = millis();           //Stops the motors and stores a time in stopTimer
            }
            break;

        case 6:                                       //Drive forward until edge of box
            runMotors(targetAngle);                   //Run motors forward
            if (distance <= 0 || distance >= 40) {    //Does the US have a large distance
                if ((millis() - stopTimer) >= 200) {  //100 -> 200  //Has enough time passed with the US having a large distance
                    robotDriveSequence++;             //Go to next step in the drive sequence
                    stopMotors();                     //Stops the motors and stores a time in stopTimer
                }
            }
            break;

        case 7:                                   //Stop (with motors)
            if ((millis() - stopTimer) >= 500) {  //Stop for time(in milliseconds)
                robotDriveSequence++;             //Go to next step in the drive sequence
                stopTimer = millis();              //Stops the motors and stores a time in stopTimer
            }
            break;

        case 8:                                   // Turn Right
            rightTurn();                          //Run Motors Rights
            if ((millis() - stopTimer) >= 400) {  //Turn for time(in milliseconds)
                robotDriveSequence++;             //Go to next step in the drive sequence
                stopMotors();                     //Stops the motors and stores a time in stopTimer
                clearEncoders();
            }
            break;

        case 9:  //Stop (with motors)
            setServo(90);   //Sets the way the US is facing to the front of the Robot
            if ((millis() - stopTimer) >= 500) {  //Stop for time(in milliseconds)
                robotDriveSequence++;             //Go to next step in the drive sequence
                stopTimer = millis();           //Stops the motors and stores a time in stopTimer
                clearEncoders();
            }
            break;

        case 10:                                //Drive forward a little
            runMotors(targetAngle);             //Run motors forward
            if ((millis() - stopTimer) >= 400) {  //Hard code forward for time (ms) so it can get in range of wall so US can get a reading then use that
                robotDriveSequence++;  //Go to next step in the drive sequence
                stopMotors();          //Stops the motors and stores a time in stopTimer
            }

            break;

        case 11:                                  //Stop (with motors)
            if ((millis() - stopTimer) >= 500) {  //Stop for time(in milliseconds)
                robotDriveSequence++;             //Go to next step in the drive sequence
                stopTimer = millis();               //Stops the motors and stores a time in stopTimer
            }
            break;

        case 12:                     //Drive forward until wall
            runMotors(targetAngle);  //Run motors forward
            if (distance <= 5) {    //Does the US has a small distance input
                if ((millis() - stopTimer) >= 100) {  //Has 100ms passed with the US having a small distance
                    robotDriveSequence++;             //Go to next step in the drive sequence
                    stopMotors();                     //Stops the motors and stores a time in stopTimer
                }
            }
            break;

        case 13:                                //Stop (with motors)
            if ((millis() - stopTimer) >= 200) { //Stop for time(in milliseconds)
                robotDriveSequence++;  //Go to next step in the drive sequence
                robotSequence++; // Go to next to ensure that the motors don't run 
            }
            break;
    }
}
