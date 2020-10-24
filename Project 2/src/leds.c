#include <platform.h>
#include <gpio.h>
#include "leds.h"

void leds_init(void) {
	// Set 1 led pin to outputs.
	gpio_set_mode(P_LED_R, Output);
	
	leds_set(0);
}

void leds_set(int red_on) {
	// Boolean operation to decide on state for both active
	// high and low LEDs.
	gpio_set(P_LED_R, !red_on != LED_ON);

}

// *******************************ARM University Program Copyright © ARM Ltd 2016*************************************   
