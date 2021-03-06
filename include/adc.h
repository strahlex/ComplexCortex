/**
 * @file adc.h
 * @author Alexander Rössler
 * @brief ADC Library
 * @date 14-11-2012
 */
/* Cortex M3 Libraries ----------------------------------------------------------- */
/** @defgroup ComplexCortex
 *  ComplexCortex Libaries
 */
/* Peripheral group ----------------------------------------------------------- */
/** @defgroup Peripheral
 *  @ingroup ComplexCortex
 *  Libraries to control the peripheral devices
 */
/* Device group ----------------------------------------------------------- */
/** @defgroup Device
 *  @ingroup ComplexCortex
 *  Libraries to control control various hardware devices
 */
/* Functional group ----------------------------------------------------------- */
/** @defgroup Functional
 *  @ingroup ComplexCortex
 *  Libraries that implement useful functions not using any specific hardware
 */
/** @defgroup ADC ADC (Analog to Digital Converter)
 *  @ingroup Peripheral
 *  Include adc.h to use the ADC library.
 * @{
 */
#pragma once

#include <types.h>
#include <adcDriver.h>

typedef enum {
    Adc_Pin_0 = 0u,
    Adc_Pin_1 = 1u,
    Adc_Pin_2 = 2u,
    Adc_Pin_3 = 3u,
    Adc_Pin_4 = 4u,
    Adc_Pin_5 = 5u,
    Adc_Pin_6 = 6u,
    Adc_Pin_7 = 7u
} Adc_Pin;

typedef enum {
    Adc_BurstMode_Enabled = 1u,
    Adc_BurstMode_Disabled = 0u
} Adc_BurstMode;

/** Initializes the ADC
 *  @param clk Clock the ADC should be refreshed with in Hz.
 *  @param burstMode If 1 the ADC runs in burst mode it is continuously refreshing its data.
 *  @return Return 0 if successful, -1 if not.
 */
int8 Adc_initialize(uint32 clk, Adc_BurstMode burstMode);
/** Enables an ADC pin 
 *  @param pin ADC pin to enable
 *  @return Return 0 if successful, -1 if not
 */
int8 Adc_enablePin(Adc_Pin pin);
/** Disables an ADC pin 
 *  @param pin ADC pin to disable
 *  @return Return 0 if successful, -1 if not
 */
int8 Adc_disablePin(Adc_Pin pin);
/** Deinitializes the ADC
 *  @return Returns 0 if successful, -1 if not.
 */
int8 Adc_deinitialize(void);
/** Reads the value from the adc
 *  @param value A pointer to the variable the value should be written to.
 *  @return Returns 0 if successful, -1 if not.
 */
int8 Adc_read(Adc_Pin pin, uint16* value);

/**
 * @}
 */
