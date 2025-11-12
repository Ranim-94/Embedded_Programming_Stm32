

/*
 *
 * Exercise: toggle a LED whenever an interrupt is triggered
 *
 * by a button on falling edge
 *
 * */



#include "stm32f407G.h"
#include "gpio_driver.h"

#include <string.h>

#define CYCLE 25e4

void delay(){

	for(int i=0; i<CYCLE; i++){

	}

} /* End delay*()*/

int main(void){




// Instantiate structures for button and LED
GPIO_Handle_t gpio_button, gpio_led;
memset(&gpio_button,0,sizeof(gpio_button));
memset(&gpio_led,0,sizeof(gpio_led));

// Configure PA0 as input (USER BUTTON)
gpio_button.gpio_reg_x = GPIOA;
gpio_button.gpio_pin_conf.GPIO_PinNumber = GPIO_PIN_0;

// For interrupt, the mode is no longer input mode
gpio_button.gpio_pin_conf.GPIO_PinMode = INT_FALLING_EDGE;

gpio_button.gpio_pin_conf.GPIO_PinSpeed = LOW;

// External pull-down on Discovery board
gpio_button.gpio_pin_conf.GPIO_PinPuPdControl = NO_PULLUP;


// Configure PD12 as output (LED) - or use PD12 for Discovery board LED
gpio_led.gpio_reg_x = GPIOD; // Change to GPIOD for Discovery board

// PD12 is the green LED on Discovery
gpio_led.gpio_pin_conf.GPIO_PinNumber = GPIO_PIN_12;
gpio_led.gpio_pin_conf.GPIO_PinMode = OUT;
gpio_led.gpio_pin_conf.GPIO_PinSpeed = HIGH;
gpio_led.gpio_pin_conf.GPIO_PinOPType = PUSH_PULL;
gpio_led.gpio_pin_conf.GPIO_PinPuPdControl = NO_PULLUP;

// Enable clocks for both GPIO ports
GPIO_PeriClockControl(GPIOA, ON); // For button
GPIO_PeriClockControl(GPIOD, ON); // For LED

// Initialize both GPIO configurations
GPIO_Init(&gpio_button);
GPIO_Init(&gpio_led);


// Now configure the Interrupt part

// TODO: setting up the priority i will let it for now

// Step 1: configure the interrupt at the processor side <-> setting up NVIC registers
 GPIO_IRQ_InterruptConfig(IRQ_EXTI_0,ON);
 /*
  * Recall that PA0 interrupt is handled by EXTI_0
  * that's why we use IRQ_EXTI_0
  *
  * */


 	 while(1);


}/* End main()*/


void EXTI0_IRQHandler(void){

	delay(); // for debouncing effect of the push button

	// Clear the pending event from EXTI line
	GPIO_IRQ_Handle(GPIO_PIN_0);

	// toggle user LED PD12
	GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_12);


} /* End EXTI0_IRQHandler() */



