#include <platform.h>
#include <gpio.h>
#include "delay.h"
#include "leds.h"
#include "cycle_ccnt.h"

#define expType 1 //(1)Normal (0)Reverse 


// Public volatile variable
volatile int flag = 1;


// Interrupt Handler
void button_press_isr(int sources) {
	
	if ((sources << GET_PIN_INDEX(P_SW)) & (1 << GET_PIN_INDEX(P_SW))) 
	{
		flag = 0;
	}	
}


// Main Function
int main(void) {
	
	int i, experimentNumber = 0, delayTime, cycles;  // Number of Cycles
	double sum = 0;
	double ResultsArray [5] = {0, 0, 0, 0, 0};
	volatile double time_ms, avgTime;
 
	// Initialization
	leds_init();
		
	// Set Switch
	gpio_set_mode(P_SW, PullUp);
	gpio_set_trigger(P_SW, Rising);

	// Set Interrupt Handler
  	gpio_set_callback(P_SW, button_press_isr);

	__enable_irq();
	
	while (1) {
		
		flag = 1;
		
		// Turning led off/on
		leds_set(!expType);

		// Delay
		delayTime = ((rand() % 6) + 3) * 1000; // Random number between 3 - 8 *10^3
		delay_ms(delayTime);

		// Turning led on/off
		leds_set(expType);
		
		// Enable Cycle Counter
		KIN1_InitCycleCounter(); // Enable DWT hardware 
		KIN1_ResetCycleCounter(); // Reset cycle counter 
		KIN1_EnableCycleCounter(); // Start counting 
		 
		while(flag); // Waiting for Interrupt
		
		// Read cycle counter
		cycles = KIN1_GetCycleCounter(); // Get cycle counter 
		KIN1_DisableCycleCounter(); // Disable counting if not used any m 
		
		// Calculatin Time
		time_ms = (double) 1000* cycles / SystemCoreClock;
		
		// Calculate Average every 5 experiments.
		ResultsArray[experimentNumber] = time_ms;
		experimentNumber = (experimentNumber + 1) % 5;
		
		if (experimentNumber == 0) 
		{
			sum = 0;

			for (i = 0; i < 5; i++) 
			{
				sum = sum + ResultsArray[i];
			}

			avgTime = sum / 5;	
		}
		
	}
	
}

