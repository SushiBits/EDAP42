/*
 * main.c
 *
 *  Created on: Dec 28, 2019
 *      Author: technix
 */

#include <stm32f0xx.h>

#include <DAP.h>

#include "rcc.h"
#include "usb-common.h"


void SystemInit(void)
{
	rcc_init();
}

int main(void)
{
	DAP_Setup();
	usb_init();

	for (;;)
		__WFE();
}
