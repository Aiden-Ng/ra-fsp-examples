/***********************************************************************************************************************
 * File Name    : rm_usbx_pprn_descriptor.c
 * Description  : Contains macros and functions used in usbx_pprn_thread_entry.c
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2022 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/

 /******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include <r_usb_basic.h>
#include <r_usb_basic_api.h>
#include "r_usb_basic_cfg.h"
#include "usbx_pprn_ep.h"

/******************************************************************************
 Macro definitions
 ******************************************************************************/
/* bcdUSB */
#define USB_BCDNUM                      (0x0200U)
/* Release Number */
#define USB_RELEASE                     (0x0200U)
/* DCP max packet size */
#define USB_DCPMAXP                     (64U)
/* Configuration number */
#define USB_CONFIGNUM                   (1U)
/* Vendor ID */
#define USB_VENDORID                    (0x0000U)
/* Product ID */
#define USB_PRODUCTID                   (0x0007U)

/* Descriptor length */
#define USB_PPRN_QD_LEN                 (10U)

/* Descriptor data Mask */
#define USB_UCHAR_MAX                   (0xffU)
#define USB_W_TOTAL_LENGTH_MASK         (256U)
#define USB_W_MAX_PACKET_SIZE_MASK      (64U)

/* Define device framework.  */
#define CD_LEN (9+9+7+((DEMO_PROTOCOL > 1) ? 7 : 0))

#define DEMO_PROTOCOL   (1U)    /* 1-Uni-dir, 2-Bi-dir, 3-Bi-dir-1284. Do not set 3 (uncare) */

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/

/******************************************************************************
 Exported global variables
 ******************************************************************************/

/******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/
uint8_t g_device_framework_full_speed[] = {

    /* Device descriptor */
    USB_DD_BLENGTH,                                                       /*  0:bLength */
    USB_DT_DEVICE,                                                        /*  1:bDescriptorType */
    (uint8_t) (USB_BCDNUM & (uint8_t) USB_UCHAR_MAX),                     /*  2:bcdUSB_lo */
    (uint8_t) ((uint8_t) (USB_BCDNUM >> 8) & (uint8_t) USB_UCHAR_MAX),    /*  3:bcdUSB_hi */
    0x00,                                                                 /*  4:bDeviceClass */
    0x00,                                                                 /*  5:bDeviceSubClass */
    0x00,                                                                 /*  6:bDeviceProtocol */
    (uint8_t) USB_DCPMAXP,                                                /*  7:bMAXPacketSize(for DCP) */
    (uint8_t) (USB_VENDORID & (uint8_t) USB_UCHAR_MAX),                   /*  8:idVendor_lo */
    (uint8_t) ((uint8_t) (USB_VENDORID >> 8) & (uint8_t) USB_UCHAR_MAX),  /*  9:idVendor_hi */
    (uint8_t) (USB_PRODUCTID & (uint8_t) USB_UCHAR_MAX),                  /* 10:idProduct_lo */
    (uint8_t) ((uint8_t) (USB_PRODUCTID >> 8) & (uint8_t) USB_UCHAR_MAX), /* 11:idProduct_hi */
    (uint8_t) (USB_RELEASE & (uint8_t) USB_UCHAR_MAX),                    /* 12:bcdDevice_lo */
    (uint8_t) ((uint8_t) (USB_RELEASE >> 8) & (uint8_t) USB_UCHAR_MAX),   /* 13:bcdDevice_hi */
    1,                                                                    /* 14:iManufacturer */
    2,                                                                    /* 15:iProduct */
    3,                                                                    /* 16:iSerialNumber */
    USB_CONFIGNUM,                                                        /* 17:bNumConfigurations */

    /* Configuration Descriptor */
    USB_CD_BLENGTH,                                                       /*  0:bLength */
#ifdef HIGH_SPEED_CONFIG
    USB_DT_OTHER_SPEED_CONF,                                              /*  1:bDescriptorType */ /* For High-speed */
#else
    USB_DT_CONFIGURATION,                                                 /*  1:bDescriptorType */ /* For Full-speed */
