/*
 * gpio.c
 *
 *  Created on: Sep 16, 2012
 *      Author: Burns Fisher
 *
 *  This is a tiny scrap of code to use a general purpose I/O device for simple
 *  single-bit output.
 *
 *  This is a bit more general purpose than it has to be with only two GPIOs in use,
 *  but you can see how it might be good to keep track of many many single bit inputs
 *  and outputs.
 *
 */


#include "stm32l1xx_gpio.h"  // Standard peripheral library include
#include "gpio.h"			 // Include for this gpio code


/*-----------------------------------------------------------*/

#define NUM_GPIO 2
static GPIO_TypeDef  *GPIO_PORT[NUM_GPIO] = {GPIOB, GPIOB};
static const uint16_t GPIO_PIN[NUM_GPIO] = {GPIO_Pin_6,GPIO_Pin_7};
static const uint32_t GPIO_CLK[NUM_GPIO] = {RCC_AHBPeriph_GPIOB, RCC_AHBPeriph_GPIOB};
static const uint8_t  GPIO_MODE[NUM_GPIO] = {GPIO_Mode_OUT, GPIO_Mode_OUT};
static const uint8_t  GPIO_PUPD[NUM_GPIO] = {GPIO_PuPd_NOPULL, GPIO_PuPd_NOPULL};
static const uint8_t  GPIO_OTYPE[NUM_GPIO]= {GPIO_OType_PP,GPIO_OType_PP};
static const uint8_t  GPIO_INIT_STATE[NUM_GPIO] = {0,1};




void GPIOInitialize( Gpio_Use whichGpio )
{

	  GPIO_InitTypeDef  GPIO_InitStructure;

	  /* Enable the GPIO_LED Clock */
	  RCC_AHBPeriphClockCmd(GPIO_CLK[whichGpio], ENABLE);

	  /* Configure the GPIO_LED pin */
	  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[whichGpio];
	  GPIO_InitStructure.GPIO_Mode = GPIO_MODE[whichGpio];
	  GPIO_InitStructure.GPIO_OType = GPIO_OTYPE[whichGpio];
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD[whichGpio];
	  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(GPIO_PORT[whichGpio], &GPIO_InitStructure);
	  if (GPIO_MODE[whichGpio]==GPIO_Mode_OUT)
	  {
		  if (GPIO_INIT_STATE[whichGpio])GPIOSetOn(whichGpio);
		  else GPIOSetOff(whichGpio);
	  }

}

void GPIOSetOn(Gpio_Use whichGpio)
{
	GPIO_SetBits(GPIO_PORT[whichGpio], GPIO_PIN[whichGpio]);
}
void GPIOSetOff(Gpio_Use whichGpio)
{
	GPIO_ResetBits(GPIO_PORT[whichGpio], GPIO_PIN[whichGpio]);
}
void GPIOToggle(Gpio_Use whichGpio)
{
	uint16_t current;
	current=GPIO_ReadOutputData(GPIO_PORT[whichGpio]);
	if (current & GPIO_PIN[whichGpio]) GPIOSetOff(whichGpio);
	else GPIOSetOn(whichGpio);
}

