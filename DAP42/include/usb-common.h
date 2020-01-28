/*
 * usb-common.h
 *
 *  Created on: Jan 1, 2020
 *      Author: technix
 */

#ifndef INCLUDE_USB_COMMON_H_
#define INCLUDE_USB_COMMON_H_

#include <stm32f0xx.h>
#include <usb.h>
#include <usb_std.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

void usb_init(void);

__END_DECLS

#endif /* INCLUDE_USB_COMMON_H_ */
