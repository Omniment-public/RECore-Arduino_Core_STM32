#include <RECoreLibrary.h>
RECoreLibrary recore;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //init motor
  recore.setMotorType(MOTOR_UNIT_A, SINGLE_DC);
  recore.setMotorType(MOTOR_UNIT_B, SINGLE_DC);
  recore.setMotorCurrent(500);

  //init IMU
  recore.setAccDataRate(ACC_RATE_104_HZ);
  recore.setAccScale(ACC_2G);
  recore.setAngularRateDataRate(A_RATE_104_HZ);
  recore.setAngularRateScale(A_RATE_250DPS);
}

void loop() {
  // put your main code here, to run repeatedly:

}