#endif
    (uint8_t) (CD_LEN % USB_W_TOTAL_LENGTH_MASK),                         /*  2:wTotalLength(L) */
    (uint8_t) (CD_LEN / USB_W_TOTAL_LENGTH_MASK),                         /*  3:wTotalLength(H) */
    1,                                                                    /*  4:bNumInterfaces */
    1,                                                                    /*  5:bConfigurationValue */
    0,                                                                    /*  6:iConfiguration */
    (uint8_t) (USB_CF_RESERVED | USB_CF_SELFP),                           /*  7:bmAttributes */
    (uint8_t) (10 / 2),                                                   /*  8:bMaxPower (2mA unit) */

    /* Interface Descriptor */
    USB_ID_BLENGTH,                                                       /*  0:bLength */
    USB_DT_INTERFACE,                                                     /*  1:bDescriptor */
    0,                                                                    /*  2:bInterfaceNumber */
    0,                                                                    /*  3:bAlternateSetting */
    (DEMO_PROTOCOL > 1) ? 2 : 1,                                          /*  4:bNumEndpoints */
    USB_IFCLS_PRN,                                                        /*  5:bInterfaceClass(Printer) */
    0x01,                                                                 /*  6:bInterfaceSubClass */
    DEMO_PROTOCOL,                                                        /*  7:bInterfaceProtocol */
    0,                                                                    /*  8:iInterface */

    /* Endpoint Descriptor 0 */
    USB_ED_BLENGTH,                                                       /*  0:bLength */
    USB_DT_ENDPOINT,                                                      /*  1:bDescriptorType */
    (uint8_t) (USB_EP_OUT | USB_EP1),                                     /*  2:bEndpointAddress */
    USB_EP_BULK,                                                          /*  3:bmAttribute */
    USB_W_MAX_PACKET_SIZE_MASK,                                           /*  4:wMaxPacketSize_lo */
    0,                                                                    /*  5:wMaxPacketSize_hi */
    0,                                                                    /*  6:bInterval */
};

uint8_t g_device_framework_hi_speed[] = {

    /* Device descriptor */
    USB_DD_BLENGTH,                                                       /*  0:bLength */
    USB_DT_DEVICE,                                                        /*  1:bDescriptorType */
    (uint8_t) (USB_BCDNUM & (uint8_t) USB_UCHAR_MAX),                     /*  2:bcdUSB_lo */
    (uint8_t) ((uint8_t) (USB_BCDNUM >> 8) & (uint8_t) USB_UCHAR_MAX),    /*  3:bcdUSB_hi */
    0x00,                                                                 /*  4:bDeviceClass */
    0x00,                                                                 /*  5:bDeviceSubClass */
    0x00,                                                                 /*  6:bDeviceProtocol */
    (uint8_t) USB_DCPMAXP,                                                /*  7:bMAXPacketSize(for DCP) */
    (uint8_t) (USB_VENDORID & (uint8_t) USB_UCHAR_MAX),                   /*  8:idVendor_lo */
    (uint8_t) ((uint8_t) (USB_VENDORID >> 8) & (uint8_t) USB_UCHAR_MAX),  /*  9:idVendor_hi */
    (uint8_t) (USB_PRODUCTID & (uint8_t) USB_UCHAR_MAX),                  /* 10:idProduct_lo */
    (uint8_t) ((uint8_t) (USB_PRODUCTID >> 8) & (uint8_t) USB_UCHAR_MAX), /* 11:idProduct_hi */
    (uint8_t) (USB_RELEASE & (uint8_t) USB_UCHAR_MAX),                    /* 12:bcdDevice_lo */
    (uint8_t) ((uint8_t) (USB_RELEASE >> 8) & (uint8_t) USB_UCHAR_MAX),   /* 13:bcdDevice_hi */
    1,                                                                    /* 14:iManufacturer */
    2,                                                                    /* 15:iProduct */
    3,                                                                    /* 16:iSerialNumber */
    USB_CONFIGNUM,                                                        /* 17:bNumConfigurations */

    /* Device qualifier descriptor */
    USB_PPRN_QD_LEN,                                                      /*  0:bLength */
    USB_DT_DEVICE_QUALIFIER,                                              /*  1:bDescriptorType */
    (USB_BCDNUM & (uint8_t) USB_UCHAR_MAX),                               /*  2:bcdUSB_lo */
    ((uint8_t) (USB_BCDNUM >> 8) & (uint8_t) USB_UCHAR_MAX),              /*  3:bcdUSB_hi */
    0,                                                                    /*  4:bDeviceClass */
    0,                                                                    /*  5:bDeviceSubClass */
    0,                                                                    /*  6:bDeviceProtocol */
    (uint8_t) USB_DCPMAXP,                                                /*  7:bMAXPacketSize(for DCP) */
    USB_CONFIGNUM,                                                        /*  8:bNumConfigurations */
    0,                                                                    /*  9:bReserved */

    /* Configuration Descriptor */
    USB_CD_BLENGTH,                                                       /*  0:bLength */
#ifdef HIGH_SPEED_CONFIG
    USB_DT_CONFIGURATION,                                                 /*  1:bDescriptorType */ /* For High-speed */
#else
    USB_DT_OTHER_SPEED_CONF,                                              /*  1:bDescriptorType */ /* For Full-speed */
#endif
    (uint8_t) (CD_LEN % USB_W_TOTAL_LENGTH_MASK),                         /*  2:wTotalLength(L) */
    (uint8_t) (CD_LEN / USB_W_TOTAL_LENGTH_MASK),                         /*  3:wTotalLength(H) */
    1,                                                                    /*  4:bNumInterfaces */
    1,                                                                    /*  5:bConfigurationValue */
    0,                                                                    /*  6:iConfiguration */
    (uint8_t) (USB_CF_RESERVED | USB_CF_SELFP),                           /*  7:bmAttributes */
    (uint8_t) (10 / 2),                                                   /*  8:bMaxPower (2mA unit) */

    /* Interface Descriptor */
    USB_ID_BLENGTH,                                                       /*  0:bLength */
    USB_DT_INTERFACE,                                                     /*  1:bDescriptor */
    0,                                                                    /*  2:bInterfaceNumber */
    0,                                                                    /*  3:bAlternateSetting */
    (DEMO_PROTOCOL > 1) ? 2 : 1,                                          /*  4:bNumEndpoints */
    USB_IFCLS_PRN,                                                        /*  5:bInterfaceClass(Printer) */
    0x01,                                                                 /*  6:bInterfaceSubClass */
    DEMO_PROTOCOL,                                                        /*  7:bInterfaceProtocol */
    0,                                                                    /*  8:iInterface */

    /* Endpoint Descriptor 0 */
    USB_ED_BLENGTH,                                                       /*  0:bLength */
    USB_DT_ENDPOINT,                                                      /*  1:bDescriptorType */
    (uint8_t) (USB_EP_OUT | USB_EP1),                                     /*  2:bEndpointAddress */
    USB_EP_BULK,                                                          /*  3:bmAttribute */
    0x00,                                                                 /*  4:wMaxPacketSize_lo */
    0x02,                                                                 /*  5:wMaxPacketSize_hi */
    0,                                                                    /*  6:bInterval */
};

