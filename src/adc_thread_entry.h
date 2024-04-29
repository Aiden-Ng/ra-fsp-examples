/*
 * adc_thread_entry.h
 *
 *  Created on: 29 Apr 2024
 *      Author: Ng Hong Xi
 */

#ifndef ADC_THREAD_ENTRY_H_
#define ADC_THREAD_ENTRY_H_
void adc_thread_entry(void);

typedef uint16_t adc_data_size_t;

typedef struct st_sf_adc_periodic_instance g_sf_adc0_period_t;
typedef struct st_sf_adc_periodic_cfg sf_adc_periodic_cfg_t;

typedef struct st_sf_adc_periodic_instance
{
    sf_adc_periodic_cfg_t * p_cfg;
}g_sf_adc0_period_t;

typedef struct st_sf_adc_periodic_cfg
{
    adc_data_size_t *p_data_buffer;
    uint32_t data_buffer_length;
    uint32_t sample_count;
}sf_adc_periodic_cfg_t;




#endif /* ADC_THREAD_ENTRY_H_ */
