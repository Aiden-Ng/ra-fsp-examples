/*
 * Initialization.h
 *
 *  Created on: 3 May 2024
 *      Author: Ng Hong Xi
 */

#ifndef INITIALIZATION_H_
#define INITIALIZATION_H_

#include <stdio.h>
#include <stdlib.h>
//stdint is included inside the hal_data

//bsp_api is delcared inside hal_data.h
//remember to declare bsp_api before fsp_common_api
#include "hal_data.h"
#include "fsp_common_api.h"
#include "SEGGER_RTT/SEGGER_RTT.h"

//for segger rtt print
#define SEGGER_BUFFER_INDEX     0
#define APP_PRINTF(format_specifier, ...)        SEGGER_RTT_printf(SEGGER_BUFFER_INDEX, format_specifier, ##__VA_ARGS__)








#endif /* INITIALIZATION_H_ */
