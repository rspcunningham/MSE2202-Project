void moveRobotSequence(double distance){
    switch (robotSequence){
        case 0:
            //*angle=180;
            runMotors2(0,distance); //Let the angle be the way it moves -- 0 should be forward
            //Serial.println(distance);
            robotSequenceCounter++;
            if(robotSequenceCounter==950){
                robotSequence=1;
                robotSequenceCounter=0;
            }
            break;

         case 1:
            runMotors2(4,distance);
            robotSequenceCounter++;
            if(robotSequenceCounter==30){
                robotSequence=2;
                robotSequenceCounter=0;
            }
            break;
        case 2:
            runMotors2(2,distance);//Let the angle be the way it moves -- 2 should be left
            robotSequenceCounter++;
            if(robotSequenceCounter==75){
                robotSequence=3;
                robotSequenceCounter=0;
            }
            break;
        case 3:
            runMotors2(4,distance);
            robotSequenceCounter++;
            if(robotSequenceCounter==30){
                robotSequence=4;
                robotSequenceCounter=0;
            }
            break;
        case 4:
            runMotors2(0,distance); //Let the angle be the way it moves -- 0 should be forward
            robotSequenceCounter++;
            if(robotSequenceCounter==200){
                robotSequence=5;
                robotSequenceCounter=0;
            }
            break;
        case 5:
            runMotors2(4,distance);
            robotSequenceCounter++;
            if(robotSequenceCounter==40){
                robotSequence=6;
                robotSequenceCounter=0;
            }
            break;
        case 6: 
            runMotors2(1,distance);//Let the angle be the way it moves -- 1 should be right
            robotSequenceCounter++;
            if(robotSequenceCounter==50){
                robotSequence=7;
                robotSequenceCounter=0;
            }
            break;
         case 7:
            runMotors2(4,distance);
            robotSequenceCounter++;
            if(robotSequenceCounter==40){
                robotSequence=8;
                robotSequenceCounter=0;
            }
            break;
        case 8: 
            runMotors2(5,distance);//Let the angle be the way it moves -- 
            robotSequenceCounter++;
            if(robotSequenceCounter==100){
                robotSequence=9;
                robotSequenceCounter=0;
            }
            break;
         case 9:
            runMotors2(4,distance);//Let the angle be the way it moves -- 2 should be left
            robotSequenceCounter++;
            if(robotSequenceCounter==30){
                robotSequence=10;
                robotSequenceCounter=0;
            }
            break;
        case 10:
            runMotors2(0,distance); //Let the angle be the way it moves -- 0 should be forward
            robotSequenceCounter++;
            if(robotSequenceCounter==200){
                robotSequence=11;
                robotSequenceCounter=0;
            }
            //runMotors2(2,distance);//Let the angle be the way it moves -- 2 should be left
            break;
         case 11:
            runMotors2(4,distance);//Let the angle be the way it moves -- 2 should be left
            robotSequenceCounter++;
            if(robotSequenceCounter==30){
                robotSequence=12;
                robotSequenceCounter=0;
            }
            break;
        case 12: 
            runMotors2(1,distance);//Let the angle be the way it moves -- 1 should be right
            robotSequenceCounter++;
            if(robotSequenceCounter==75){
                robotSequence=13;
                robotSequenceCounter=0;
            }
            break;
         case 13:
            runMotors2(4,distance);//Let the angle be the way it moves -- 2 should be left
            robotSequenceCounter++;
            if(robotSequenceCounter==30){
                robotSequence=14;
                robotSequenceCounter=0;
            }
            break;
        case 14:
            runMotors2(0,distance); //Let the angle be the way it moves -- 0 should be forward
            robotSequenceCounter++;
            if(robotSequenceCounter==300){
                robotSequence=15;
                robotSequenceCounter=0;
            } 
            //runMotors2(3,distance); //Let the angle be the way it moves -- 3 should be backwards
            break;
        case 15:
            runMotors2(4,distance);
            break;

    } 
} 

