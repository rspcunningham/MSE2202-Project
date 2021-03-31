void moveRobotSequence(double distance){
    switch (robotSequence){
        case 0://Move Foward
            //*angle=180;
            runMotors2(0,distance); //Let the angle be the way it moves -- 0 should be forward
            robotSequenceCounter++;
            if(robotSequenceCounter>=950){
                setServo(90);
                robotSequence++;
                robotSequenceCounter=0;
            }
            break;

         case 1://Stop
            runMotors2(4,distance);
            robotSequenceCounter++;
            if(robotSequenceCounter>=200){
                if(distance>45){
                    runMotors2(5,distance);
                }
                else if(distance<35){
                    runMotors2(3,distance);
                }
                else{
                    runMotors2(4,distance);
                    robotSequence++;
                    robotSequenceCounter=0;
                }
            }
            break;
        case 2://Stop
            runMotors2(4,distance);
            robotSequenceCounter++;
            if(robotSequenceCounter>=200){
                robotSequence++;
                robotSequenceCounter=0;
            }
        case 3://Turn Left
            setServo(0);
            runMotors2(2,distance);//Let the angle be the way it moves -- 2 should be left
            robotSequenceCounter++;
            if(robotSequenceCounter>=1){
                robotSequence++;
                robotSequenceCounter=0;
            }
            break;
        case 4://Stop
            runMotors2(4,distance);
            robotSequenceCounter++;
            if(robotSequenceCounter==100){
                robotSequence++;
                robotSequenceCounter=0;
            }
            break;
        case 5://Move Forward
            runMotors2(0,distance); //Let the angle be the way it moves -- 0 should be forward
            robotSequenceCounter++;
            if(robotSequenceCounter==100){
                robotSequence++;
                robotSequenceCounter=0;
            }
            break;
        case 6:// Stop
            runMotors2(4,distance);
            robotSequenceCounter++;
            if(robotSequenceCounter==50){
                robotSequence++;
                robotSequenceCounter=0;
            }
            break;
        case 7://Turn Right 
            runMotors2(1,distance);//Let the angle be the way it moves -- 1 should be right
            robotSequenceCounter++;
            if(robotSequenceCounter==100){
                robotSequence++;
                robotSequenceCounter=0;
            }
            break;
         case 8://Stop
            runMotors2(4,distance);
            robotSequenceCounter++;
            if(robotSequenceCounter==40){
                robotSequence++;
                robotSequenceCounter=0;
            }
            break;
        case 9://Move Forward without adjustment 
            runMotors2(5,distance);//Let the angle be the way it moves -- 
            robotSequenceCounter++;
            if(robotSequenceCounter==100){
                robotSequence++;
                robotSequenceCounter=0;
            }
            break;
         case 10://Stop
            runMotors2(4,distance);//Let the angle be the way it moves -- 2 should be left
            robotSequenceCounter++;
            if(robotSequenceCounter==30){
                robotSequence++;
                robotSequenceCounter=0;
            }
            break;
        case 11://Move Forward
            runMotors2(0,distance); //Let the angle be the way it moves -- 0 should be forward
            robotSequenceCounter++;
            if(robotSequenceCounter==200){
                robotSequence++;
                robotSequenceCounter=0;
            }
            //runMotors2(2,distance);//Let the angle be the way it moves -- 2 should be left
            break;
         case 12://Stop
            runMotors2(4,distance);//Let the angle be the way it moves -- 2 should be left
            robotSequenceCounter++;
            if(robotSequenceCounter==30){
                robotSequence++;
                robotSequenceCounter=0;
            }
            break;
        case 13://Turn Right
            runMotors2(1,distance);//Let the angle be the way it moves -- 1 should be right
            robotSequenceCounter++;
            if(robotSequenceCounter==75){
                robotSequence++;
                robotSequenceCounter=0;
            }
            break;
         case 14://Stop
            runMotors2(4,distance);//Let the angle be the way it moves -- 2 should be left
            robotSequenceCounter++;
            if(robotSequenceCounter==30){
                robotSequence++;
                robotSequenceCounter=0;
            }
            break;
        case 15://Move Forward
            runMotors2(0,distance); //Let the angle be the way it moves -- 0 should be forward
            robotSequenceCounter++;
            if(robotSequenceCounter==300){
                robotSequence++;
                robotSequenceCounter=0;
            } 
            //runMotors2(3,distance); //Let the angle be the way it moves -- 3 should be backwards
            break;
        case 16://Stop
            runMotors2(4,distance);
            break;

    } 
} 

