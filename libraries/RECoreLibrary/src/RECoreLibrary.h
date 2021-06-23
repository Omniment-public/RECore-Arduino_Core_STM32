
/*
    RECoreLibrary.h - RECore onboard Function library
    Copyright (c) 2021 Omniment Inc. All right reserved.
    
    MIT License
    
*/

#ifndef RECoreLibrary_h
#define RECoreLibrary_h

#include <RECoreAuxFuncLibrary.h>
#include <RECoreMotorDriverLibrary.h>
#include <RECoreLSM6Library.h>

#define SINGLE_DC   0
#define PARALLEL_DC 1
#define STEPPING    2

#define MOTOR_UNIT_A 0
#define MOTOR_UNIT_B 1

#define COAST 0
#define BRAKE 1

#define ACC_2G 0x00
#define ACC_4G 0x02
#define ACC_8G 0x03
#define ACC_16G 0x01

#define A_RATE_250DPS 0x00
#define A_RATE_500DPS 0x01
#define A_RATE_1000DPS 0x02
#define A_RATE_2000DPS 0x03
#define A_RATE_125DPS 0x04

#define ACC_RATE_DOWN 0x00
#define ACC_RATE_12_5_HZ 0x01
#define ACC_RATE_26_HZ 0x02
#define ACC_RATE_52_HZ 0x03
#define ACC_RATE_104_HZ 0x04
#define ACC_RATE_208_HZ 0x05
#define ACC_RATE_416_HZ 0x06
#define ACC_RATE_833_HZ 0x07
#define ACC_RATE_1660_HZ 0x08
#define ACC_RATE_3330_HZ 0x09
#define ACC_RATE_6660_HZ 0x0A

#define A_RATE_DOWN 0x00
#define A_RATE_12_5_HZ 0x01
#define A_RATE_26_HZ 0x02
#define A_RATE_52_HZ 0x03
#define A_RATE_104_HZ 0x04
#define A_RATE_208_HZ 0x05
#define A_RATE_416_HZ 0x06
#define A_RATE_833_HZ 0x07
#define A_RATE_1660_HZ 0x08

class RECoreLibrary : public RECoreAuxFuncLibrary , public RECoreMotorDriverLibrary , public RECoreLSM6Library{
    public:
        RECoreLibrary() : RECoreAuxFuncLibrary() , RECoreMotorDriverLibrary() , RECoreLSM6Library(){
            
        }

    private:

};

#endif
