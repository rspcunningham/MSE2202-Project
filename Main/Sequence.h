void moveRobotSequence(double distance){
    switch (robotSequence){
        case 0:
            //*angle=180;
            runMotors2(0,distance); //Let the angle be the way it moves -- 0 should be forward
            //Serial.println(distance);
            robotSequenceCounter++;
            if(robotSequenceCounter==50){
                robotSequence=1;
                robotSequenceCounter=0;
            }
            break;

        case 1:
            runMotors2(1,distance);//Let the angle be the way it moves -- 1 should be right
            robotSequenceCounter++;
            if(robotSequenceCounter==20){
                robotSequence=2;
                robotSequenceCounter=0;
            }
            break;

        case 2:
            runMotors2(2,distance);//Let the angle be the way it moves -- 2 should be left
            break;
        
        case 3: 
            runMotors2(3,distance); //Let the angle be the way it moves -- 3 should be backwards
            break;

    } 
} 

