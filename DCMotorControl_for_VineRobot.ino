/*
There are three thing that the robot should be able to do; growing, retracting and stop when needed. 
So the motor is going to be forward in direction for growing and reverse for retracting. 
Also we can control the pace of the motions. 
Starting pace of forward or reverse motion are supposed as 150. Minimum pace determined via testing.
The motor used is simple DC motor with reductor 6V 80mA 130 RPM and 1.1kg*cm operation torque.

To control the robot first the direction of motion is needed which may be W "growing" or S "retracting"
then the pace of the robot can be adjusted between 150 to 255 with 35 increase or decrase.
To stop the robot pressing the space would be enough

the inputs ; 
"W" to growing motion
"S" to retracting
"D" to speed up
"A" to slow done
" " to stop
*/

#include <math.h>


#define OFF               0
    


int motorPin     = 5;  //Motor pin
int motorDirPin  = 2;  //Direction output pin for motor
int motorDirPinS = 3;  //Secondary direction output pin for motor

int minGrowthSpeed  = 150; //Minimum speed required to start growth
int StopSpeed       =   0; //Minimum speed required to stop growth
int minRetractSpeed = 150; //Minimum speed required to start retraction


int motorSpeed   =  0;      //Controls the motor's speed from 0-255
int speedDelta   = 35;      //Controls the change in speed //3 mode for the pace

 
unsigned char theInput = ' '; //we have char type input


void setup() {                
  Serial.begin(9600);
  //define the motor as output
  pinMode(motorPin, OUTPUT);  
  pinMode(motorDirPin, OUTPUT);
  pinMode(motorDirPinS, OUTPUT);  
  //initial conditions off the motor
  analogWrite(motorPin, OFF);            
  digitalWrite(motorDirPin, HIGH);
  digitalWrite(motorDirPinS, LOW);  
}


void loop() {  
  //input is needed for motion      
  theInput = Serial.read();
 
  //the motion -forward or backward- 
  if (theInput == 'W'){               //GROW -forward-
    motorSpeed = minGrowthSpeed ;
    grow(motorSpeed);

     Serial.println("Growing");
  }

  if (theInput == 'S'){               //RETRACT -backward-
    motorSpeed = minRetractSpeed ;
    retract(motorSpeed);

     Serial.println("Retracting");
  }
  
  //speed change
  if (theInput == 'D'){               //INCREASE SPEED     
    motorSpeed += speedDelta;

    Serial.println(motorSpeed);
  }
  
  if (theInput == 'A'){               //DECREASE SPEED     
    motorSpeed -= speedDelta;

    Serial.println(motorSpeed);
  }

  //ending the motion -stopping-
  if (theInput == ' '){               //STOP 
    motorSpeed =  StopSpeed;      
    stop();

    Serial.println("Stopping");
  }
}

//Functions -to adjust direction and motor speed for the given input-

// Tells the vine robot to grow
void grow(int motorSpeed){
    analogWrite(motorPin,motorSpeed); 

    digitalWrite(motorDirPin, HIGH);
    digitalWrite(motorDirPinS, LOW); 
}

// Tells the vine robot to retract
void retract(int motorSpeed){
    analogWrite(motorPin,motorSpeed); 

    digitalWrite(motorDirPin, LOW);
    digitalWrite(motorDirPinS, HIGH);
}

// Stops the vine robot's growth
void stop(){
    analogWrite(motorPin,StopSpeed); 
}
