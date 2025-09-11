


#include"stm32f407G.h"


uint8_t GPIO_BASEADDR_TO_CODE(GPIO_RegDef_t *pGPIOx){
/*
	Based on some addresse of some port (GPIOA,GPIOB,...)
	We transform them into some code

	See 9.2.3 in the ref manual

*/

uint8_t porte_code;

	switch ((uint32_t)pGPIOx){
		case (uint32_t)GPIOA:
			porte_code = 0;
			break;

		case (uint32_t)GPIOB:
			porte_code = 1;
			break;

		case (uint32_t)GPIOC:
			porte_code = 2;
			break;

		case (uint32_t)GPIOD:
			porte_code = 3;
			break;

		case (uint32_t)GPIOE:
			porte_code = 4;
			break;

		case (uint32_t)GPIOF:
			porte_code = 5;
			break;

		case (uint32_t)GPIOG:
			porte_code = 6;
			break;

		case (uint32_t)GPIOH:
			porte_code = 7;
			break;

		case (uint32_t)GPIOI:
			porte_code = 8;
			break;

		default:
			return 0;
			break;

	} /* End switch case*/

	return porte_code;

} /* End GPIO_BASEADDR_TO_CODE() */
