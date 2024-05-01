/*
 * Initialization.h
 *
 *  Created on: 26 Apr 2024
 *      Author: Ng Hong Xi
 */

#ifndef INITIALIZATION_H_
#define INITIALIZATION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_data.h"
#include "SEGGER_RTT/SEGGER_RTT.h"
//#include "fsp_common_api.h"

#define RESET_VALUE 0X00


#define SEGGER_RTT_PRINT_MODULE 1

#if SEGGER_RTT_PRINT_MODULE
#define SEGGER_BUFFER_INDEX 0
#define APP_PRINTF(syntax_format, ...) SEGGER_RTT_printf(SEGGER_BUFFER_INDEX, syntax_format, ##__VA_ARGS__)




#endif

#endif /* INITIALIZATION_H_ */
