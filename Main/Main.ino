#include "Setup.h"  //To include the rest of the headers (Setup includes all the other headers) plus setup code

void loop() {
    long currentTime = millis();    
    static long lastTime;
    static long lastTime2;
    static long lastTime3;
    int interval = 1;
    int hold = 2000;

    flashStatusLED(); 
    buttonHandler();
    ENC_Averaging();

    if (currentTime < lastTime + interval) return;  //If the interval time (1 ms) has not yet passed, return loop() to avoid running further code
    lastTime = currentTime; //let the last time = this loops time to reset timer

    updateEncoder(currentTime); //push current encoder positions and time to first in last out stack
    Navigation(); //run ultrasound sensor

    if (running) {  
        flashSmartLED(); 

        if (climbing) { 
            runRightMotor(0); //Make sure the motors are not running
            runLeftMotor(0);
            Climb(); //Start to climb
            return;
        }

        switch (robotSequence) {    //Used to guide the robot in the order of what to do
            case 0:  //2 second hold
                if (lastTime2 == 0) lastTime2 = currentTime;    
                if (currentTime < lastTime2 + hold) return; //Giving a pause so the robot doesn't start right away
                robotSequence ++; //Go to next step of sequence
                break;
            case 1:  //Driving around obstacle and getting up to the robot
                moveRobotSequence(wallDist);   //drive according to parameters defined by move sequence
                break;
            case 2: 
                setLock(40);    //close the lock servo to hold rope in winch
                if (lastTime3 == 0) lastTime3 = currentTime; //giving a 2 s pause to make sure the bot is still before beginning to climb
                if (currentTime < lastTime3 + hold) return;
                climbing = true;    
                break;
        }

    } else {        // If we are not in the running to go through the sequence. This can reset as well  
    //Reseting all the values that get changed once the push button is pressed and we start 
        runRightMotor(0);   //Stop the motors   
        runLeftMotor(0);
        ledcWrite(7, 0);    //Stop the winch motor
        robotSequence = 0;  //reset to default/starting values
        robotDriveSequence = 0;
        lastTime2 = 0;
        climbing = false;
        deltaRegisterRight = 0;
        deltaRegisterLeft = 0;
        SmartLEDs.clear();  //turn off smart LEDs wich normally falsh to indicate the bot is running
        SmartLEDs.show();
    }
}
