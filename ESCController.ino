#include <Servo.h>
//Create as much as Servo object you want. 
//You can controll 2 or more Servos at the same time
Servo firstESC, secondESC;  
int ESC MAX=2000, ESC MIN=1000; 
int virtualPotentiometer=0; //To test MAX RPMS 
//int virtualPotentiometer= 1024; // To test MIN RPMS 

void setup() { 
  firstESC.attach(9); // attached to pin 9 
  Serial.begin(9600); // start serial at 9600 baud 
  secondESC.attach(10); //attached to pin 9 
  } 
void loop() { 
  //ESCCalibration(); 
  simulatePotentiometerHIGH(); //MAX RPMS -- make sure to set virtualPot to 0 
  //simulatePotentiometerLOW(); //MIN RPMS -- make sure to set virtualPot to 1024 
}

void ESC_Calibration(){ 
  int value = 0; 
  //Connect your ESC without Arming. 
  firstESC.writeMicroseconds(value); 
  secondESC.writeMicroseconds(value); 
  /* Push the pull rod of throttle in the ESC to the highest 
  ** position to make the ESC enter the setting mode and 
  ** then turn on the ESC.*/ 
  firstESC.writeMicroseconds(2000); //Setting to the highest throttle 
  secondESC.writeMicroseconds(2000); 
  delay(500); 
  firstESC.writeMicroseconds(1000); //Setting to the highest throttle 
  secondESC.writeMicroseconds(1000); 
  //Now you should connect the battery pack. 
  delay(2000); 
  secondESC.writeMicroseconds(1200); 
  firstESC.writeMicroseconds(1200); 
  delay(2000); 
  secondESC.writeMicroseconds(1500); 
  firstESC.writeMicroseconds(1500); 
  delay(2000); 
  secondESC.writeMicroseconds(1700); 
  firstESC.writeMicroseconds(1700); 
  delay(2000);
  secondESC.writeMicroseconds(2000); 
  firstESC.writeMicroseconds(2000); 
  delay(2000); 
}

void writeRPMs(int virtualPotentionmeter){
  int value = map(virtualPotentionmeter, 0, 1023, ESC MIA, ESC_MAX); 
  Serial.println(value); 
  firstESC.writeMicroseconds(value); 
} 

void simulatePotentiometerHIGH(){ //MAX RPMS 
  /* simulates incrementing a potentiometer from 
   ** 0 to 1024 
   ** in 8 seconds each second increment 128 numbers; 
   ** 1000/128 = 7.8125 ms/increment */
   if (virtualPotentiometer < 1024){ 
    delay(7.8125); 
    writeRPMs(virtualPotentiometer); 
    virtualPotentiometer++; 
} 
else{ 
  delay(1000); 
  firstESC.writeMicroseconds(1000); //shutdown at maximum 
  secondESC.writeMicroseconds(1000); 
  } 
} 

void simulatePotentiometerLOW() { //MIN RPMS 
  /* simulates decrementin g a potentiometer from 
  ** 1024 to 0 
  ** in 8 seconds each second decrementing 128 numbers; 
  ** 1000/128 = 7.8125 ms/decrement */ 
  if (virtualPotentiometer > 0){ 
    delay(7.8125); 
    writeRPMs(virtualPotentiometer); 
    virtualPotentiometer--; 
  }
  else{ 
    firstESC.writeMicroseconds(1000); //keep writing 
    }
 }
 

