/*
   RECore Library
   Stepping motor example

   All motor unit use stepping motor mode.

*/

#include <RECoreLibrary.h>

RECoreLibrary recore;

void setup() {
  //init motor type stepping mode
  //stepping mode need step/rev
  //setMotorType(unit, stepping, step/rev)
  //example set 200step/rev
  recore.setMotorType(MOTOR_UNIT_A, STEPPING, 200);
  recore.setMotorType(MOTOR_UNIT_B, STEPPING, 200);

  //set all motor current limit
  //setMotorCurrent(current);
  //current range : 0 ~ 1500

  //example set 300mA
  recore.setMotorCurrent(300);
}

void loop() {
  //set Stepping speed
  //keep rotate stepping motor
  //setSteppingSpeed(motor unit, set speed, dir);
  //motor unit : MOTOR_UNIT_A , MOTOR_UNIT_B
  //set speed : set min^-1
  //dir : true , false

  //example set MOTOR_UNIT_A 200min^-1
  recore.setSteppingSpeed(MOTOR_UNIT_A, 200, true);
  delay(1000);
  
  recore.setSteppingSpeed(MOTOR_UNIT_A, 0, true);
  delay(1000);
  
  //set Stepping steps
  //Rotate set value times
  //setSteppingSpeed(motor unit, set speed, rotate value);
  //motor unit : MOTOR_UNIT_A , MOTOR_UNIT_B
  //set speed : set min^-1
  //rotate value : int32_t
  recore.setSteppingSteps(MOTOR_UNIT_A, 200, 200);
  delay(1000);
}
