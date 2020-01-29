/*
 * usb-hid-descriptors.h
 *
 *  Created on: Jan 1, 2020
 *      Author: technix
 */

#ifndef INCLUDE_USB_HID_DESCRIPTORS_H_
#define INCLUDE_USB_HID_DESCRIPTORS_H_

#include <usb.h>
#include <usb_std.h>
#include <usb_hid.h>

static const uint8_t report_descriptor[] =
{
		HID_RI_USAGE_PAGE(16, 0xff00),
		HID_USAGE(0),
		HID_COLLECTION(HID_APPLICATION_COLLECTION),
			HID_LOGICAL_MINIMUM(0x00),
			HID_LOGICAL_MAXIMUM(0xff),

			HID_REPORT_ID(1),
			HID_REPORT_SIZE(8),
			HID_REPORT_COUNT(64),
			HID_USAGE(0),
			HID_INPUT(HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

			HID_REPORT_ID(2),
			HID_REPORT_SIZE(8),
			HID_REPORT_COUNT(64),
			HID_USAGE(0),
			HID_OUTPUT(HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
		HID_END_COLLECTION
};

#endif /* INCLUDE_USB_HID_DESCRIPTORS_H_ */
