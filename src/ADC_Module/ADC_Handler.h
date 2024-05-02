/*
 * ADC_Handler.h
 *
 *  Created on: 26 Apr 2024
 *      Author: Ng Hong Xi
 */

#ifndef ADC_MODULE_ADC_HANDLER_H_
#define ADC_MODULE_ADC_HANDLER_H_

#include "Initialization.h"


fsp_err_t ADC_Open(adc_instance_t const * g_adc_instance);
fsp_err_t ADC_ScanCfg(adc_instance_t const * g_adc_instance);
fsp_err_t ADC_Calibrate(adc_instance_t const * g_adc_instance, adc_status_t * g_adc_status);
fsp_err_t ADC_Read(adc_instance_t const * g_adc_instance, adc_channel_t const adc_channel, uint16_t * data_buffer_address);


#endif /* ADC_MODULE_ADC_HANDLER_H_ */
