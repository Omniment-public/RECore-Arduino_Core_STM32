
/*
    RECoreLSM6Library.h - RECore onboard LSM6 Function library
    Copyright (c) 2021 Omniment Inc. All right reserved.
    
    MIT License
    
*/

#ifndef RECoreLSM6Library_h
#define RECoreLSM6Library_h

#include <SPI.h>

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

class RECoreLSM6Library{
    public:
        
        RECoreLSM6Library();
        
        int16_t getRawAccX();
        int16_t getRawAccY();
        int16_t getRawAccZ();

        float getAccX();
        float getAccY();
        float getAccZ();

        int16_t getRawAngularRateX();
        int16_t getRawAngularRateY();
        int16_t getRawAngularRateZ();

        float getAngularRateX();
        float getAngularRateY();
        float getAngularRateZ();

        float getTemp();
        
        uint8_t getAccScale();
        float getAccScaleConstant();
        uint16_t getAngularRateScale();
        float getAngularRateScaleConstant();

        int16_t get_multibyte_data(uint8_t head_addr);
        uint8_t get_singlebyte_data(uint8_t head_addr);
        void write_singlebyte_data(uint8_t head_addr, uint8_t set_data);

        void setAccDataRate(uint8_t set_data);
        void setAccScale(uint8_t set_data);
        void setAccLpfBandwith(uint8_t set_data);

        void setAngularRateDataRate(uint8_t set_data);
        void setAngularRateScale(uint8_t set_data);

    private:
        SPIClass* SPI_2;

        void init();
        
        void send_spi_data(uint8_t send_data, bool wr);
        void receive_spi_data(uint8_t* receive_data, uint8_t len);

        uint8_t set_acc_rate;
        uint8_t set_acc_scale;
        uint8_t set_acc_plf_bw;
        uint8_t set_arate_rate;
        uint8_t set_arate_scale;

};

#endif
