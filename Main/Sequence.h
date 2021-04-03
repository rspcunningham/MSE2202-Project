void moveRobotSequence(double distance) {
    int targetAngle;

    long currentTime = millis();
    static long lastTime;

    switch (robotDriveSequence){
        case 0:                      //Drive forward until edge of box
            targetAngle = 0;         //Drive forward
            runMotors(targetAngle);  //Run motors forward
            //Serial.println(distance);
            Serial.println("0");
            if (distance <=0) {  //Does the US has a large distance input
                if ((currentTime - stopTimer) >= 50) {  //Has 100ms passed with the US having a large distance
                    robotDriveSequence++;               //Go to next step in the drive sequence
                    stopMotors(); //Stop motors
                }
            }
            else{
                stopTimer=millis();
            }
            break;
        
        case 1:     //Stop (with motors)
        Serial.println("1");
            if ((millis() - stopTimer) >= 300) { //Stop for 200ms
                robotDriveSequence++; //Go to next step in the drive sequence
                stopTimer=millis();
            }
            break;
       
        case 2: //Turn Right
        Serial.println("2");
            rightTurn(); //Run Motors Rights
             if ((currentTime - stopTimer) >= 250) {  //Has 100ms passed with the US having a large distance
                    robotDriveSequence++;               //Go to next step in the drive sequence
                    stopMotors(); //Stop motors
                }
            break;
        
        case 3: //Stop (with motors)
        Serial.println("3");
            if ((millis() - stopTimer) >= 300) { //Stop for 200ms
                robotDriveSequence++; //Go to next step in the drive sequence
                stopTimer=millis();
            }
            break;
        
        case 4: //Drive forward until edge of box
            runMotors(targetAngle);  //Run motors forward
            //Serial.println(distance);
            Serial.println("4");
            if (distance <=0) {  //Does the US has a large distance input
                //Serial.println("YESSSSSSSSSS");

                if ((currentTime - lastTime) >= 50) {  //Has 100ms passed with the US having a large distance
                    robotDriveSequence++;               //Go to next step in the drive sequence
                }
            }
            break;
        
        case 5: //Stop (with motors)
            stopMotors(); //Stop motors
            if ((millis() - stopTimer) >= 300) { //Stop for 200ms
                robotDriveSequence++; //Go to next step in the drive sequence
                stopTimer=millis();
            }
            break;
        
        case 6: // Turn Right
            rightTurn(); //Run Motors Rights
             if ((currentTime - stopTimer) >= 250) {  //Has 100ms passed with the US having a large distance
                    robotDriveSequence++;               //Go to next step in the drive sequence
                    stopMotors(); //Stop motors
                }
            break;
        
        case 7: //Stop (with motors)
            if ((millis() - stopTimer) >= 300) { //Stop for 200ms
                robotDriveSequence++; //Go to next step in the drive sequence
                stopTimer=millis();
            }
            break;
        
        case 8: //Drive forward until edge of box
            runMotors(targetAngle);  //Run motors forward
            //Serial.println(distance);
            if (distance <= 30) {  //Does the US has a large distance input
                Serial.println("YESSSSSSSSSS");

                if ((currentTime - lastTime) >= 100) {  //Has 100ms passed with the US having a large distance
                    robotDriveSequence++;               //Go to next step in the drive sequence
                    stopMotors(); //Stop motors
                }
            }
            break;

        case 9: //Stop (with motors)
            if ((millis() - stopTimer) >= 200) { //Stop for 200ms
                robotDriveSequence++; //Go to next step in the drive sequence
            }
            break;

    }
}
