/*
 * usb-vcp.c
 *
 *  Created on: Jan 2, 2020
 *      Author: technix
 */

#include "usb-vcp.h"

#include <stdbool.h>
#include <usb_cdc.h>

static struct usb_cdc_line_coding line_coding;
static bool serial_enabled;

static void set_line_coding(struct usb_cdc_line_coding *new_line_coding)
{
	// Check the validity of the settings.
	if (new_line_coding)
	{

	}
}

void vcp_init(void)
{
	static const struct usb_cdc_line_coding default_line_coding =
	{
			.dwDTERate = 115200,
			.bCharFormat = USB_CDC_1_STOP_BITS,
			.bParityType = USB_CDC_NO_PARITY,
			.bDataBits = 8
	};

	serial_enabled = false;
	set_line_coding(&default_line_coding);
}

static void vcp_enable(bool dtr)
{
	if (serial_enabled != dtr)
	{
		if (dtr)
		{

		}
		else
		{

		}

		serial_enabled = dtr;
	}
}

usbd_respond vcp_control(usbd_device *dev, usbd_ctlreq *req, usbd_rqc_callback *callback)
{
	switch (req->bRequest)
	{
	case USB_CDC_SET_LINE_CODING:
		set_line_coding((struct usb_cdc_line_coding *)req->data);
		return usbd_ack;
		break;

	case USB_CDC_GET_LINE_CODING:
		dev->status.data_ptr = &line_coding;
		dev->status.data_count = sizeof(line_coding);
		return usbd_ack;

	case USB_CDC_SET_CONTROL_LINE_STATE:
		{
			bool dtr = !!(req->wValue & 0x0001); // DTR
			vcp_enable(dtr);
		}
		return usbd_ack;

	case USB_CDC_SEND_BREAK:
		return usbd_ack;

	default:
		return usbd_fail;
	}
}

void vcp_data(usbd_device *dev, uint8_t event, uint8_t ep)
{

}

void vcp_kill(void)
{

}
