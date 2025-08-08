

/*
 * Goal of this project: turning LED on using bare metal style
 *
 * */


#define AHB1_ADD  0x40020000

#define GPIOA_ADD 0x40020000 // base address for GPIOA
// AHB1 and GPIOA have same addresses

/*
 *  starting from this base address and using suitable offset
 *  we can access the suitable registers
 *
 *  In case of turning the LED on, we need to
 *  	1- set GPIOA as output (the mode ) <-> GPIOx_MODER
 *  	2- write data to GPIOA since we are using it as output
 *  		<-> GPIOx_ODR
 *
 * */

#define GPIOx_MODER (*(volatile unsigned int*)(GPIOA_ADD + 0x00))
#define GPIOx_ODR	(*(volatile unsigned int*)(GPIOA_ADD + 0x14))

// ================ Clock registers =================

#define RCC_ADD   0x40023800

#define RCC_AHB1ENR (*(volatile unsigned int*)(RCC_ADD + 0x30UL))
// RCC_AHB1ENR is used to set the clock of GPIOA


int main(){


	// set the clock for GPIOA
	RCC_AHB1ENR |= (1U<<0);

	// set PA5

	/*
	 *  we know the that the user LED is connected to PA5 from
	 *  the user manual doc (section 7.4 page 24)
	 *
	 *  From ref manual also: eack I/O has 16 pins, configured by
	 *  32 bit registers <-> we need 2 bit to control each I/O pin
	 *
	 *  for PA5 and GPIOx_MODER: we need to go to MODER field 5
	 *
	 * */

	GPIOx_MODER |= (1U<<10); // set bit 10 to 1
	GPIOx_MODER &= ~(1U<<11); // set bit 11 to 0
	// after this step. PA5 is now an output

	/*
	 * the | operator ensure that only bit 0 or bit x
	 * is set to 1, and we leave other bits as they initially are
	 *
	 * */

	while(1){

	// writing+ data is through GPIOx_ODR
		GPIOx_ODR |= (1U<<5); // setting pin 5

	} /*End while() */


} /* End main ()*/
