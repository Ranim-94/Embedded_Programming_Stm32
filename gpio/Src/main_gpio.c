


#include "stm32f407G.h"
#include "gpio_driver.h"

#define CYCLE 5e5

void delay(){

	for(int i=0; i<CYCLE; i++){

	}

} /* End delay*()*/

int main(void){

// Goal: toggling a LED in push pull mode as output

// Instantiate some structure
GPIO_Handle_t gpio_handle;

// Initialize members for GPIO Port D registers
gpio_handle.gpio_reg_x = GPIOD; // Use GPIOD 

gpio_handle.gpio_pin_conf.GPIO_PinNumber = GPIO_PIN_12;

gpio_handle.gpio_pin_conf.GPIO_PinMode = OUT; // Set as output  
gpio_handle.gpio_pin_conf.GPIO_PinSpeed = LOW; // Set low speed
gpio_handle.gpio_pin_conf.GPIO_PinOPType = PUSH_PULL; // Push-pull

// since push pull is used, no need for pull-up resistor
// see report for more info
gpio_handle.gpio_pin_conf.GPIO_PinPuPdControl = NO_PULLUP; // No pull-up

// TODO: I will keep this field now uninitialized
// gpio_handle.gpio_pin_conf.GPIO_PinAltFunMode = 0; // No alternate function

// Turning the clock on GPIO Port D
GPIO_PeriClockControl(GPIOD, ON);

GPIO_Init(&gpio_handle); // Set up GPIO Registers

	while(1){

		GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_12);

		delay(); // wait for certain time


	} /* End while()*/


// Resetting GPIO Port D
//GPIO_DeInit(GPIOD);



}/* End main()*/

/*

 Some notes measurement regarding delays,
 captured by logic analyzer and sigrok software

 Download pulseview for linux in https://sigrok.org/wiki/Downloads


	for 5e5 -> delay = 433 ms
	


*/
