/*
 * GPT_Timer_Handler.c
 *
 *  Created on: 1 May 2024
 *      Author: Ng Hong Xi
 */
#include "Initialization.h"
#include "GPT_Handler.h"

/**
 * @brief This Module encapsule necessaries API that we require
 * @details
 * Dependenceis
 * This module depends on the "fsp_common_api.h" from Initialization.h for the return type
 * This module uses "SEGGER_RTT.h" library to print the status
 *
 *
 * */

fsp_err_t Timer_Open(timer_instance_t const * g_timer_instance)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_GPT_Open(g_timer_instance->p_ctrl,g_timer_instance->p_cfg);
    if ( err != FSP_SUCCESS)
    {
        APP_PRINTF("GPT_Open failed\n");
        return err;
    }

    return err;
}

fsp_err_t Timer_Enable(timer_instance_t const * g_timer_instance)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_GPT_Enable(g_timer_instance->p_ctrl);
    if ( err != FSP_SUCCESS)
    {
        APP_PRINTF("GPT_Enable failed\n");
        return err;
    }
    return err;
}

fsp_err_t Timer_Start(timer_instance_t const * g_timer_instance)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_GPT_Start(g_timer_instance->p_ctrl);
    if ( err != FSP_SUCCESS)
    {
        APP_PRINTF("GPT_Enable failed\n");
        return err;
    }
    return err;
}

fsp_err_t Timer_Reset(timer_instance_t const * g_timer_instance)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_GPT_Reset(g_timer_instance->p_ctrl);
    if ( err != FSP_SUCCESS)
    {
        APP_PRINTF("GPT_Enable failed\n");
        return err;
    }
    return err;
}

fsp_err_t Timer_Disable(timer_instance_t const * g_timer_instance)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_GPT_Disable(g_timer_instance->p_ctrl);
    if ( err != FSP_SUCCESS)
    {
        APP_PRINTF("GPT_Enable failed\n");
        return err;
    }
    return err;
}

fsp_err_t Timer_Close(timer_instance_t const * g_timer_instance)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_GPT_Close(g_timer_instance->p_ctrl);
    if ( err != FSP_SUCCESS)
    {
        APP_PRINTF("GPT_Open failed\n");
        return err;
    }
    return err;
}

fsp_err_t Timer_InfoGet(timer_instance_t const * g_timer_instance, timer_info_t * g_timer_info)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_GPT_InfoGet(g_timer_instance->p_ctrl, g_timer_info);
    if ( err != FSP_SUCCESS)
    {
        APP_PRINTF("GPT_Open failed\n");
        return err;
    }
    return err;

}

fsp_err_t Timer_StatusGet(timer_instance_t const * g_timer_instance, timer_status_t * g_timer_status)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_GPT_StatusGet(g_timer_instance->p_ctrl, g_timer_status);
    if ( err != FSP_SUCCESS)
    {
        APP_PRINTF("GPT_Open failed\n");
        return err;
    }
    return err;
}

fsp_err_t Timer_CallbackSet(timer_instance_t const * g_timer_instance,
                            void (                      * p_callback)(timer_callback_args_t *),
                            void const * const            p_context,
                            timer_callback_args_t * const p_callback_memory)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_GPT_CallbackSet(g_timer_instance->p_ctrl,p_callback, p_context, p_callback_memory);
    if ( err != FSP_SUCCESS)
    {
        APP_PRINTF("GPT_Open failed\n");
        return err;
    }
    return err;

}


