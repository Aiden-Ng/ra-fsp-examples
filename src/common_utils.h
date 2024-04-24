/*
 * common_utils.h
 *
 *  Created on: 24 Apr 2024
 *      Author: Ng Hong Xi
 */

#ifndef SEGGER_RTT_COMMON_UTILS_H_
#define SEGGER_RTT_COMMON_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_data.h"
#include "SEGGER_RTT/SEGGER_RTT.h"


#define DEBUG_STR_SIZE 512u
#define SEGGER_BUFFER_INDEX 0
#define APP_PRINTF(syntax_formatter, ...) SEGGER_RTT_printf(SEGGER_BUFFER_INDEX, syntax_formatter, ##__VA_ARGS__)

#endif /* SEGGER_RTT_COMMON_UTILS_H_ */
