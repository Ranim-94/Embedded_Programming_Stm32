  

/*
 * Goal: implement a header file for stm board
 *
 * understand more the characteristic of developing
 * bare metal software for MCU
 *
 * */


#pragma once

#include<stdint.h>

#define __vo volatile



#define FLASH_BASEADDR	0x08000000U
#define SRAM1_BASEADDR	0x20000000U
#define SRAM2_BASEADDR	0x2001C000U
#define ROM_BASEADDR	0x1FFF0000U
#define SRAM 			SRAM1_BASEADDR

/*
 * See table 3 in chapter 2 "Memory and bus architecture"
 * for the above addresses
 *
 * The "U" is to tell the compiler that the address is unsigned
 * because it will interpret by default as signed int, and
 * we know an address can't be a negative nb
 *
 * */

// ============ Buses ============

/*
 * Now we move to bus addresses, AHBx and APB
 *
 * for that we can see the memory map (see table 1 in chapter 2 also)
 * */

#define PERIPH_BASEADDR 		(0x40000000U)
#define APB1PERIPH_BASEADDR 	(PERIPH_BASEADDR)
#define APB2PERIPH_BASEADDR		(0x40010000U)
#define AHB1PERIPH_BASEADDR		(0x40020000U)
#define AHB2PERIPH_BASEADDR		(0x50000000U)

// ======== GPIO ========

/*
 * Referring to the data sheet (functional block diagram)
 *
 * and the memory map table in the reference manual,
 * all GPIO port are connected to AHB1 bus,
 *
 * so from the base address of AHB1 we can reach every
 * GPIO by some offset
 *
 * */

#define GPIOA_BASEADDR (AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR (AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR (AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR (AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR (AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR (AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR (AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR (AHB1PERIPH_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR (AHB1PERIPH_BASEADDR + 0x2000)
#define RCC_BASEADDR (AHB1PERIPH_BASEADDR + 0x3800)

/* Instantiate */


/*
 * Now we start creating some structure to hold
 * different registers of the GPIO peripheral
 * */

typedef struct{

	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];

} GPIO_RegDef_t;

/*
 * Note: it is important when creating the fields
 * to conserve the order as in the reference manual,
 * so we can have the appropriate offset (address)
 * for each register
 *
 * */

/*2nd step: instantiate some GPIO port at sepecific addresses
 * according to memory map
 *
 *
 * */

#define GPIOA ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH ((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI ((GPIO_RegDef_t*)GPIOI_BASEADDR)

// ============= Clock configuration using RCC =============


/*  Now for RCC, responsible for the clock */

typedef struct{

  __vo uint32_t CR;            /*  Address offset: 0x00 */
  __vo uint32_t PLLCFGR;       /*									Address offset: 0x04 */
  __vo uint32_t CFGR;          /* 	Address offset: 0x08 */
  __vo uint32_t CIR;           /*  Address offset: 0x0C */
  __vo uint32_t AHB1RSTR;      /* 	Address offset: 0x10 */
  __vo uint32_t AHB2RSTR;      /*     										Address offset: 0x14 */
  __vo uint32_t AHB3RSTR;      /*	Address offset: 0x18 */
  	   uint32_t  RESERVED0;     /*            */
  __vo uint32_t APB1RSTR;      /*   Address offset: 0x20 */
  __vo uint32_t APB2RSTR;      /*	Address offset: 0x24 */
  	   uint32_t RESERVED1[2];  /*                                                  */
  __vo uint32_t AHB1ENR;       /*	Address offset: 0x30 */
  __vo uint32_t AHB2ENR;       /* 										Address offset: 0x34 */
  __vo uint32_t AHB3ENR;       /*	Address offset: 0x38 */
  	   uint32_t RESERVED2;     /*                                                     */
  __vo uint32_t APB1ENR;       /*	Address offset: 0x40 */
  __vo uint32_t APB2ENR;       /*	Address offset: 0x44 */
  	   uint32_t RESERVED3[2];  /*                                                 */
  __vo uint32_t AHB1LPENR;     /*	Address offset: 0x50 */
  __vo uint32_t AHB2LPENR;     /*									Address offset: 0x54 */
  __vo uint32_t AHB3LPENR;     /*	Address offset: 0x58 */
  	   uint32_t RESERVED4;     /*                                                   */
  __vo uint32_t APB1LPENR;     /*	Address offset: 0x60 */
  __vo uint32_t APB2LPENR;     /*	Address offset: 0x64 */
  	   uint32_t RESERVED5[2];  /*   0x68,0x6C                       */
  __vo uint32_t BDCR;          /*	Address offset: 0x70 */
  __vo uint32_t CSR;           /*	Address offset: 0x74 */
  	   uint32_t RESERVED6[2];  /*  Reserved, 0x78-0x7C                                                  */
  __vo uint32_t SSCGR;         /* 	Address offset: 0x80 */
  __vo uint32_t PLLI2SCFGR;    /*	Address offset: 0x84 */
  __vo uint32_t PLLSAICFGR;    /*  Address offset: 0x88 */
  __vo uint32_t DCKCFGR;       /* 	Address offset: 0x8C */
  __vo uint32_t CKGATENR;      /*   Address offset: 0x90 */
  __vo uint32_t DCKCFGR2;      /*	Address offset: 0x94 */

} RCC_RegDef_t;

/* Instantiate RCC struct at RCC specific address */
#define RCC ((RCC_RegDef_t*)RCC_BASEADDR)


// GENRIC MACROS used in different places
// such as comparison, ...

#define ON 1
#define OFF 0









