/*
 * ADC_Periodic_Framework_API.h
 *
 *  Created on: 2 May 2024
 *      Author: Ng Hong Xi
 */

#ifndef ADC_FRAMEWORK_ADC_PERIODIC_FRAMEWORK_API_H_
#define ADC_FRAMEWORK_ADC_PERIODIC_FRAMEWORK_API_H_

#include "Initialization.h"

fsp_err_t ADC_PERIODIC_SCAN(sf_adc_period_t * g_sf_adc_period_ptr, adc_instance_t const * g_adc_instance, adc_channel_t channel);

#endif /* ADC_FRAMEWORK_ADC_PERIODIC_FRAMEWORK_API_H_ */
