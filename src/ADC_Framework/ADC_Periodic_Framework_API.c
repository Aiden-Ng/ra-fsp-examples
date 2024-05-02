/*
 * ADC_Periodic_Framework_API.c
 *
 *  Created on: 2 May 2024
 *      Author: Ng Hong Xi
 */

#include <ADC_Framework/ADC_Periodic_Framework_API.h>
#include <ADC_Framework/ADC_Periodic_Framework_Stack.h>


fsp_err_t ADC_PERIODIC_SCAN(sf_adc_period_t * g_sf_adc_period_ptr, adc_instance_t const * g_adc_instance, adc_channel_t channel)
{
    fsp_err_t err = FSP_SUCCESS;
    for (uint32_t i =0; i < g_sf_adc_period_ptr->p_cfg->sample_count; i++)
    {
        err = R_ADC_Read(g_adc_instance->p_ctrl, channel, g_sf_adc_period_ptr->p_cfg->p_data_buffer + i);
        //check for buffer overflow
        if (err != FSP_SUCCESS || g_sf_adc_period_ptr->p_cfg->data_buffer_length >= g_sf_adc_period_ptr->p_cfg->sample_count)
        {
            if (err != FSP_SUCCESS) APP_PRINTF("R_ADC_Read failed for i = %lu\n", i);
            else if (g_sf_adc_period_ptr->p_cfg->data_buffer_length >= g_sf_adc_period_ptr->p_cfg->sample_count) APP_PRINTF("Buffer overflow\n");
            return err;

        }
        APP_PRINTF("The value of the adc_volt is = %lu\n", *(g_sf_adc_period_ptr->p_cfg->p_data_buffer + i));
        //data[i] = *(g_sf_adc_period_ptr->p_cfg->p_data_buffer + i);
    }
    //buffer_is_full = true;
    return err;


}
