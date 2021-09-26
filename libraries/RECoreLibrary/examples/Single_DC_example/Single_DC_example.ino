/*
   RECore Library
   Single DC motor example

   All motor unit use single DC motor mode.

*/

#include <RECoreLibrary.h>

RECoreLibrary recore;

void setup() {
  //init motor type single_dc mode
  recore.setMotorType(MOTOR_UNIT_A, SINGLE_DC);
  recore.setMotorType(MOTOR_UNIT_B, SINGLE_DC);

  //set all motor current limit
  //current range : 0 ~ 1500
  //setMotorCurrent(current);

  //example set 500mA
  recore.setMotorCurrent(500);

  //set motor brake mode
  //can change motor brake mode
  //setBrakeMode(motor number, brake type);
  //motor number : 0 ~ 3
  //brake type : COAST , BRAKE (default set brake)
}

void loop() {
  //set Motor speed
  //motor number : 0 ~ 3
  //motor power : -1.0 ~ 0 ~ 1.0
  //setMotorSpeed(motor number, motor power);
  //set Motor 0 speed forward 50%
  recore.setMotorSpeed(0, 0.5);
  delay(1000);

  //stop motor 0
  recore.setMotorSpeed(0, 0);
  delay(1000);

  //set Motor 0 speed reverse 50%
  recore.setMotorSpeed(0, -0.5);
  delay(1000);

  //stop motor 0
  recore.setMotorSpeed(0, 0);
  delay(1000);
}
