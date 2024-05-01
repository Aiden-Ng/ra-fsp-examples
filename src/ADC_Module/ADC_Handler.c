/*
 * ADC_Handler.c
 *
 *  Created on: 26 Apr 2024
 *      Author: Ng Hong Xi
 */
#include "ADC_Handler.h"
#include "Initialization.h"
#include "ADC_Framework_Stack/ADC_Periodic_Framework_Stack.h"

//void adc_start_calibration(sf_adc_periodic_cfg_t * g_sf_adc_periodic0_cfg)
//
//{
//    fsp_err_t err = FSP_SUCCESS;
//    err = R_ADC_Calibrate(g_adc0.p_ctrl, NULL);
//
//    do
//    {
//        err = R_ADC_StatusGet(g_adc0.p_ctrl, &adc0_status);
//        if (err != FSP_SUCCESS)
//        {
//            APP_PRINTF("Status Get failed\n");
//        }
//
//
//    }
//    while(ADC_STATE_IDLE != adc0_status.state);
//    APP_PRINTF("\r\nADC Calibration Successful..\r\n");
//}
