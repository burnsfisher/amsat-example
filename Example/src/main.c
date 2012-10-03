
/*
 * AMSAT Fox Build Tools Example Program - Copyright (C) 2012 Radio Amateur Satellite Corp.
 *
 * This main program simply initializes the GPIOs which match LEDs 3 and 4 on the
 * STM32L1xx Discovery board, and the alternately flashes them.  The point of
 * this program is to serve as an example to go with a paper called "The Fox-1
 * Build Environment" in the AMSAT 2012 Space Symposium proceedings.
 *
 * Burns Fisher, W2BFJ, 9/30/2012
 *
 */

#include "gpio.h"
int main(void)
{


		// Initialize the LED setup.
		GPIOInitialize(DiscoveryLED3);
		GPIOInitialize(DiscoveryLED4);

		while(1)
		{
			int i=500000; // Change the number to change the toggle speed
			// We should obvious use a clock in a real application.
			while(--i) {}
			GPIOToggle(DiscoveryLED3);
			GPIOToggle(DiscoveryLED4);
		}
	return 0; // And he never returned, no he never returned...
}
