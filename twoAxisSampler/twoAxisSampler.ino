
/*
 12/7/12
 -Samples up to 49 bottles on evenly spaced platform 7x7 bottles
 -hardware consists of Arduino uno, adafruit motor shield v2, datalogging shield
 with RTC.
 -code to be used with 49 bottle fraction collector designed and built by Bric Management www.bricmgmt.com, but can easily be adapted to suit your needs.
*/


#include <Wire.h>
#include<Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include "RTClib.h"
//-------------------------------------------------------------Change time interval here--------------------------------------------
int timeInterval = 35;                            // time in minutes you'd like between samples
int sampleCount = 48;                             //number of sample bottles
//-------------------------------------------------------------Shouldn't need to change anything below this line--------------------
//----------------------------------------------------------------------------------------------------------------------------------

RTC_DS1307 RTC;
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *xAxis = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *yAxis = AFMS.getStepper(200, 2);
int spacing = 500;
int count = 0;
int yLimit = A0;
int xLimit = A1;
int timeDelayMin = 0;
int timeDelayHr = 0;
int actionTimeMin = 0;
int actionTimeHr = 0;
int currentMin = 0;
int currentHr = 0;
void setup()
{
    delay(5000);
    Wire.begin();
    RTC.begin();
    AFMS.begin(1000);          
    yAxis->setSpeed(50);        
    xAxis->setSpeed(50);
    setDelay();
    pinMode(yLimit, INPUT_PULLUP);
    pinMode(xLimit, INPUT_PULLUP);
    //----------------------------- homing routine
    while(digitalRead(yLimit) != LOW)
    {
        yAxis->step(1, BACKWARD, SINGLE);
    }
    yAxis->step(100, FORWARD, DOUBLE);
    while(digitalRead(xLimit) != LOW)
    {
        xAxis->step(1, BACKWARD, SINGLE);
    }
    xAxis->step(100, FORWARD, DOUBLE);
    xAxis->release();
    yAxis->release();
    DateTime now = RTC.now();
    currentMin = now.minute();
    currentHr = now.hour();
    setTimes();
}

void loop()
{
    DateTime now = RTC.now(); 
    currentMin = now.minute();
    currentHr = now.hour();
    if ((currentMin == actionTimeMin) && (currentHr == actionTimeHr) && (count < sampleCount)){
        movePlatform();
        setTimes();
        count++;
    } 
}    
void movePlatform ()  {
     if ((count ==6) || (count == 13) || (count==20) || (count == 27) || (count==34) || (count == 41))
       {
            jogYaxis();
        }
        else if(count < 6)
        {
            xForward();
        }
        else if((count > 6) && (count < 13))
        {
            xBackward();
        }
        else if ((count > 13) && (count < 20))  {
            xForward();
        }
        else if ((count > 20) && (count < 27)) {
            xBackward();
        }
        else if ((count > 27) && (count < 34))  {
            xForward();
        }
        else if ((count >34) && (count < 41))  {
            xBackward();
        }
        else if ((count > 41) && (count < 48)) {
            xForward();
        }
    }
void jogYaxis(){
    yAxis->step(spacing, FORWARD, SINGLE);
    yAxis->release();
}
void xForward()
   {
       xAxis->step(spacing, FORWARD, SINGLE);
       xAxis->release();
   }
   
void xBackward()
   {
       xAxis->step(spacing, BACKWARD, SINGLE);
       xAxis->release();  
 }
void setTimes()
{
  int nextMoveMin = currentMin + timeDelayMin;
  int nextMoveHr = currentHr + timeDelayHr;
  if (nextMoveMin >= 60)
   {
   nextMoveMin = nextMoveMin - 60;   
   nextMoveHr = currentHr +1;  
  } 
  if (nextMoveHr >=24){
    nextMoveHr = nextMoveHr -24;
  }
  actionTimeMin = nextMoveMin;
  actionTimeHr = nextMoveHr;
}
void setDelay()
{
 timeDelayMin = timeInterval % 60;
 timeDelayHr = (timeInterval - timeDelayMin)/60;
}
              

















