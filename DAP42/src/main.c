/*
 * main.c
 *
 *  Created on: Dec 28, 2019
 *      Author: technix
 */

#include <stm32f0xx.h>

#include "rcc.h"

void SystemInit(void)
{
	rcc_init();
}

int main(void)
{
	for (;;)
		__WFE();
}
