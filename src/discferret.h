/****************************************************************************
 *
 *                - DiscFerret Interface Library for C / C++ -
 *
 * Copyright (C) 2010 - 2011 P. A. Pemberton t/a. Red Fox Engineering.
 * All Rights Reserved.
 *
 * This library (libdiscferret.so, discferret.c, discferret.h) is distributed
 * under the Apache License, version 2.0. Distribution is permitted under the
 * terms of the aforementioned License.
 ****************************************************************************/

/**
 * @file discferret.h
 * @brief DiscFerret interface library (libdiscferret)
 * @author Philip Pemberton
 * @date 2010-2011
 */

#ifndef _DISCFERRET_H
#define _DISCFERRET_H

#include <libusb-1.0/libusb.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief	A structure to encapsulate information about a specific DiscFerret device.
 */
typedef struct {
	unsigned char productname[256];		///< Device product name.
	unsigned char manufacturer[256];	///< Device manufacturer.
	unsigned char serialnumber[256];	///< Device serial number.
	uint16_t vid;						///< USB Vendor ID.
	uint16_t pid;						///< USB Product ID.
} DISCFERRET_DEVICE;

/**
 * @brief	Handle to an open DiscFerret device.
 */
typedef struct {
	libusb_device_handle *dh;			///< Libusb device handle.
} DISCFERRET_DEVICE_HANDLE;

/**
 * @brief	DiscFerret library error codes.
 */
typedef enum {
	DISCFERRET_E_OK				=	0,		///< Operation succeeded.
	DISCFERRET_E_ALREADY_INIT	=	-1024,	///< Library already initialised
	DISCFERRET_E_NOT_INIT,					///< Library not initialised yet
	DISCFERRET_E_USB_ERROR,					///< USB error
	DISCFERRET_E_OUT_OF_MEMORY,				///< Out of memory
} DISCFERRET_ERROR;

/**
 * @brief	Initialise libDiscFerret.
 * @note	Must be called before calling any other discferret_* functions.
 * @returns	Error code, or DISCFERRET_E_OK on success.
 */
DISCFERRET_ERROR discferret_init(void);

/**
 * @brief	Shut down libDiscFerret.
 * @note	Must be called after all DiscFerret calls have completed, but before the user application exits.
 * @returns	Error code, or DISCFERRET_E_OK on success.
 */
DISCFERRET_ERROR discferret_done(void);

/**
 * @brief	Enumerate all available DiscFerret devices.
 * @param	devlist		Pointer to a DISCFERRET_DEVICE* block, or NULL.
 * @return	Number of devices found, or one of the DISCFERRET_E_* error constants.
 *
 * This function scans the system for available DiscFerret devices which have
 * not been claimed by another process. It returns either a DISCFERRET_E_xxx
 * constant (if there was an error), or a count of the number of available
 * devices.
 *
 * If devlist is set to NULL, then a count of devices will be performed, but
 * no device list will be returned (for obvious reasons).
 */
int discferret_find_devices(DISCFERRET_DEVICE **devlist);

#ifdef __cplusplus
}
#endif

#endif
