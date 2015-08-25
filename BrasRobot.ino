// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 

#define STOP 0
 
Servo BaseServoRight;  // create servo object to control a servo 
Servo BaseServoLeft;  // create servo object to control a servo 
Servo MiddleServoBottom;  // create servo object to control a servo 
Servo MiddleServoHight;  // create servo object to control a servo 
 
int PotBaseArm = 0;    // analog pin used to connect the potentiometer
int PotMiddleArm = 1;  // analog pin used to connect the potentiometer
int PotHightArm = 2;   // analog pin used to connect the potentiometer
int PotSpeedClaw = 3;  // analog pin used to connect the potentiometer
int ButtonClaw = 4;   // analog pin used to connect the potentiometer

int PosBase;      // variable to read the value from the analog pin
int BaseRight, BaseLeft;
int PosMiddle;    // variable to read the value from the analog pin 
int PosHight;     // variable to read the value from the analog pin 
int SpeedClaw;    // variable to read the value from the analog pin 
int EnableClaw;
 
void setup() 
{ 
  Serial.begin(9600);
  Serial.write("test");
  BaseServoRight.attach(3);    // attaches the servo on pin 9 to the servo object 
  BaseServoLeft.attach(5);    // attaches the servo on pin 9 to the servo object
  MiddleServoBottom.attach(6);    // attaches the servo on pin 9 to the servo object
  MiddleServoHight.attach(9);    // attaches the servo on pin 9 to the servo object
  pinMode(11, OUTPUT);  //fixe la broche en sortie
  pinMode(12, INPUT);  //fixe la broche en entree
} 
 
void loop() 
{ 
  PosBase = analogRead(PotBaseArm);          // reads the value of the potentiometer (value between 0 and 1023) 
  PosMiddle = analogRead(PotMiddleArm);      // reads the value of the potentiometer (value between 0 and 1023) 
  PosHight = analogRead(PotHightArm);        // reads the value of the potentiometer (value between 0 and 1023) 
  SpeedClaw = analogRead(PotSpeedClaw);      // reads the value of the potentiometer (value between 0 and 1023) 
  
  EnableClaw = digitalRead(ButtonClaw);
  
  BaseLeft = map(PosBase, 0, 1023, 0, 179);      // scale it to use it with the servo (value between 0 and 180) 
  BaseRight = map(PosBase, 0, 1023, 179, 0);     // scale it to use it with the servo (value between 0 and 180)
  PosMiddle = map(PosMiddle, 0, 1023, 0, 179);   // scale it to use it with the servo (value between 0 and 180)
  PosHight = map(PosHight, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180)
  SpeedClaw = map(SpeedClaw, 0, 1023, 0, 179);   // scale it to use it with the servo (value between 0 and 180)
  
 
  BaseServoRight.write(BaseRight);
  BaseServoLeft.write(BaseLeft);
  MiddleServoBottom.write(PosMiddle);
  MiddleServoHight.write(PosHight);
  
  if(!EnableClaw)
  {
    analogWrite(11,SpeedClaw); 
  }
  else
  {
    analogWrite(11,STOP);
  }
  Serial.write(SpeedClaw);
  delay(15);                           // waits for the servo to get there 
} 
