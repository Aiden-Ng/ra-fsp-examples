/*
 * LPM_handler.c
 *
 *  Created on: 3 May 2024
 *      Author: Ng Hong Xi
 */

#include "LPM_handler.h"

//create a pointer for the addresses of the differnet power mode
lpm_instance_t const * g_lpm_instance_t[APP_LPM_MAX_STATE] = { [APP_LPM_SLEEP_STATE] = &g_lpm_sleep,
                                                               [APP_LPM_SW_STANDBY_STATE] = &g_lpm_sw_standby};

fsp_err_t LPM_Open(lpm_instance_t const * g_lpm_instance)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_LPM_Open(g_lpm_instance->p_ctrl, g_lpm_instance->p_cfg);
    if (err != FSP_SUCCESS)
    {
        APP_PRINTF("LPM Open failed\n");
        return err;
    }
    return err;
}

fsp_err_t LPM_Reconfigure(lpm_instance_t const * g_lpm_instance)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_LPM_LowPowerReconfigure(g_lpm_instance->p_ctrl, g_lpm_instance->p_cfg);
    if (err != FSP_SUCCESS)
    {
        APP_PRINTF("LPM Enter failed \n");
        return err;
    }
    return err;
}

fsp_err_t LPM_Enter(lpm_instance_t const * g_lpm_instance)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_LPM_LowPowerModeEnter(g_lpm_instance->p_ctrl);
    if (err != FSP_SUCCESS)
    {
        APP_PRINTF("LPM Enter failed \n");
        return err;
    }
    return err;
}

fsp_err_t LPM_Close(lpm_instance_t const * g_lpm_instance)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_LPM_Close(g_lpm_instance->p_ctrl);
    if (err != FSP_SUCCESS)
    {
        APP_PRINTF("LPM Close failed\n");
        return err;
    }
    return err;
}
