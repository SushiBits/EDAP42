/*
 * rcc.c
 *
 *  Created on: Jan 1, 2020
 *      Author: technix
 */

#include "rcc.h"

void rcc_init(void)
{
	// Turn on HSE oscillator, f = 8MHz
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY));

	// Turn on PLL, f = HSE * 6 = 48MHz
	SET_FIELD(RCC->CFGR, RCC_CFGR_PLLSRC_Msk, RCC_CFGR_PLLSRC_HSE_PREDIV);
	SET_FIELD(RCC->CFGR, RCC_CFGR_PLLMUL_Msk, RCC_CFGR_PLLMUL6);
	RCC->CFGR2 = 0;
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY));

	// Clock the CPU from PLL, HCLK = 48MHz
	FLASH->ACR = (1 << FLASH_ACR_LATENCY_Pos) | FLASH_ACR_PRFTBE;
	SET_FIELD(RCC->CFGR, RCC_CFGR_SW_Msk, RCC_CFGR_SW_PLL);
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

	// Clock the peripherals from PLL, HCLK = 48MHz
	RCC->CFGR3 = RCC_CFGR3_USBSW_PLLCLK;
}
