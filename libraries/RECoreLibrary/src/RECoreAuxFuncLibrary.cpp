
/*
    RECoreAuxFuncLibrary.cpp - RECore onboard Function library
    Copyright (c) 2021 Omniment Inc. All right reserved.
    
    MIT License
    
*/

#if defined(ARDUINO_ARCH_STM32)

#include <Arduino.h>

#include "RECoreAuxFuncLibrary.h"

float RECoreAuxFuncLibrary::getBatteryVoltage()
{
    //(((3.3 / 1023) * vbat_adc) + 0.35) * ((120.0 + 51.0) / 51.0)
    float vbat_adc = analogRead(A8);
    return ((0.00322581 * vbat_adc) + 0.1 + 0.35) * 3.156862745;
}

int RECoreAuxFuncLibrary::getMcuTemp()
{
    //V30 : 0.76
    //avg_slope : 2.5
    //10bit adc
    // (0.76-(adc * 3.3/1023))/2.5 + 30
    uint16_t adc_val = analogRead(ATEMP);
    float calc_temp = 30.304 - (0.00129032 * adc_val);
    return calc_temp;
}

#endif // ARDUINO_ARCH_STM32
