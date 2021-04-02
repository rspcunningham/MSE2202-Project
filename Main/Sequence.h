void moveRobotSequence(double distance){
    switch (robotSequence){
        case 0://Move Foward
            runMotors2(0,distance); //Let the angle be the way it moves -- 0 should be forward
            if((millis()-timeCounter)>=2500){
                robotSequence++;
                timeCounter=millis();
            }
            break;
         case 1://Stop
            runMotors2(4,distance);
            if((millis()-timeCounter)>=100){
                /*if(distance>45){
                    runMotors2(5,distance);
                }
                else if(distance<35){
                    runMotors2(3,distance);
                }
                else{
                    runMotors2(4,distance);
                    robotSequence++;
                    robotSequenceCounter=0;
                }*/
                //runMotors2(4,distance);
                    robotSequence++;
                    timeCounter=millis();
            }
            break;
        case 2://Move Forward without adjustment 
            runMotors2(5,distance); //Let the angle be the way it moves -- 0 should be forward
            if((millis()-timeCounter)>=500){
                robotSequence++;
                timeCounter=millis();
            }
            break;
        case 3://Stop
            runMotors2(4,distance);
            if((millis()-timeCounter)>=100){
                robotSequence++;
                timeCounter=millis();
            }
            break;
        case 4://Turn Right
            //setServo(0);
            runMotors2(1,distance);
            if((millis()-timeCounter)>=750){
                robotSequence++;
                timeCounter=millis();
            }
            break;
        case 5://Stop
            runMotors2(4,distance);
            if((millis()-timeCounter)>=100){
                robotSequence++;
                timeCounter=millis();
            }
            break;
        case 6://Move Forward without adjustment 
            runMotors2(5,distance); //Let the angle be the way it moves -- 0 should be forward
            if((millis()-timeCounter)>=500){
                robotSequence++;
                timeCounter=millis();
            }
            break;
        case 7:// Stop
            runMotors2(4,distance);
            if((millis()-timeCounter)>=100){
                robotSequence++;
                timeCounter=millis();
            }
            break;
        case 8://Turn Right 
            runMotors2(1,distance);//Let the angle be the way it moves -- 1 should be right
            if((millis()-timeCounter)>=750){
                robotSequence++;
                timeCounter=millis();
            }
            break;
         case 9://Stop
            runMotors2(4,distance);
            if((millis()-timeCounter)>=100){
                robotSequence++;
                timeCounter=millis();
            }
            break;
        case 10://Move Forward without adjustment 
            runMotors2(5,distance);//Let the angle be the way it moves -- 
            if((millis()-timeCounter)>=1000){
                robotSequence++;
                timeCounter=millis();
            }
            break;
         case 11://Stop
            runMotors2(4,distance);//Let the angle be the way it moves -- 2 should be left
            if((millis()-timeCounter)>=100){
                robotSequence++;
                timeCounter=millis();
            }
            break;
        case 12://Move Forward
            runMotors2(0,distance); //Let the angle be the way it moves -- 0 should be forward
            if((millis()-timeCounter)>=1000){
                robotSequence++;
                timeCounter=millis();
                
            }
            //runMotors2(2,distance);//Let the angle be the way it moves -- 2 should be left
            break;
        case 13://Stop
            runMotors2(4,distance);//Let the angle be the way it moves -- 2 should be left
            /*            if((millis()-timeCounter)>=100){
                robotSequence++;
                timeCounter=millis();
            }*/
            break;
        case 14://Turn Right
            runMotors2(1,distance);//Let the angle be the way it moves -- 1 should be right
            if((millis()-timeCounter)>=100){
                robotSequence++;
                timeCounter=millis();
            }
            break;
         case 15://Stop
            runMotors2(4,distance);//Let the angle be the way it moves -- 2 should be left
            if((millis()-timeCounter)>=100){
                robotSequence++;
                timeCounter=millis();
            }
            break;
        case 16://Move Forward
            runMotors2(0,distance); //Let the angle be the way it moves -- 0 should be forward
            if((millis()-timeCounter)>=100){
                robotSequence++;
                timeCounter=millis();
            }
            //runMotors2(3,distance); //Let the angle be the way it moves -- 3 should be backwards
            break;
        case 17://Stop
            runMotors2(4,distance);
            break;

    } 
} 

