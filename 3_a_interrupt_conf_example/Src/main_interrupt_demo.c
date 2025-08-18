

/*
 * Goal of this demo:
 * a simple code to conf interrupt for USART3 peripheral
 *
 * */


#include<stdio.h>
#include<stdint.h>

int main(){


   /*
    * Task:
    *
    * 1) Pend the pending bit for USART3 IRQ nb in NVIC peripheral
    *
    * 2) Enable the interrupt once the pending is done
    *
    * */

	/*
	 * Sol for 1)
	 *
	 * - pending a bit is done via NVIC_ISPR register
	 * 		-> ISPR = Interrupt Set-pending Registers
	 * 		-> see the generic user guide section 4.2.4
	 *
	 * - the peripheral is USART3. which have an IRQ nb = 39
	 * 		-> recall that in interrupt programming, there is
	 * 		the peripheral side (USART3) and the processor side (arm cortex M)
	 * 		-> identify the IRQ number of the peripheral using the vector table
	 * 		in the reference manual of the microcontroller
	 *
	 *
	 * 	- we have 8 NVIC_ISPR registers, each handle 32 interrupt
	 *
	 * 		- we need to know 2 things:
	 * 			- which register we use among the 8
	 * 			- the bit position in the selected register
	 * 			- the answer reside in the IRQ number
	 *
	 * 		- since IRQ = 39 for USART3 peripheral,
	 * 		 - we need to use NVIC_ISPR1 (the 2nd register)
	 *
	 * 		- the bit position is calculated using a % operation
	 * 		 39%32 = 7 -> 7th bit
	 *
	 * */


	//============== Step 1: Pending bit ==============

	uint32_t usart_irq_nb = 39;

	uint32_t *ispr1_reg = (uint32_t*)(0XE000E200 + 4);

	/*
	 * 0XE000E200 -> address of ISPR0
	 * 		- see Table 4-2 NVIC register summary in the generic user guide
	 * for ISPR1: we add 4 (4 byte) since we have 32 bit width register
	 *
	 * */

	// set the bit for the pending register -> it will set the 7th bit
	*ispr1_reg |= (1<< (usart_irq_nb%32));


	//============== Step 2: enabling the interrupt ==============

	/*
	 *  this is done via NVIC_ISER0 ()
	 *  	-> Interrupt Set-enable Registers
	 *  	-> see section 4.2.2 in the generic user guide
	 *
	 * */

	uint32_t *iser1_reg = (uint32_t*)(0XE000E100 + 4);

	/*
	 * ISER0 base address = 0xE000E100
	 * 	-> from the table in the generic user guide
	 * */

	// Enable the interrupt by setting the bit

	*iser1_reg |= (1<< (usart_irq_nb%32));


	/*
	 * Note: to debug registers (make sure that we have)
	 *
	 * set the 7th bit, in debug mode we can go to window -> sfr
	 *
	 * 	- under NVIC we can see each register
	 *
	 * */

	//============== Step 3: Implement the interrupt ==============

	/*
	 * the name of the function for the interrupt
	 * can be found in the startup file, inside the startup folder
	 *
	 * */


} /* End main()  */

// Implement the interrupt
void USART3_IRQHandler(void){

 printf("Entering USART4 ISR \n");

}  /* End USART3_IRQHandler  */



/*
 *  Summary about the main points:
 *
 *  - interrupts require 2 side:
 *  	- a peripheral from the MCU like USART3
 *  	- we must identify the IRQ number using vector table
 *  	 founded in the reference manual
 *
 *  - once the IRQ number is specified, we need to configure the
 *  registers, depending on the task
 *
 *  	-> for NVIC peripherals, we have many registers such as:
 *  	ISPR : pending the interrupt in the pending state
 *  	ISER (to enable the interrupt)
 *
 *  	-> we have 8 of these registers, since we
 *  	have 240 interrupts in the cortex M archi
 *
 *  	-> each register handle 32 interrupts
 *
 *
 *
 *
 * */






