//Include the Arduino Stepper Library
#include <Stepper.h>
// Define Constants
const float STEPS_PER_REV = 32; // Number of steps per internal motor revolution 
const float GEAR_RED = 64;//  Amount of Gear Reduction
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;// Number of steps per geared output rotation
int val; //Define optical switch_1 variable as integer
int val_2; // Define optical switch_2 variable as integer
const int inPin = 4; //Optical switch_1 to digitial pin 4 on arduino
const int inPin2 = 5;//Optical switch_2 to digitial pin 5 on arduino
int StepsRequired;
// The pins used are 8,9,10,11 
// Connected to ULN2003 Motor Driver In1, In2, In3, In4 
// Pins entered in sequence 1-3-2-4 for proper step sequencing
Stepper steppermotor(STEPS_PER_REV, 8, 10, 9, 11);
 
void setup(){
  pinMode(inPin, INPUT);
  pinMode(inPin2, INPUT);
  Serial.begin(9600);
}

void loop(){
  val = digitalRead(inPin);
  val_2 = digitalRead(inPin2);
  
  if (val >= 1 && val_2 == 0){
    while (val_2 == 0){
      // Rotate CCW 
      val = digitalRead(inPin);
      val_2 = digitalRead(inPin2);
      StepsRequired  =  - STEPS_PER_OUT_REV;   
      steppermotor.setSpeed(100);  
      steppermotor.step(StepsRequired);
      delay(1000);//Delays motor for 15 Seconds
      Serial.println("In Counter CW loop");
    }
  }
  else if (val == 0 && val_2 >= 1){
    while (val == 0){
      // Rotate CW 
      val = digitalRead(inPin);
      val_2 = digitalRead(inPin2);
      StepsRequired  =  STEPS_PER_OUT_REV; 
      steppermotor.setSpeed(100);   
      steppermotor.step(StepsRequired);
      delay(1000);//Delays motor for 15 Seconds
      // Rotate CW 1/3 turn 
      Serial.println("In CW loop");
       }
    }
}
