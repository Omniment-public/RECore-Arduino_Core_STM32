/*
 *******************************************************************************
 * Copyright (c) 2020-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#if defined(ARDUINO_RECore_G431CBU)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
    //VCP
    PA_10, //D0 - VCP RX
    PA_9,  //D1 - VCP TX

    //IO PIN Head
    PA_8, //D2    - GPIO0
    PC_4, //D3    - A0 - GPIO1
    PB_2, //D4    - A1 - GPIO2
    PA_7, //D5    - A2 - GPIO3
    PA_6, //D6    - A3 - GPIO4
    PA_5, //D7    - A4 - GPIO5

    PA_3, //D8    - A5 - GPIO6
    PA_1, //D9    - A6 - GPIO7
    PA_2, //D10   - A7 - GPIO8

    PA_11, //D11   - CAN RX,I2C SCL,Servo3
    PA_12, //D12   - CAN TX,I2C SDA,Servo4

    //Builtin IF
    PB_6, //D13   - LED
    PB_1, //D14 - SW

    //Motor Driver
    PA_15, //D14   - U1 AIN 1
    PB_3,  //D15   - U1 AIN 2
    PB_10, //D16   - U1 BIN 1
    PB_11, //D17   - U1 BIN 2
    PC_6,  //D18   - U2 AIN 1
    PB_5,  //D19   - U2 AIN 2
    PB_0,  //D20   - U2 BIN 1
    PB_7,  //D21   - U2 BIN 2
    PC_13, //D22   - MSLEEP
    PB_4,  //D23   - MFAULT
    PA_4,  //D24   - DAC

    //IMU ISP
    PB_12, //D25 - SPI NSS
    PB_15, //D26 - SPI MOSI
    PB_14, //D27 - SPI MISO
    PB_13, //D28 - SPI SCK

    //Battery Voltage ADC
    PA_0 //D29 - A8 - VBATIN

    //no work
    //PC_11,  //D30
    //PB_9    //D31
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
    3,  // A0,  PC4
    4,  // A1,  PB2
    5,  // A2,  PA7
    6,  // A3,  PA6
    7,  // A4,  PA5
    8,  // A5,  PA3
    9,  // A6,  PA1
    10, // A7,  PA2
    29, // A8,  PA0
};

// ----------------------------------------------------------------------------

//pin name define
#define SW_Pin GPIO_PIN_1
#define SW_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_6
#define LED_GPIO_Port GPIOB

#ifdef __cplusplus
extern "C"
{
#endif

  /**
  * @brief  System Clock Configuration
  */
  WEAK void SystemClock_Config(void)
  {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Configure the main internal regulator output voltage
  */
    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
    /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
    RCC_OscInitStruct.PLL.PLLN = 42;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
  */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    {
      Error_Handler();
    }
    /** Initializes the peripherals clocks
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_ADC12 | RCC_PERIPHCLK_FDCAN;
    PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
    PeriphClkInit.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
    PeriphClkInit.Adc12ClockSelection = RCC_ADC12CLKSOURCE_SYSCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }
  }

  WEAK void initVariant(void)
  {
    //set pin input sw
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = SW_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SW_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SW_GPIO_Port, &GPIO_InitStruct);

    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
  }

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_GENERIC_* */
