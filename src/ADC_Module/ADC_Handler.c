/*
 * ADC_Handler.c
 *
 *  Created on: 26 Apr 2024
 *      Author: Ng Hong Xi
 */
#include <ADC_Framework/ADC_Periodic_Framework_Stack.h>
#include "ADC_Handler.h"
#include "Initialization.h"



fsp_err_t ADC_Open(adc_instance_t const * g_adc_instance)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_ADC_Open(g_adc_instance->p_ctrl, g_adc_instance->p_cfg);
    if (err != FSP_SUCCESS)
    {
        APP_PRINTF("ADC Open failed\n");
        return err;
    }
    return err;
}

fsp_err_t ADC_ScanCfg(adc_instance_t const * g_adc_instance)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_ADC_ScanCfg(g_adc_instance->p_ctrl, g_adc_instance->p_channel_cfg);
    if (err != FSP_SUCCESS)
    {
        APP_PRINTF("ADC Scan failed\n");
        return err;
    }
    return err;
}

fsp_err_t ADC_Read(adc_instance_t const * g_adc_instance, adc_channel_t const adc_channel, uint16_t * data_buffer_address)
{
    fsp_err_t err = FSP_SUCCESS;
    err =R_ADC_Read(g_adc_instance->p_ctrl, adc_channel, data_buffer_address);
    if (err != FSP_SUCCESS)
    {
        APP_PRINTF("Read Get failed\n");
        return err;
    }
    return err;
}

//================================================================================================================================
fsp_err_t ADC_Calibrate(adc_instance_t const * g_adc_instance, adc_status_t * g_adc_status)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_ADC_Calibrate(g_adc_instance->p_ctrl, NULL);

    do
    {
        err = R_ADC_StatusGet(g_adc_instance->p_ctrl, g_adc_status);
        if (err != FSP_SUCCESS)
        {
            APP_PRINTF("Status Get failed\n");
            return err;
        }


    }
    while(ADC_STATE_IDLE != g_adc_status->state);
    APP_PRINTF("\r\nADC Calibration Successful..\r\n");
    return err;
}










