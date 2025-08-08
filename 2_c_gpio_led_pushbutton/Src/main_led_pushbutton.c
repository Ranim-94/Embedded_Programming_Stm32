

#include "stm32f4xx.h"

/*
 * Goal of this project:
 *
 * 	toggle led on and off using bsrr register
 *
 * 	BSRR: see section 8.4.7 page 160 from ref manual
 *
 * */


int main(void){

	// set the clock for peripherals
	RCC->AHB1ENR |= (1U<<0); // for GPIOA
	RCC->AHB1ENR |= (1U<<2); // set the clock for GPIOC


		// set PA5

		/*
		 *  we know the that the user LED is connected to PA5 from
		 *  the user manual doc (section 7.4 page 24)
		 *
		 *  From ref manual also: each I/O has 16 pins, configured by
		 *  32 bit registers <-> we need 2 bit to control each I/O pin
		 *
		 *  for PA5 and GPIOx_MODER: we need to go to MODER field 5
		 *
		 * */

		GPIOA->MODER |= (1U<<10); // set bit 10 to 1
		GPIOA->MODER &= ~(1U<<11); // set bit 11 to 0
		// after this step. PA5 is now an output


		/*
		 * the | operator ensure that only bit 0 or bit x
		 * is set to 1, and we leave other bits as they initially are
		 *
		 * */

		// Now for PC13 (for the push button)
		// we need to reset MODER 13 (bit 26 and 27)
		GPIOC->MODER &= ~(1U<<26);
		GPIOC->MODER &= ~(1U<<27);

		while(1){

			if (GPIOC->IDR & (1U<<13)){

				GPIOA->BSRR |= (1U<<5); // setting pin 5

			} else{

				GPIOA->BSRR |= (1U<<21); // setting pin 5 off (reset)
			}




		} /*End while() */


} /* End main() */