/* String Device Framework :
   Byte 0 and 1 : Word containing the language ID : 0x0904 for US
   Byte 2       : Byte containing the index of the descriptor
   Byte 3       : Byte containing the length of the descriptor string
*/
uint8_t g_string_framework[] = {

    /* Manufacturer string descriptor : Index 1 */
    0x09, 0x04, 0x01, 14,
    'A',
    'z',
    'u',
    'r',
    'e',
    ' ',
    'R',
    'T',
    'O',
    'S',
    'U',
    'S',
    'B',
    'X',

    /* Product string descriptor : Index 2 */
    0x09, 0x04, 0x02, 12,
    'P',
    'r',
    'i',
    'n',
    't',
    'e',
    'r',
    ' ',
    'D',
    'e',
    'm',
    'o',

    /* Serial Number string descriptor : Index 3 */
    0x09, 0x04, 0x03, 15,
    '0',
    '0',
    '0',
    '0',
    '0',
    '0',
    '0',
    '0',
    '0',
    '0',
    '0',
    '0',
    '0',
    '0',
    '1',
};

/* Multiple languages are supported on the device, to add
   a language besides english, the unicode language code must
   be appended to the language_id_framework array and the length
   adjusted accordingly. */
uint8_t g_language_id_framework[] =
{
    /* English. */
    0x09,
    0x04
};

/* Device printer device ID.  */
uint8_t printer_device_id[] =
{
    "  "                                /* Will be replaced by length (big endian)  */
    "MFG:Generic;"                      /*   manufacturer (case sensitive)          */
    "MDL:Generic_/_Text_Only;"          /*   model (case sensitive)                 */
    "CMD:1284.4;"                       /*   PDL command set                        */
    "CLS:PRINTER;"                      /*   class                                  */
    "DES:Generic text only printer;"    /*   description                            */
};

/*******************************************************************************************************************//**
 * @} (end addtogroup usbx_pprn_ep)
 **********************************************************************************************************************/

/******************************************************************************
 End  Of File
 ******************************************************************************/
