/*
   RECore Library
   Parallel DC motor example

   All motor unit use parallel DC motor mode.

*/

#include <RECoreLibrary.h>

RECoreLibrary recore;

void setup() {
  //init motor type parallel_dc mode
  recore.setMotorType(MOTOR_UNIT_A, PARALLEL_DC);
  recore.setMotorType(MOTOR_UNIT_B, PARALLEL_DC);

  //set all motor current limit
  //setMotorCurrent(current);
  //current : 0 ~ 1500

  //example set 500mA
  recore.setMotorCurrent(500);

  //set motor brake mode
  //can change motor brake mode
  //setBrakeMode(motor number, brake type);
  //motor number : 0,2 (Parallel mode can set 0 or 2)
  //brake type : COAST , BRAKE (default set brake)
}

void loop() {
  //set Motor speed
  //setMotorSpeed(motor number, motor power);
  //motor number : 0 , 2
  //motor power : -1.0 ~ 0 ~ 1.0
  
  //example set Motor 0 speed forward 50%
  recore.setMotorSpeed(0, 0.5);
  delay(1000);

  //stop motor 0
  recore.setMotorSpeed(0, 0);
  delay(1000);

  //set Motor 0 speed reverse 50%
  recore.setMotorSpeed(0, -0.5);
  delay(1000);

  recore.setMotorSpeed(0, 0);
  delay(1000);
}
