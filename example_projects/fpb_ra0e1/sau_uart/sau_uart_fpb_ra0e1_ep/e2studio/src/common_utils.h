/***********************************************************************************************************************
 * File Name    : common_utils.h
 * Description  : Contains macros, data structures and functions used  common to the EP
 ***********************************************************************************************************************/
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
 * Copyright (C) 2020-2024 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/

#ifndef COMMON_UTILS_H_
#define COMMON_UTILS_H_

/* generic headers */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hal_data.h"

/* SEGGER RTT and error related headers */
#include "SEGGER_RTT/SEGGER_RTT.h"


#define BIT_SHIFT_8     (8U)
#define SIZE_64         (64U)

#define LVL_ERR         (1U)       /* error conditions   */

#define RESET_VALUE     (0x00)
#define MODULE_CLOSE    (0U)

#define EP_VERSION      "1.0"
#define MODULE_NAME     "r_sau_uart"
#define BANNER_INFO     "\r\n******************************************************************"\
                        "\r\n*   Renesas FSP Example Project for "MODULE_NAME" Module            *"\
                        "\r\n*   Example Project Version %s                                  *"\
                        "\r\n*   Flex Software Pack Version  %d.%d.%d                            *"\
                        "\r\n******************************************************************"\
                        "\r\nRefer to readme.txt file for more details on Example Project and" \
                        "\r\nFSP User's Manual for more information about "MODULE_NAME" driver\r\n"

#define EP_INFO         "\r\nThe Example Project demonstrates the basic functionality of the SAU UART driver on"\
                        "\r\nRenesas RA MCUs based on FSP. Upon successfully initializing the SAU UART module,"\
                        "\r\na message requesting the user to open the Tera Term application on the PC along"\
                        "\r\nwith the configuration parameters for the Tera Term application will be displayed on"\
                        "\r\nthe RTT Viewer. After opening and configuring the Tera Term application, the user can"\
                        "\r\nenter any ASCII character string with a length less than 256 characters into the Tera Term"\
                        "\r\napplication, then press enter-key to send it to the RA board. The RA Board will echo"\
                        "\r\nany data received back to the Tera Term application on the host PC.\r\n"

#define EP_MESSAGE      "\r\nPlease open the Tera Term application on the PC and set up the serial connection to:"\
                        "\r\nThe COM port is facilitated by the PmodUSBUART, operating at a baud rate of 115200 bps,"\
                        "\r\nwith a data length of 8 bits, no parity check, one-bit stop, and without any flow control.\r\n\r\n"

#define SEGGER_INDEX            (0U)

#define APP_PRINT(fn_, ...)     (SEGGER_RTT_printf (SEGGER_INDEX,(fn_), ##__VA_ARGS__))

#define APP_ERR_PRINT(fn_, ...) ({\
    if(LVL_ERR)\
    {\
        SEGGER_RTT_printf (SEGGER_INDEX, "[ERR] In Function: %s(), %s", __FUNCTION__, (fn_), ##__VA_ARGS__);\
    }\
})

#define APP_ERR_RETURN(err, fn_, ...)   ({\
    if(err){\
        APP_ERR_PRINT((fn_), ##__VA_ARGS__);\
        return (err);\
    }\
})

#define APP_ERR_TRAP(err)  ({\
    if(err) {\
        SEGGER_RTT_printf(SEGGER_INDEX, "\r\nReturned Error Code: 0x%x  \r\n", (err));\
        __asm("BKPT #0\n");\
    }\
})

#define APP_READ(buf)           (SEGGER_RTT_Read (SEGGER_INDEX, (buf), BUFFER_SIZE_DOWN))

#define APP_CHECK_DATA          (SEGGER_RTT_HasKey())

#endif /* COMMON_UTILS_H_ */
