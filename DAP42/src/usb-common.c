/*
 * usb-common.c
 *
 *  Created on: Jan 1, 2020
 *      Author: technix
 */

#include "usb-common.h"

#include <stm32f0xx.h>
#include <usb.h>
#include <usbd_core.h>

#include "usb-descriptors.h"
#include "usb-dap.h"
#include "usb-vcp.h"

usbd_device usbd;
uint32_t usbd_buffer[0x20];

static usbd_respond usb_descriptor(usbd_ctlreq *req, void **address, uint16_t *length);
static usbd_respond usb_control(usbd_device *dev, usbd_ctlreq *req, usbd_rqc_callback *callback);
static usbd_respond usb_config(usbd_device *dev, uint8_t cfg);

void usb_init(void)
{
	// STM32F042 needs a pin re-map before USB can work.
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
	SYSCFG->CFGR1 |= SYSCFG_CFGR1_PA11_PA12_RMP;

	// We use interrupt-driven USB.
	NVIC_EnableIRQ(USB_IRQn);

	// Setting up USB.
	usbd_init(&usbd, &usbd_devfs, USB_EP_SIZE, usbd_buffer, sizeof(usbd_buffer));
	usbd_reg_descr(&usbd, usb_descriptor);
    usbd_reg_config(&usbd, usb_config);
    usbd_reg_control(&usbd, usb_control);

	// Enable and connect USB.
	usbd_enable(&usbd, true);
	usbd_connect(&usbd, true);
}

static usbd_respond usb_descriptor(usbd_ctlreq *req, void **address, uint16_t *length)
{
    const uint8_t dtype = req->wValue >> 8;
    const uint8_t dnumber = req->wValue & 0xFF;
    const void* descriptor;
    uint16_t len = 0;

    switch (dtype)
    {
    case USB_DTYPE_DEVICE:
    	descriptor = &device_descritor;
        break;

    case USB_DTYPE_QUALIFIER:
    	descriptor = &qualifier_descriptor;
    	break;

    case USB_DTYPE_CONFIGURATION:
    	descriptor = &config_descriptor;
    	len = sizeof(config_descriptor);
        break;

    case USB_DTYPE_STRING:
        if (dnumber < (sizeof(string_descriptors) / sizeof(intptr_t)))
        	descriptor = string_descriptors[dnumber];
        else
        	return usbd_fail;
        break;

    default:
        return usbd_fail;
    }

    if (len == 0)
    	len = ((struct usb_header_descriptor*)descriptor)->bLength;

    *address = (void*)descriptor;
    *length = len;
    return usbd_ack;
}

static usbd_respond usb_control(usbd_device *dev, usbd_ctlreq *req, usbd_rqc_callback *callback)
{
	switch ((req->bmRequestType & USB_REQ_RECIPIENT) | (req->wIndex << 2))
	{
	case (USB_REQ_INTERFACE | (0 << 2)):
		return dap_control(dev, req, callback);

	case (USB_REQ_INTERFACE | (1 << 2)):
	case (USB_REQ_INTERFACE | (2 << 2)):
		return vcp_control(dev, req, callback);

	default:
		return usbd_fail;
	}
}

static usbd_respond usb_config(usbd_device *dev, uint8_t cfg)
{
	switch (cfg)
	{
	case 0:
        usbd_ep_deconfig(dev, USB_HID_RXD);
        usbd_reg_endpoint(dev, USB_HID_RXD, NULL);
        usbd_ep_deconfig(dev, USB_HID_TXD);
		usbd_reg_endpoint(dev, USB_HID_TXD, NULL);
		dap_kill();

        usbd_ep_deconfig(dev, USB_CDC_TXC);
        usbd_ep_deconfig(dev, USB_CDC_RXD);
        usbd_reg_endpoint(dev, USB_CDC_RXD, NULL);
        usbd_ep_deconfig(dev, USB_CDC_TXD);
        usbd_reg_endpoint(dev, USB_CDC_TXD, NULL);
        vcp_kill();
        return usbd_ack;

	case 1:
		dap_init();
		usbd_ep_config(dev, USB_HID_RXD, USB_EPTYPE_INTERRUPT, USB_EP_SIZE);
		usbd_reg_endpoint(dev, USB_HID_RXD, dap_data);
		usbd_ep_config(dev, USB_HID_TXD, USB_EPTYPE_INTERRUPT, USB_EP_SIZE);
		usbd_reg_endpoint(dev, USB_HID_TXD, dap_data);
		usbd_ep_write(dev, USB_HID_TXD, NULL, 0);

		vcp_init();
		usbd_ep_config(dev, USB_CDC_TXC, USB_EPTYPE_INTERRUPT, USB_EP_SIZE);
		usbd_ep_write(dev, USB_CDC_TXC, NULL, 0);
		usbd_ep_config(dev, USB_CDC_RXD, USB_EPTYPE_BULK, USB_EP_SIZE);
		usbd_reg_endpoint(dev, USB_CDC_RXD, vcp_data);
		usbd_ep_config(dev, USB_CDC_TXD, USB_EPTYPE_BULK, USB_EP_SIZE);
		usbd_reg_endpoint(dev, USB_CDC_TXD, vcp_data);
		return usbd_ack;

	default:
		return usbd_fail;
	}
}

void USB_IRQHandler(void)
{
	// Pass interrupt handling to USB driver.
	usbd_poll(&usbd);
}
