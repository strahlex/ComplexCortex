 /**
 * @file pincon.h
 * @author Alexander Rössler
 * @brief PINCON Library
 * @date 08-12-2012
 */
/** @defgroup PINCON PINCON (Pin Configuration)
 * @ingroup Peripheral
 * @{
 */
#pragma once

#include <pinconDriver.h>
#include <types.h>

typedef enum { 
    Pin_Function_Primary = 0u,
    Pin_Function_FirstAlternate = 1u,
    Pin_Function_SecondAlternate = 2u,
    Pin_Function_ThirdAlternate = 3u
} Pin_Function;

typedef enum { 
    Pin_Mode_PullUp = 0u,
    Pin_Mode_Repeater = 1u,
    Pin_Mode_NoPullUpDown = 2u,
    Pin_Mode_PullDown = 3u
} Pin_Mode;

typedef enum { 
    Pin_OpenDrain_Disable = 0u,
    Pin_OpenDrain_Enable = 1u
} Pin_OpenDrain;

/** Set the function of the selected pin, lookup the functions in the manual (PINSEL)
 *  @param port Port of the pin.
 *  @param pin Pin number.
 *  @param function Function to be selected.
 */
void Pin_setFunction(uint8 port, uint8 pin, Pin_Function function);
/** Set the mode of the selected pin, lookup the modes in the manual (PINMODE)
 *  @param port Port of the pin.
 *  @param pin Pin number.
 *  @param mode Mode that should be set on the pin.
 */
void Pin_setMode(uint8 port, uint8 pin, Pin_Mode mode);
/** Set open drain mode of the selected pin, lookup the open drain modes in the manul (PINMODE_OD)
 *  @param port Port of the pin.
 *  @param pin Pin number.
 *  @param mode Open drain mode that should be set on the pin (enabled or not).
 */
void Pin_setOpenDrainMode(uint8 port, uint8 pin, Pin_OpenDrain mode);

/**
 * @}
 */
