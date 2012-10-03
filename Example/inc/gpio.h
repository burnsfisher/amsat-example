/*
 * gpio.h
 *
 *  Created on: Sep 16, 2012
 *      Author: Burns Fisher
 *
 *  Goes with GPIO.C and is needed by those who call routines in that module.
 */
#ifndef GPIO_H_
#define GPIO_H_

#include "stm32l1xx_gpio.h" // This is the standard peripheral interface include


typedef enum gu {DiscoveryLED3, DiscoveryLED4} Gpio_Use;


void GPIOInitialize(Gpio_Use whichGpio);
void GPIOSetOn(Gpio_Use whichGpio);
void GPIOSetOff(Gpio_Use whichGpio);
void GPIOToggle(Gpio_Use whichGpio);

#endif /* GPIO_H_ */
