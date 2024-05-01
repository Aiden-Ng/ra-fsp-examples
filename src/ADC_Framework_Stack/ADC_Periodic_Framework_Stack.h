/*
 * ADC_Periodic_Framework_Stack.h
 *
 *  Created on: 1 May 2024
 *      Author: Ng Hong Xi
 */

#ifndef ADC_FRAMEWORK_STACK_ADC_PERIODIC_FRAMEWORK_STACK_H_
#define ADC_FRAMEWORK_STACK_ADC_PERIODIC_FRAMEWORK_STACK_H_

/**
 * @brief Copied from ssp-renesas framework "ADC Periodic Framework on sf_adc_periodic"
 */

#include "Initialization.h"

typedef uint16_t adc_data_size_t;

typedef struct st_sf_adc_periodic_cfg
{
    adc_data_size_t *p_data_buffer;
    uint32_t data_buffer_length;
    uint32_t sample_count;
}sf_adc_periodic_cfg_t;

typedef struct st_sf_adc_periodic_instance
{
    sf_adc_periodic_cfg_t  * p_cfg;
}sf_adc_period_t;


#endif /* ADC_FRAMEWORK_STACK_ADC_PERIODIC_FRAMEWORK_STACK_H_ */
