//Include the Arduino Stepper Library
#include <Stepper.h>

#define delaytime 30
#define pin1  8//these are the Arduino pins that we use to activate coils 1-4 of the stepper motor
#define pin2  9
#define pin3  10
#define pin4  11

// Define floats and integers
const float STEPS_PER_REV = 32; // Number of steps per internal motor revolution 
const float GEAR_RED = 64;//  Amount of Gear Reduction
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;// Number of steps per geared output rotation
const int inPin = 4; //Optical switch_1 to digitial pin 4 on arduino
const int inPin2 = 5;//Optical switch_2 to digitial pin 5 on arduino
int val; //Define optical switch_1 variable as integer
int val_2; // Define optical switch_2 variable as integer
int StepsRequired;
int pButton = 7; // declares arduino digital input 7 as a push button input
int pbVal = 0; //variable for storing on button state


Stepper steppermotor(STEPS_PER_REV, 8, 10, 9, 11);
 
void setup(){
  pinMode(inPin, INPUT);
  pinMode(inPin2, INPUT);
  pinMode(pButton, INPUT);
  Serial.begin(9600);
}
void Step_A(){
  digitalWrite(pin1, HIGH);//turn on coil 1 
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, LOW); 
}
void Step_B(){
  digitalWrite(pin1, LOW); 
  digitalWrite(pin2, HIGH);//turn on coil 2
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, LOW); 
}
void Step_C(){
  digitalWrite(pin1, LOW); 
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, HIGH); //turn on coil 3
  digitalWrite(pin4, LOW); 
}
void Step_D(){
  digitalWrite(pin1, LOW); 
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, HIGH); //turn on coil 4
}
void step_OFF(){
  digitalWrite(pin1, LOW); //power all coils down
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, LOW); 
}

void pb_increment(){
  pbVal = pbVal+1;
}

void loop(){
  val = digitalRead(inPin);
  val_2 = digitalRead(inPin2);
  if(digitalRead(pButton) == HIGH){
    delay(100);
    if(digitalRead(pButton) == HIGH){
          pb_increment();
          Serial.println(pbVal);
    }
  }
 //Homing Loop
  if (pbVal == 2 && val != 1){
    val = digitalRead(inPin);
    while (val == 0){
      // Rotate CCW 
      val = digitalRead(inPin);
      val_2 = digitalRead(inPin2);
      Step_D();
      delay(10);
      Step_C();
      delay(10);
      Step_B();
      delay(10);
      Step_A();
      delay(10);
      Serial.println("Homing");
    }
    pbVal = 0; //Resets pusbutton variable
  }
  //Rotational Test Start
  if (pbVal == 4 && val == 1){
    if (val >= 1 && val_2 == 0){
      while (val_2 == 0){
        // Rotate CCW 
        val = digitalRead(inPin);
        val_2 = digitalRead(inPin2);
        digitalRead(pbVal);
        Step_D();
        delay(delaytime);
        Step_C();
        delay(delaytime);
        Step_B();
        delay(delaytime);
        Step_A();
        delay(delaytime);
        Serial.println("In Counter CW loop");
       
      if (val == 0 && val_2 >= 1){
        while (val == 0){
          val = digitalRead(inPin);
          val_2 = digitalRead(inPin2);
          digitalRead(pbVal);
          Step_A();
          delay(delaytime);
          Step_B();
          delay(delaytime);
          Step_C();
          delay(delaytime);
          Step_D();
          delay(delaytime);
          // Rotate CW 1/3 turn 
          Serial.println("In CW loop");
          Serial.println(pbVal);
      }
     }
Serial.println("Out of loop");
   }
   //   delay(1000);//1 second pause 
  } 
 }
}

 
