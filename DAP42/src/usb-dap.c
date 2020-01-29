/*
 * usb-dap.c
 *
 *  Created on: Jan 2, 2020
 *      Author: technix
 */

#include "usb-dap.h"

#include "usb-descriptors.h"

bool dap_enabled;

void dap_init(void)
{
	dap_enabled = false;
}

usbd_respond dap_control(usbd_device *dev, usbd_ctlreq *req, usbd_rqc_callback *callback)
{
	if (req->bRequest == USB_STD_GET_DESCRIPTOR)
	{
		switch (req->wValue >> 8)
		{
        case USB_DTYPE_HID:
            dev->status.data_ptr = (uint8_t *)(&config_descriptor.hid_desc);
            dev->status.data_count = sizeof(config_descriptor.hid_desc);
            return usbd_ack;

        case USB_DTYPE_HID_REPORT:
            dev->status.data_ptr = (uint8_t *)report_descriptor;
            dev->status.data_count = sizeof(report_descriptor);
            return usbd_ack;

		default:
			return usbd_fail;
		}
	}
	return usbd_fail;
}

void dap_data(usbd_device *dev, uint8_t event, uint8_t ep)
{

}

void dap_kill(void)
{

}
