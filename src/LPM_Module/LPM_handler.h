/*
 * LPM_handler.h
 *
 *  Created on: 3 May 2024
 *      Author: Ng Hong Xi
 */


#ifndef LPM_MODULE_LPM_HANDLER_H_
#define LPM_MODULE_LPM_HANDLER_H_

#include "Initialization.h"

typedef enum lpm_state_t
{
    APP_LPM_SLEEP_STATE = 0,
    APP_LPM_SW_STANDBY_STATE,
    APP_LPM_MAX_STATE
}lpm_state_t;

fsp_err_t LPM_Open(lpm_instance_t const * g_lpm_instance);
fsp_err_t LPM_Reconfigure(lpm_instance_t const * g_lpm_instance);
fsp_err_t LPM_Enter(lpm_instance_t const * g_lpm_instance);
fsp_err_t LPM_Close(lpm_instance_t const * g_lpm_instance);

#endif /* LPM_MODULE_LPM_HANDLER_H_ */
