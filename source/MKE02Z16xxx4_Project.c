/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MKE02Z16xxx4_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include <string.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKE02Z4.h"
#include "cmsis_gcc.h"
#include "fsl_adc.h"


void ConvertToString(uint8_t* string, uint16_t num)
{
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t temp[6] = {0};
	while(num != 0)
	{
		temp[i++] = num % 10 + '0';
		num = num / 10;
	}
	while(i != 0)
	{
		*(string + j++) = temp[--i];
	}
}


/* I2C release bus*/
void i2c_release_bus_delay(void)
{
    uint32_t i = 0;
    for (i; i < 10000; i++)
    {
    	__ASM volatile ("nop");
    }
}
/* API sleep I2C*/
void user_i2c_sleep(uint32_t ms)
{
	uint32_t j = 0;
	for (j; j < ms; j++)
	{
		i2c_release_bus_delay();
	}
}


/*	Configure to read from ADC input channel x
 *
 *
 * */
uint16_t ADC_channelSelectAndRead(uint8_t x){
	adc_channel_config_t adcChannelConfigStruct;
	adcChannelConfigStruct.channelNumber                        = ADC_SC1_ADCH(x);
	adcChannelConfigStruct.enableInterruptOnConversionCompleted = false;
	adcChannelConfigStruct.enableContinuousConversion           = false;

	ADC_EnableAnalogInput(ADC, ADC_SC1_ADCH(x), true);
	ADC_SetChannelConfig(ADC, &adcChannelConfigStruct);
	while (!ADC_GetChannelStatusFlags(ADC));
	return ADC_GetChannelConversionValue(ADC);
}


/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    uint8_t str[30];

    adc_config_t adcConfigStruct;

    adcConfigStruct.referenceVoltageSource = kADC_ReferenceVoltageSourceAlt0;
    adcConfigStruct.enableLowPower = false;
    adcConfigStruct.enableLongSampleTime = false;
    adcConfigStruct.clockDivider = kADC_ClockDivider1;
    adcConfigStruct.ResolutionMode = kADC_Resolution12BitMode;
    adcConfigStruct.clockSource = kADC_ClockSourceAlt0;

	ADC_Init(ADC, &adcConfigStruct);

	ADC_EnableHardwareTrigger(ADC, false);
	/* 2-No2, 3-No2_ref
	 * 6-So2,7-So2_ref
	 * 8-CO,9-CO_ref
	 * 10-O3,11-O3_ref
	 */
	ConvertToString(str, ADC_channelSelectAndRead(2));
	UART_WriteBlocking(UART1, str, sizeof(str));
	/*

	 * */
	while(1){



	}
    return 0 ;
}


