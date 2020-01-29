/*
 * usb-descriptors.h
 *
 *  Created on: Jan 1, 2020
 *      Author: technix
 */

#ifndef INCLUDE_USB_DESCRIPTORS_H_
#define INCLUDE_USB_DESCRIPTORS_H_

#include <usb.h>
#include <usb_std.h>
#include <usb_hid.h>
#include <usb_cdc.h>

#include "usb-hid-descriptors.h"

#define USB_EP_SIZE 64

#define USB_HID_RXD (USB_EPDIR_IN | 0x01)
#define USB_HID_TXD (USB_EPDIR_OUT | 0x01)
#define USB_CDC_TXC (USB_EPDIR_OUT | 0x02)
#define USB_CDC_RXD (USB_EPDIR_IN | 0x03)
#define USB_CDC_TXD (USB_EPDIR_OUT | 0x03)

static const struct usb_device_descriptor device_descritor =
{
		.bLength = sizeof(struct usb_device_descriptor),
		.bDescriptorType = USB_DTYPE_DEVICE,
		.bcdUSB = VERSION_BCD(2, 0, 0),
		.bDeviceClass = USB_CLASS_IAD,
		.bDeviceSubClass = USB_SUBCLASS_IAD,
		.bDeviceProtocol = USB_PROTO_IAD,
		.bMaxPacketSize0 = USB_EP_SIZE,
		.idVendor = 0x0002,
		.idProduct = 0xda42,
		.bcdDevice = VERSION_BCD(1, 1, 0),
		.iManufacturer = 1,
		.iProduct = 2,
		.iSerialNumber = INTSERIALNO_DESCRIPTOR,
		.bNumConfigurations = 1
};

static const struct usb_qualifier_descriptor qualifier_descriptor =
{
		.bLength = sizeof(struct usb_qualifier_descriptor),
		.bDescriptorType = USB_DTYPE_QUALIFIER,
		.bcdUSB = VERSION_BCD(2, 0, 0),
		.bDeviceClass = USB_CLASS_IAD,
		.bDeviceSubClass = USB_SUBCLASS_IAD,
		.bDeviceProtocol = USB_PROTO_IAD,
		.bMaxPacketSize0 = USB_EP_SIZE,
		.bNumConfigurations = 1,
		.bReserved = 0
};

static const struct usb_string_descriptor language_string = USB_ARRAY_DESC(USB_LANGID_ENG_US);
static const struct usb_string_descriptor vendor_string = USB_STRING_DESC("SushiBits Innovation");
static const struct usb_string_descriptor product_string = USB_STRING_DESC("SushiBits One with CMSIS-DAP");
static const struct usb_string_descriptor hid_string = USB_STRING_DESC("SushiBits One CMSIS-DAP");
static const struct usb_string_descriptor cdc_string = USB_STRING_DESC("SushiBits One Virtual COM Port");
static const struct usb_string_descriptor *string_descriptors[] =
{
		&language_string,
		&vendor_string,
		&product_string,
		&hid_string,
		&cdc_string
};

