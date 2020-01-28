/*
 * usb-dap.c
 *
 *  Created on: Jan 2, 2020
 *      Author: technix
 */

#include "usb-dap.h"

bool dap_enabled;

void dap_init(void)
{
	dap_enabled = false;
}

usbd_respond dap_control(usbd_device *dev, usbd_ctlreq *req, usbd_rqc_callback *callback)
{
	return usbd_fail;
}

void dap_data(usbd_device *dev, uint8_t event, uint8_t ep)
{

}

void dap_kill(void)
{

}
