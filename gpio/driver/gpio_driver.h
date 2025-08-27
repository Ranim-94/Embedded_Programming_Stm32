#include "stm32f407G.h"

/* Create a structure to configure a pin of a GPIO */

typedef struct{

	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;

} GPIO_PinConf_t;

/* For the members of PinConf_t, each of the members
   can take a value from the Enum defined below
*/

// ------------ Coding states for GPIO Registers ------------

// see section 8.4 from refrence manual

typedef enum GPIO_Mode {IN,OUT,ALT,ANALOG,
						INT_FALLING_EDGE, INT_RISING_EDGE,
                        INT_FALL_AND_RISE} gpio_mode;
// ALT for alternate
// INT for interrupt

/*
	Note: 
	- the order of the enum follows the same order 
            in the reference manual
	- IN is for 0 (or 00), OUT is for 1 (or 01),....

*/

// Pull up and pull down resistor
typedef enum GPIO_Resistor {NO_PULLUP,PULLUP,PULLDOWN,REVERSED} gpio_resistor;

// Speed register
typedef enum GPIO_Speed {LOW,MEDIUM,HIGH,VERY} gpio_speed;

// Output type: open drain or push pull
typedef enum GPIO_Output {PUSH_PULL,OPEN_DRAIN} gpio_output;

// Pin numbers as enum for better type safety
typedef enum {
    GPIO_PIN_0 = 0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_15

} GPIO_PinNumber_t;



/* Create a global gpio struct which contains
 * definition of gpio port and gpio pin conf
 * 	*/

typedef struct{

	GPIO_RegDef_t *gpio_reg_x;
	// this can be GPIOA, GPIOB,....

	GPIO_PinConf_t gpio_pin_conf;

} GPIO_Handle_t;


// ============================================================

typedef struct {
    GPIO_RegDef_t *base;
    void (*clk_on)(void);
    void (*clk_off)(void);
} GPIO_ClkMap;

typedef struct gpio_driver{
    GPIO_RegDef_t *base;
    void (*reset_gpiox)(void);

} GPIO_Reset;


// Declare the array and port count as extern
extern GPIO_ClkMap gpio_clk_map[];
extern GPIO_Reset gpio_reset_table[];

#define NB_GPIO_PORTS (sizeof(gpio_clk_map)/sizeof(gpio_clk_map[0]))


// ================== GPIO Clock Control Function Declarations ==================

void GPIOA_CLK_ON(void);

void GPIOA_CLK_OFF(void);
void GPIOB_CLK_ON(void);
void GPIOB_CLK_OFF(void);
void GPIOC_CLK_ON(void);
void GPIOC_CLK_OFF(void);
void GPIOD_CLK_ON(void);
void GPIOD_CLK_OFF(void);
void GPIOE_CLK_ON(void);
void GPIOE_CLK_OFF(void);
void GPIOF_CLK_ON(void);
void GPIOF_CLK_OFF(void);
void GPIOG_CLK_ON(void);
void GPIOG_CLK_OFF(void);
void GPIOH_CLK_ON(void);
void GPIOH_CLK_OFF(void);
void GPIOI_CLK_ON(void);
void GPIOI_CLK_OFF(void);

// ================== GPIO Reset Function Declarations ==================

void GPIOA_RESET(void);
void GPIOB_RESET(void);
void GPIOC_RESET(void);
void GPIOD_RESET(void);
void GPIOE_RESET(void);
void GPIOF_RESET(void);
void GPIOG_RESET(void);
void GPIOH_RESET(void);
void GPIOI_RESET(void);

// ================== SYSCFG Clock Control Functions ==================
void SYSCFG_CLK_ON(void);
void SYSCFG_CLK_OFF(void);


// ================== Now API Part (function part) ==================


void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx,	
						  uint8_t ON_OFF);

void GPIO_Init(GPIO_Handle_t *pGPIOHandle);

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

// Read and Write functions

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,
							  uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,
						uint8_t PinNumber, uint8_t Value);

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,
							uint16_t Value);

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, 
                         uint8_t PinNumber);




