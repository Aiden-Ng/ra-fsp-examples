/***********************************************************************************************************************
 * File Name    : app_definitions.h
 * Description  : Contains macros specific to this application
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/
#ifndef APP_DEFINITIONS_H_
#define APP_DEFINITIONS_H_

#include <stdint.h>
/* SEGGER RTT and error related headers */
#include "SEGGER_RTT/SEGGER_RTT.h"
#include "common_utils.h"

#define _unused(x) ((void)(x))


#define CRYPTO_OPERATION_WITH_INITIAL_WRAPPED_KEY_SUCCESS " \r\nResult: Cryptographic operation is successful with initial wrapped AES 128 key\r\n\r\n"
#define WRAP_KUK_SUCCESS " \r\nResult: KUK Wrapping is successful \r\n\r\n"
#define UPDATE_KEY_WRAP_SUCCESS " \r\nResult: AES 128 Update Key Wrap is successful\r\n\r\n"


#define CRYPTO_OPERATION_WITH_INITIAL_WRAPPED_KEY_FAILED " \r\nResult: Cryptographic operation failed with initial wrapped AES 128 key\r\n\r\n"
#define WRAP_KUK_FAILED " \r\nResult: KUK Wrapping failed \r\n\r\n"
#define UPDATE_KEY_WRAP_FAILED " \r\nResult: AES 128 Update Key Wrap failed\r\n\r\n"


#define INITIAL_KEY_WRAP_SUCCESS  " \r\nResult: Initial AES 128 Key Wrap is successful\r\n\r\n"
#define INITIAL_KEY_WRAP_FAILED  " \r\nResult: Initial AES 128 Key Wrap failed\r\n\r\n"

#define CRYPTO_OPERATION_WITH_UPDATED_WRAPPED_KEY_SUCCESS  " \r\nResult: Cryptographic operation is successful with updated wrapped AES 128 key\r\n\r\n"
#define CRYPTO_OPERATION_WITH_UPDATED_WRAPPED_KEY_FAILED  " \r\nResult: Cryptographic operation failed with updated wrapped AES 128 key\r\n\r\n"

#endif /* APP_DEFINITIONS_H_ */
