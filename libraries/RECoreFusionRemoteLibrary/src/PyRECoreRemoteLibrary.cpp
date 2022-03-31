/* RECore-PyRECore --- A Python library for control of RECore

   Copyright (c) 2021 Omniment, Inc.

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE. */

#include "PyRECoreRemoteLibrary.h"
#include "Wire.h"

namespace PyRECore {

bool PyRECoreRemoteLibrary::read_eval() {
  PyRECore::Packet::Request *req;
  auto err = _protocol.read(&req);

  if (err != PyRECore::Packet::Error::OK) { // receives an invalid packet.
    _protocol.write(PyRECore::Packet::Header::NACK, &err, sizeof(err));
    return false;
  }

  switch (req->opcode) {
  case 0x0001: // pinMode
  {
    pinMode(*reinterpret_cast<const uint8_t *>(req->payload + 0),
            *reinterpret_cast<const uint8_t *>(req->payload + 1));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x0002: // digitalRead
  {
    uint8_t ret =
        digitalRead(*reinterpret_cast<const uint8_t *>(req->payload + 0));
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x0003: // digitalWrite
  {
    digitalWrite(*reinterpret_cast<const uint8_t *>(req->payload + 0),
                 *reinterpret_cast<const uint8_t *>(req->payload + 1));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x0004: // analogRead
  {
    uint16_t ret =
        analogRead(*reinterpret_cast<const uint8_t *>(req->payload + 0));
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x0005: // analogWrite
  {
    analogWrite(*reinterpret_cast<const uint8_t *>(req->payload + 0),
                *reinterpret_cast<const uint16_t *>(req->payload + 2));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x0006: // getBatteryVoltage
  {
    float ret = _recore.getBatteryVoltage();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x0007: // getMcuTemp
  {
    int8_t ret = _recore.getMcuTemp();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x0008: // wireBegin
  {
    Wire.begin(*reinterpret_cast<const uint8_t *>(req->payload + 0));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x0009: // wireRequestFrom
  {
    uint8_t ret =
        Wire.requestFrom(*reinterpret_cast<const uint8_t *>(req->payload + 0),
                         *reinterpret_cast<const uint8_t *>(req->payload + 1));
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x000a: // wireBeginTransmission
  {
    Wire.beginTransmission(
        *reinterpret_cast<const uint8_t *>(req->payload + 0));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x000b: // wireEndTransmission
  {
    uint8_t ret = Wire.endTransmission();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x000c: // wireWrite
  {
    Wire.write(*reinterpret_cast<const uint8_t *>(req->payload + 0));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x000d: // wireAvailable
  {
    uint8_t ret = Wire.available();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x000e: // wireRead
  {
    uint8_t ret = Wire.read();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x000f: // setMotorType
  {
    _recore.setMotorType(*reinterpret_cast<const uint8_t *>(req->payload + 0),
                         *reinterpret_cast<const uint8_t *>(req->payload + 1),
                         *reinterpret_cast<const uint16_t *>(req->payload + 2));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x0010: // setMotorCurrent
  {
    _recore.setMotorCurrent(
        *reinterpret_cast<const uint16_t *>(req->payload + 0));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x0011: // setBrakeMode
  {
    _recore.setBrakeMode(*reinterpret_cast<const uint8_t *>(req->payload + 0),
                         *reinterpret_cast<const uint8_t *>(req->payload + 1));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x0012: // setMotorSpeed
  {
    _recore.setMotorSpeed(*reinterpret_cast<const uint8_t *>(req->payload + 0),
                          *reinterpret_cast<const float *>(req->payload + 4));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x0013: // setDrivePwm
  {
    _recore.setDrivePwm(*reinterpret_cast<const uint8_t *>(req->payload + 0),
                        *reinterpret_cast<const int16_t *>(req->payload + 2));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x0014: // setSteppingSpeed
  {
    _recore.setSteppingSpeed(
        *reinterpret_cast<const uint8_t *>(req->payload + 0),
        *reinterpret_cast<const uint16_t *>(req->payload + 2),
        *reinterpret_cast<const uint8_t *>(req->payload + 4));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x0015: // setSteppingSteps
  {
    _recore.setSteppingSteps(
        *reinterpret_cast<const uint8_t *>(req->payload + 0),
        *reinterpret_cast<const uint16_t *>(req->payload + 2),
        *reinterpret_cast<const int32_t *>(req->payload + 4));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x0016: // getMotorFault
  {
    uint8_t ret = _recore.getMotorFault();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x0017: // getRawAccX
  {
    uint16_t ret = _recore.getRawAccX();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x0018: // getRawAccY
  {
    uint16_t ret = _recore.getRawAccY();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x0019: // getRawAccZ
  {
    uint16_t ret = _recore.getRawAccZ();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x001a: // getAccX
  {
    float ret = _recore.getAccX();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x001b: // getAccY
  {
    float ret = _recore.getAccY();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x001c: // getAccZ
  {
    float ret = _recore.getAccZ();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x001d: // getRawAngularRateX
  {
    uint16_t ret = _recore.getRawAngularRateX();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x001e: // getRawAngularRateY
  {
    uint16_t ret = _recore.getRawAngularRateY();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x001f: // getRawAngularRateZ
  {
    uint16_t ret = _recore.getRawAngularRateZ();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x0020: // getAngularRateX
  {
    float ret = _recore.getAngularRateX();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x0021: // getAngularRateY
  {
    float ret = _recore.getAngularRateY();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x0022: // getAngularRateZ
  {
    float ret = _recore.getAngularRateZ();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x0023: // getAccScale
  {
    uint8_t ret = _recore.getAccScale();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x0024: // getAccScaleConstant
  {
    float ret = _recore.getAccScaleConstant();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x0025: // getAngularRateScale
  {
    uint16_t ret = _recore.getAngularRateScale();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x0026: // getAngularRateScaleConstant
  {
    float ret = _recore.getAngularRateScaleConstant();
    _protocol.write(PyRECore::Packet::Header::ACK, &ret, sizeof(ret));
    return true;
  }
  case 0x0027: // setAccDataRate
  {
    _recore.setAccDataRate(
        *reinterpret_cast<const uint8_t *>(req->payload + 0));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x0028: // setAccScale
  {
    _recore.setAccScale(*reinterpret_cast<const uint8_t *>(req->payload + 0));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x0029: // setAccLpfBandwith
  {
    _recore.setAccLpfBandwith(
        *reinterpret_cast<const uint8_t *>(req->payload + 0));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x002a: // setAngularRateDataRate
  {
    _recore.setAngularRateDataRate(
        *reinterpret_cast<const uint8_t *>(req->payload + 0));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x002b: // setAngularRateScale
  {
    _recore.setAngularRateScale(
        *reinterpret_cast<const uint8_t *>(req->payload + 0));
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }
  case 0x002c: // interrupt
  {
    interrupt();
    _protocol.write(PyRECore::Packet::Header::ACK, nullptr, 0);
    return true;
  }

  default:
    err = PyRECore::Packet::Error::INVALID_OPCODE;
    _protocol.write(PyRECore::Packet::Header::NACK, &err, sizeof(err));
    return false;
  }
}

void PyRECoreRemoteLibrary::interrupt() {
  // Write zeros to GPIO
  for (int pin = 2; pin <= 13; ++pin) {
    digitalWrite(pin, 0);
  }

  // Stop motors
  _recore.setMotorCurrent(0);
  _recore.setMotorSpeed(0, 0);
  _recore.setMotorSpeed(1, 0);
  _recore.setMotorSpeed(2, 0);
  _recore.setMotorSpeed(3, 0);
}
} // namespace PyRECore