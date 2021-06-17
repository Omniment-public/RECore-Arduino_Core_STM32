
/*
    RECoreAuxFuncLibrary.h - RECore onboard Function library
    Copyright (c) 2021 Omniment Inc. All right reserved.
    
    MIT License
    
*/

#ifndef RECoreAuxFuncLibrary_h
#define RECoreAuxFuncLibrary_h

class RECoreAuxFuncLibrary{
    public:
        RECoreAuxFuncLibrary(){
            //init vbat pin
            pinMode(A8,INPUT);

            //init onboard sw
            pinMode(12,INPUT_PULLUP);

            //init onboard led
            pinMode(13,OUTPUT);
        }

        float getBatteryVoltage();
        int getMcuTemp();

    private:

};

#endif
