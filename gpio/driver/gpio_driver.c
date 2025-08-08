


#include "gpio_driver.h"



void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx,
						  uint8_t ON_OFF){


	if(ON_OFF == ON){

		switch (pGPIOx){

		case GPIOA:

			GPIOA_CLK_ON();
			break;

		case GPIOB:

			GPIOB_CLK_ON();
			break;

		case GPIOC:

			GPIOC_CLK_ON();
			break;

		case GPIOD:

			GPIOD_CLK_ON();
			break;

		case GPIOE:

			GPIOE_CLK_ON();
			break;

		case GPIOF:

			GPIOF_CLK_EN();
			break;

		case GPIOG:

			GPIOG_CLK_EN();
			break;

		case GPIOH:

			GPIOH_CLK_EN();
			break;

		case GPIOI:

			GPIOI_CLK_EN();
			break;


		 }/* End switch (pGPIOx)*/



	}else{

	/* Clock off block
	 *
	 * Here we chose to turn off a clock for a certain GPIO
	 *
	 * */

		switch (pGPIOx){

				case GPIOA:

					GPIOA_CLK_OFF();
					break;

				case GPIOB:

					GPIOB_CLK_OFF();
					break;

				case GPIOC:

					GPIOC_CLK_OFF();
					break;

				case GPIOD:

					GPIOD_CLK_OFF();
					break;

				case GPIOE:

					GPIOE_CLK_OFF();
					break;

				case GPIOF:

					GPIOF_CLK_OFF();
					break;

				case GPIOG:

					GPIOG_CLK_OFF();
					break;

				case GPIOH:

					GPIOH_CLK_OFF();
					break;

				case GPIOI:

					GPIOI_CLK_OFF();
					break;


				 }/* End switch (pGPIOx)*/



	} /* End if-else */




} /* End GPIO_PeriClockControl() */

// =========================================================


void GPIO_Init(GPIO_Handle_t *pGPIOHandle){

	/*
	 * This function configure the pin of a certain GPIO
	 *
	 * such as : mode, speed, pull pull down resistor, output type
	 *
	 *
	 * */

	

	//1. we speicify if we are in 
	// Interrupt or non interrupt mode

	if(pGPIOHandle->gpio_pin_conf.GPIO_PinMode < ANALOG){
	// Here we are in non interrupt mode	

		// 1.1. Configure the mode of the pin
	pGPIOHandle->gpio_reg_x->MODER |=  pGPIOHandle->gpio_pin_conf.GPIO_PinMode << (2 * pGPIOHandle->gpio_pin_conf.GPIO_PinNumber);	 

	/*
		- The pin mode is given by the user (00,01,...)
		we shift it to the right position
		- The multiplier is 2 because each pin mode
		occupies 2 bits in the GPIOx_MODER register
		- Example: if pin number =1 then 2*1 = 2
		- Recall that counting starts from 0
		- Other example: if pin number =2 (MODER2), then
		2*2 = 4, so we shift the pin mode by 4 bits

		The mode value will be stored in the GPIOx_MODER register

	*/
	
	// Now we start by the othe registers, speed, output type, pull up and pull down resistor

	// 1.2. Configure the speed 
	pGPIOHandle->gpio_reg_x->OSPEEDR |= (pGPIOHandle->gpio_pin_conf.GPIO_PinSpeed << (2 * pGPIOHandle->gpio_pin_conf.GPIO_PinNumber));

	// 1.3. Configure the output type
	pGPIOHandle->gpio_reg_x->OTYPER |= (pGPIOHandle->gpio_pin_conf.GPIO_PinOPType << pGPIOHandle->gpio_pin_conf.GPIO_PinNumber);

	// 1.4. Configure the pull up and pull down resistor
	pGPIOHandle->gpio_reg_x->PUPDR |= (pGPIOHandle->gpio_pin_conf.GPIO_PinPuPdControl << (2 * pGPIOHandle->gpio_pin_conf.GPIO_PinNumber));



	}







}/* End GPIO_Init()   */


