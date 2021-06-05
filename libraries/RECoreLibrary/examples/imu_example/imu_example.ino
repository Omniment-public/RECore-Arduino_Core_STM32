/*
   RECore Library
   LSM6 IMU example
*/

#include <RECoreLibrary.h>

RECoreLibrary recore;

void setup() {
  //init serial
  Serial.begin(115200);

  //set Acceleromater Output Data Rate
  //ACC_RATE_DOWN 0x00
  //ACC_RATE_12_5_HZ 0x01
  //ACC_RATE_26_HZ 0x02
  //ACC_RATE_52_HZ 0x03
  //ACC_RATE_104_HZ 0x04
  //ACC_RATE_208_HZ 0x05
  //ACC_RATE_416_HZ 0x06
  //ACC_RATE_833_HZ 0x07
  //ACC_RATE_1660_HZ 0x08
  //ACC_RATE_3330_HZ 0x09
  //ACC_RATE_6660_HZ 0x0A
  recore.setAccDataRate(ACC_RATE_104_HZ);

  //set Acceleromater Output Data Scale
  //ACC_2G 0x00
  //ACC_4G 0x02
  //ACC_8G 0x03
  //ACC_16G 0x01
  recore.setAccScale(ACC_2G);

  //set Gyroscope Output Data Rate
  //A_RATE_DOWN 0x00
  //A_RATE_12_5_HZ 0x01
  //A_RATE_26_HZ 0x02
  //A_RATE_52_HZ 0x03
  //A_RATE_104_HZ 0x04
  //A_RATE_208_HZ 0x05
  //A_RATE_416_HZ 0x06
  //A_RATE_833_HZ 0x07
  //A_RATE_1660_HZ 0x08
  recore.setAngularRateDataRate(A_RATE_104_HZ);

  //set Gyroscope Output Data Scale
  //A_RATE_250DPS 0x00
  //A_RATE_500DPS 0x01
  //A_RATE_1000DPS 0x02
  //A_RATE_2000DPS 0x03
  //A_RATE_125DPS 0x04
  recore.setAngularRateScale(A_RATE_250DPS);
}

void loop() {
  //get IMU data
  //get Acceleromater Raw data
  //int16_t getRawAccX()
  //int16_t getRawAccY()
  //int16_t getRawAccZ()

  //Get Acceleromater unit-converted data(g)
  //float getAccX()
  //float getAccY()
  //float getAccZ()

  //get Gyroscope Raw data
  //int16_t getRawAngularRateX()
  //int16_t getRawAngularRateY()
  //int16_t getRawAngularRateZ()

  //get Gyroscope unit-converted data(dps)
  //float getAngularRateX()
  //float getAngularRateY()
  //float getAngularRateZ()

  Serial.print(recore.getAccX());
  Serial.print(",");
  Serial.print(recore.getAccY());
  Serial.print(",");
  Serial.print(recore.getAccZ());
  Serial.print(",");
  Serial.print(recore.getAngularRateX());
  Serial.print(",");
  Serial.print(recore.getAngularRateY());
  Serial.print(",");
  Serial.println(recore.getAngularRateZ());

  delay(5);
}