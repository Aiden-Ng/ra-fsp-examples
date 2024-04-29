/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#ifdef __cplusplus
        extern "C" {
        #endif
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (2)
#endif
/* ISR prototypes */
void adc_scan_end_isr(void);
void adc_window_compare_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_ADC0_SCAN_END ((IRQn_Type) 0) /* ADC0 SCAN END (End of A/D scanning operation) */
#define ADC0_SCAN_END_IRQn          ((IRQn_Type) 0) /* ADC0 SCAN END (End of A/D scanning operation) */
#define VECTOR_NUMBER_ADC0_WINDOW_A ((IRQn_Type) 1) /* ADC0 WINDOW A (Window A Compare match interrupt) */
#define ADC0_WINDOW_A_IRQn          ((IRQn_Type) 1) /* ADC0 WINDOW A (Window A Compare match interrupt) */
#ifdef __cplusplus
        }
        #endif
#endif /* VECTOR_DATA_H */