static const struct config_descriptor
{
	struct usb_config_descriptor config;

	struct usb_iad_descriptor hid_iad;
	struct usb_interface_descriptor hid_if;
	struct usb_hid_descriptor hid_desc;
	struct usb_endpoint_descriptor hid_ep[2];

	struct usb_iad_descriptor cdc_iad;
	struct usb_interface_descriptor cdc_cif;
	struct usb_cdc_header_desc cdc_desc;
	struct usb_cdc_call_mgmt_desc cdc_mgmt;
	struct usb_cdc_acm_desc cdc_acm;
	struct usb_cdc_union_desc cdc_union;
	struct usb_endpoint_descriptor cdc_cep[1];
	struct usb_interface_descriptor cdc_dif;
	struct usb_endpoint_descriptor cdc_dep[2];
} __attribute__((packed)) config_descriptor =
{
		.config =
		{
				.bLength = sizeof(struct usb_config_descriptor),
				.bDescriptorType = USB_DTYPE_CONFIGURATION,
				.wTotalLength = sizeof(struct config_descriptor),
				.bNumInterfaces = 3,
				.bConfigurationValue = 1,
				.iConfiguration = NO_DESCRIPTOR,
				.bmAttributes = USB_CFG_ATTR_RESERVED,
				.bMaxPower = USB_CFG_POWER_MA(250)
		},

		.hid_iad =
		{
				.bLength = sizeof(struct usb_iad_descriptor),
				.bDescriptorType = USB_DTYPE_INTERFASEASSOC,
				.bFirstInterface = 0,
				.bInterfaceCount = 1,
				.bFunctionClass = USB_CLASS_HID,
				.bFunctionSubClass = USB_HID_SUBCLASS_NONBOOT,
				.bFunctionProtocol = USB_HID_PROTO_NONBOOT,
				.iFunction = 3
		},
		.hid_if =
		{
				.bLength = sizeof(struct usb_interface_descriptor),
				.bDescriptorType = USB_DTYPE_INTERFACE,
				.bInterfaceNumber = 0,
				.bAlternateSetting = 0,
				.bNumEndpoints = 2,
				.bInterfaceClass = USB_CLASS_HID,
				.bInterfaceSubClass = USB_HID_SUBCLASS_NONBOOT,
				.bInterfaceProtocol = USB_HID_PROTO_NONBOOT,
				.iInterface = 3
		},
		.hid_desc =
		{
				.bLength = sizeof(struct usb_hid_descriptor),
				.bDescriptorType = USB_DTYPE_HID,
				.bcdHID = VERSION_BCD(1, 1, 1),
				.bCountryCode = USB_HID_COUNTRY_US,
				.bNumDescriptors = 1,
				.bDescriptorType0 = USB_DTYPE_HID_REPORT,
				.wDescriptorLength0 = sizeof(report_descriptor)
		},
		.hid_ep =
		{
				{
						.bLength = sizeof(struct usb_endpoint_descriptor),
						.bDescriptorType = USB_DTYPE_ENDPOINT,
						.bEndpointAddress = USB_HID_RXD,
						.bmAttributes = USB_EPTYPE_INTERRUPT,
						.wMaxPacketSize = USB_EP_SIZE,
						.bInterval = 1
				},
				{
						.bLength = sizeof(struct usb_endpoint_descriptor),
						.bDescriptorType = USB_DTYPE_ENDPOINT,
						.bEndpointAddress = USB_HID_TXD,
						.bmAttributes = USB_EPTYPE_INTERRUPT,
						.wMaxPacketSize = USB_EP_SIZE,
						.bInterval = 1
				}
		},

		.cdc_iad =
		{
				.bLength = sizeof(struct usb_iad_descriptor),
				.bDescriptorType = USB_DTYPE_INTERFASEASSOC,
				.bFirstInterface = 1,
				.bInterfaceCount = 2,
				.bFunctionClass = USB_CLASS_CDC,
				.bFunctionSubClass = USB_CDC_SUBCLASS_ACM,
				.bFunctionProtocol = USB_CDC_PROTO_NONE,
				.iFunction = 4
		},
		.cdc_cif =
		{
				.bLength = sizeof(struct usb_interface_descriptor),
				.bDescriptorType = USB_DTYPE_INTERFACE,
				.bInterfaceNumber = 1,
				.bAlternateSetting = 0,
				.bNumEndpoints = 1,
				.bInterfaceClass = USB_CLASS_CDC,
				.bInterfaceSubClass = USB_CDC_SUBCLASS_ACM,
				.bInterfaceProtocol = USB_CDC_PROTO_NONE,
				.iInterface = 4
		},
		.cdc_desc =
		{
				.bFunctionLength = sizeof(struct usb_cdc_header_desc),
				.bDescriptorType = USB_DTYPE_CS_INTERFACE,
				.bDescriptorSubType = USB_DTYPE_CDC_HEADER,
				.bcdCDC = VERSION_BCD(1, 2, 0)
		},
		.cdc_mgmt =
		{
				.bFunctionLength = sizeof(struct usb_cdc_call_mgmt_desc),
				.bDescriptorType = USB_DTYPE_CS_INTERFACE,
				.bDescriptorSubType = USB_DTYPE_CDC_CALL_MANAGEMENT,
				.bmCapabilities = 0,
				.bDataInterface = 2
		},
		.cdc_acm =
		{
				.bFunctionLength = sizeof(struct usb_cdc_acm_desc),
				.bDescriptorType = USB_DTYPE_CS_INTERFACE,
				.bDescriptorSubType = USB_DTYPE_CDC_ACM,
				.bmCapabilities = USB_CDC_CAP_LINE | USB_CDC_CAP_BRK
		},
		.cdc_union =
		{
				.bFunctionLength = sizeof(struct usb_cdc_union_desc),
				.bDescriptorType = USB_DTYPE_CS_INTERFACE,
				.bDescriptorSubType = USB_DTYPE_CDC_UNION,
				.bMasterInterface0 = 1,
				.bSlaveInterface0 = 2
		},
		.cdc_cep =
		{
				{
						.bLength = sizeof(struct usb_endpoint_descriptor),
						.bDescriptorType = USB_DTYPE_ENDPOINT,
						.bEndpointAddress = USB_CDC_TXC,
						.bmAttributes = USB_EPTYPE_INTERRUPT,
						.wMaxPacketSize = USB_EP_SIZE,
						.bInterval = 1
				}
		},
		.cdc_dif =
		{
				.bLength = sizeof(struct usb_interface_descriptor),
				.bDescriptorType = USB_DTYPE_INTERFACE,
				.bInterfaceNumber = 2,
				.bAlternateSetting = 0,
				.bNumEndpoints = 2,
				.bInterfaceClass = USB_CLASS_CDC_DATA,
				.bInterfaceSubClass = USB_SUBCLASS_NONE,
				.bInterfaceProtocol = USB_PROTO_NONE,
				.iInterface = 4
		},
		.cdc_dep =
		{
				{
						.bLength = sizeof(struct usb_endpoint_descriptor),
						.bDescriptorType = USB_DTYPE_ENDPOINT,
						.bEndpointAddress = USB_CDC_RXD,
						.bmAttributes = USB_EPTYPE_BULK,
						.wMaxPacketSize = USB_EP_SIZE,
						.bInterval = 1
				},
				{
						.bLength = sizeof(struct usb_endpoint_descriptor),
						.bDescriptorType = USB_DTYPE_ENDPOINT,
						.bEndpointAddress = USB_CDC_TXD,
						.bmAttributes = USB_EPTYPE_BULK,
						.wMaxPacketSize = USB_EP_SIZE,
						.bInterval = 1
				}
		}
};


#endif /* INCLUDE_USB_DESCRIPTORS_H_ */
