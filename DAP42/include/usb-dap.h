/*
 * usb-dap.h
 *
 *  Created on: Jan 2, 2020
 *      Author: technix
 */

#ifndef INCLUDE_USB_DAP_H_
#define INCLUDE_USB_DAP_H_

#include <stm32f0xx.h>
#include <usb.h>
#include <usb_std.h>
#include <stdbool.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

extern bool dap_enabled;

void dap_init(void);
usbd_respond dap_control(usbd_device *dev, usbd_ctlreq *req, usbd_rqc_callback *callback);
void dap_data(usbd_device *dev, uint8_t event, uint8_t ep);
void dap_kill(void);

__END_DECLS

#endif /* INCLUDE_USB_DAP_H_ */
