

/*
 * Goal of this project: turning LED on using bare metal style

 * However, here we adopt structure style
 * that is each peripheral (like GPIO_A) is defined as some
 * structure data type, with members defined as associated registers
 * for this peripheral , like the MODER and ODR registers
 *
 * Prerequisite for this project: review 1_b_LED_ON_f411
 *
 *
 * Gain using the structure method:
 * 	- We know only need the base address of the main peripheral
 * 	  GPIOA and RCC, and the sub registers for each
 * 	  peripheral, we can access them using proper definition
 * 	  of our structure data type as shown below
 * 	  <-> don't need anymore to compute manually the
 * 	  address of each register we want
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



// ================ Clock registers =================

#define RCC_ADD   0x40023800


// this type of practice is coming from MISRA C coding standard
// to explore this later

#include <stdio.h>
#include <stdint.h>



/*
 * Some explanation of how we construct our custom structure:
 *
 * a structure can be for example:
 * typedef struct{

	__IO uint32_t MODER;
	__IO uint32_t OTYPER;
	__IO uint32_t OSPEEDR;
	__IO uint32_t PURDR;
	__IO uint32_t IDR;
	__IO uint32_t ODR;
	__IO uint32_t BSRR;
	__IO uint32_t LCKR;
	__IO uint32_t AFR[2];

}GPIO_A_t;
 *
 *
 * 	- However, in our LED application, we need to access only 2 registers:
 * 		MODER and ODR
 *
 * 	- now for struct data type, where the members are of type
 * 	32 bit (4 byte), we need to conserve the address and the order
 * 	between MODER and ODR
 * 		- between MODER and ODR we have 4 registers
 * 		(OTYPER,OSPEEDR,PURDR,IDR), each having 4 byte length
 *
 * 	- this means we can for example create some array occupying this
 * 	length,
 * 	- and registers after ODR we can simply eliminate them
 * */

typedef struct{

	volatile uint32_t MODER;
	volatile uint32_t DUMY[4];
	volatile uint32_t ODR;

}GPIO_A_t;

/*
 * Same concept for RCC peripheral, where the 1st 12 register
 * are eliminated and replaced by some dummy variable with correspondent
 * size
 * Only the AHB1ENR register is needed so we can configure the clock
 *
 * */

typedef struct{

	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR;
	// RCC_AHB1ENR is used to set the clock of GPIOA

} RCC_t;

// Same concept for RCC register, responsible for the clock

#define GPIO_A ((GPIO_A_t*)GPIOA_ADD)
#define RCC ((RCC_t*)RCC_ADD)

int main(){


	// set the clock for GPIOA
	RCC->AHB1ENR |= (1U<<0);

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

	GPIO_A->MODER |= (1U<<10); // set bit 10 to 1
	GPIO_A->MODER &= ~(1U<<11); // set bit 11 to 0
	// after this step. PA5 is now an output

	/*
	 * the | operator ensure that only bit 0 or bit x
	 * is set to 1, and we leave other bits as they initially are
	 *
	 * */

	while(1){

	// writing+ data is through GPIOx_ODR
		GPIO_A->ODR |= (1U<<5); // setting pin 5

	} /*End while() */


} /* End main ()*/
