/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = adc_scan_end_isr, /* ADC0 SCAN END (End of A/D scanning operation) */
            [1] = adc_window_compare_isr, /* ADC0 WINDOW A (Window A Compare match interrupt) */
            [2] = gpt_counter_overflow_isr, /* GPT1 COUNTER OVERFLOW (Overflow) */
            [3] = gpt_counter_overflow_isr, /* GPT2 COUNTER OVERFLOW (Overflow) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_ADC0_SCAN_END,GROUP0), /* ADC0 SCAN END (End of A/D scanning operation) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_ADC0_WINDOW_A,GROUP1), /* ADC0 WINDOW A (Window A Compare match interrupt) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_GPT1_COUNTER_OVERFLOW,GROUP2), /* GPT1 COUNTER OVERFLOW (Overflow) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_GPT2_COUNTER_OVERFLOW,GROUP3), /* GPT2 COUNTER OVERFLOW (Overflow) */
        };
        #endif
        #endif
