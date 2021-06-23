
/*
    RECoreLSM6Library.cpp - RECore onboard LSM6 Library
    Copyright (c) 2021 Omniment Inc. All right reserved.

    MIT License

*/

#if defined(ARDUINO_ARCH_STM32)

#include <Arduino.h>
#include "RECoreLSM6Library.h"

RECoreLSM6Library::RECoreLSM6Library(){
    init();
}

void RECoreLSM6Library::init() {
    SPI_2 = new SPIClass(27, 28, 29);
    SPI_2 -> beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE3));
    SPI_2 -> begin();
    set_acc_scale = 0;
    set_arate_scale = 0;
    pinMode(nss_pin,OUTPUT);
    digitalWrite(nss_pin,1);
}

int16_t RECoreLSM6Library::getRawAccX(){
  return get_multibyte_data(0x28);
}

int16_t RECoreLSM6Library::getRawAccY(){
  return get_multibyte_data(0x2a);
}

int16_t RECoreLSM6Library::getRawAccZ(){
  return get_multibyte_data(0x2c);
}

float RECoreLSM6Library::getAccX(){
  return getAccScaleConstant() * getRawAccX();
}

float RECoreLSM6Library::getAccY(){
  return getAccScaleConstant() * getRawAccY();
}

float RECoreLSM6Library::getAccZ(){
  return getAccScaleConstant() * getRawAccZ();
}

int16_t RECoreLSM6Library::getRawAngularRateX(){
  return get_multibyte_data(0x22);
}

int16_t RECoreLSM6Library::getRawAngularRateY(){
  return get_multibyte_data(0x24);
}

int16_t RECoreLSM6Library::getRawAngularRateZ(){
  return get_multibyte_data(0x26);
}

float RECoreLSM6Library::getAngularRateX(){
  return getAngularRateScaleConstant() * getRawAngularRateX();
}

float RECoreLSM6Library::getAngularRateY(){
  return getAngularRateScaleConstant() * getRawAngularRateY();
}

float RECoreLSM6Library::getAngularRateZ(){
  return getAngularRateScaleConstant() * getRawAngularRateZ();
}

uint8_t RECoreLSM6Library::getAccScale(){
  uint8_t scale_arr[4] = {2,16,4,8};
  return scale_arr[set_acc_scale];
}

float RECoreLSM6Library::getAccScaleConstant(){
  float scale_arr[4] = {
    0.00006103701,
    0.00048829615,
    0.00012207403,
    0.00024414807
    };

  return scale_arr[set_acc_scale];
}

uint16_t RECoreLSM6Library::getAngularRateScale(){
  uint16_t scale_arr[5] = {250,500,1000,2000,125};
  return scale_arr[set_acc_scale];
}

float RECoreLSM6Library::getAngularRateScaleConstant(){
  float scale_arr[5] = {
    0.00762962736,
    0.01525925473,
    0.03051850947,
    0.06103701895,
    0.00381481368
    };

    return scale_arr[set_arate_scale];
}

int16_t RECoreLSM6Library::get_multibyte_data(uint8_t head_addr){
  uint8_t rec_data[2];
  digitalWrite(nss_pin,0);
  send_spi_data(head_addr,false);
  receive_spi_data(rec_data,2);
  int16_t return_data = (rec_data[1] << 8) | rec_data[0];
  digitalWrite(nss_pin,1);
  return return_data;
}

uint8_t RECoreLSM6Library::get_singlebyte_data(uint8_t head_addr){
  uint8_t rec_data;
  digitalWrite(nss_pin,0);
  send_spi_data(head_addr,false);
  receive_spi_data(&rec_data,2);
  digitalWrite(nss_pin,1);
  return rec_data;
}

void RECoreLSM6Library::write_singlebyte_data(uint8_t head_addr, uint8_t set_data){
  digitalWrite(nss_pin,0);
  send_spi_data(head_addr, true);
  send_spi_data(set_data,true);
  digitalWrite(nss_pin,1); 
}

void RECoreLSM6Library::setAccDataRate(uint8_t set_data){
  if(set_data > 0x0f){
    return;
  }

  set_acc_rate = set_data;
  uint8_t addr = 0x10;
  uint8_t make_data = get_singlebyte_data(addr);
  make_data = (make_data & 0x0f) | (set_data << 4);
  write_singlebyte_data(addr, make_data);
}

void RECoreLSM6Library::setAccScale(uint8_t set_data){
  if(set_data > 0x03){
    return;
  }

  set_acc_scale = set_data;
  uint8_t addr = 0x10;
  uint8_t make_data = get_singlebyte_data(addr);
  make_data = (make_data & 0xf3) | (set_data << 2);
  write_singlebyte_data(addr, make_data);
}

void RECoreLSM6Library::setAccLpfBandwith(uint8_t set_data){
  if(set_data > 0x01){
    return;
  }

  set_acc_plf_bw = set_data;
  uint8_t addr = 0x10;
  uint8_t make_data = get_singlebyte_data(addr);
  make_data = (make_data & 0xfd) | (set_data << 1);
  write_singlebyte_data(addr, make_data);
}

void RECoreLSM6Library::setAngularRateDataRate(uint8_t set_data){
  if(set_data > 0x0f){
    return;
  }

  set_arate_rate = set_data;
  uint8_t addr = 0x11;
  uint8_t make_data = get_singlebyte_data(addr);
  make_data = (make_data & 0x0f) | (set_data << 4);
  write_singlebyte_data(addr, make_data);
}

void RECoreLSM6Library::setAngularRateScale(uint8_t set_data){
  if(set_data > 0x07){
    return;
  }
  
  set_arate_scale = set_data;
  uint8_t addr = 0x11;
  uint8_t make_data = get_singlebyte_data(addr);

  if(set_data == 4){
    //125dps mode
    make_data = (make_data & 0xfd) | 2;
  }else{ 
    make_data = (make_data & 0xf3) | ((set_data & 3) << 2);
  }

  write_singlebyte_data(addr, make_data);
}

void RECoreLSM6Library::send_spi_data(uint8_t send_data, bool rw) {
  //rw : write -> true
  if (!rw) {
    send_data = send_data | 0x80;
  }
  SPI_2 -> transfer(send_data);
}

void RECoreLSM6Library::receive_spi_data(uint8_t* receive_data, uint8_t len) {
  for (int i = 0; i < len; i++) {
    receive_data[i] = SPI_2 -> transfer(0x00);
  }
}

#endif // ARDUINO_ARCH_STM32
