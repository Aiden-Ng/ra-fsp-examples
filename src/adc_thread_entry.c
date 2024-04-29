#include "Initialization.h"
#include "ADC_Module/ADC_Handler.h"
#include "IRQ_Module/IRQ_Handler.h"
#include "hal_data.h"
#include "adc_thread_entry.h"

//callback

void adc_start_calibration(void);
void adc_start_scan(void);
void adc_read_value(void);
void adc_periodic_read_scan(g_sf_adc0_period_t * g_sf_adc0_period_t_ptr);

char adc_str[128] = {0};
float adc_volt = 3;
uint16_t raw_adc_digital_data = 3;
adc_status_t adc0_status = {.state = ADC_STATE_IDLE}; //to store the adc status //please put it together with the R_ADC_StatusGet
#define ADC_16_BIT (32768u)
#define V_ref (3.3f)
#define ADC_READ_DELAY 2

#define VREFADCG_VALUE                  0x03
#define VREFADCG_ENABLE                 0x03
#define SHIFT_BY_ONE                    0x01
#define SHIFT_BY_THREE                  0x03

//extended stack for adc framework
#define ADC_FRAMEWORK 1


#if ADC_FRAMEWORK
//create a adc0 framework object
#define ADC_PERIODIC_BUFFER_SIZE (512u)
#define ADC_PERIODIC_NUMBER_SAMPING_ITERATION 256

uint16_t data[ADC_PERIODIC_BUFFER_SIZE] = {0};
uint16_t p_buffer[ADC_PERIODIC_BUFFER_SIZE] = {0};
adc_data_size_t buffer_array[ADC_PERIODIC_BUFFER_SIZE] = {0};
sf_adc_periodic_cfg_t g_sf_adc_periodic0_cfg = {.p_data_buffer = p_buffer,
                                                .data_buffer_length = ADC_PERIODIC_BUFFER_SIZE,
                                                .sample_count = ADC_PERIODIC_NUMBER_SAMPING_ITERATION};

g_sf_adc0_period_t g_sf_adc_periodic0 = {.p_cfg = &g_sf_adc_periodic0_cfg};

bool buffer_is_full = false;



#endif


/* New Thread entry function */
void adc_thread_entry(void)
{
    SEGGER_RTT_Init();
    fsp_pack_version_t version = {RESET_VALUE};
    //get the version of the FSP
    R_FSP_VersionGet(&version);
    APP_PRINTF("The version is = %d",version.version_id);
    /* TODO: add your own code here */
    adc_start_scan();
    adc_start_calibration();
    while (1)
    {
        fsp_err_t err = FSP_ERR_ASSERTION;
        FSP_PARAMETER_NOT_USED(err);
        //calibrate the adc module

        err = R_ADC_ScanStart(g_adc0.p_ctrl);
        //must be called after R_ADC_ScanStart because you cannot disable it
        R_BSP_IrqDisable((IRQn_Type)ADC_EVENT_SCAN_COMPLETE);
        adc_read_value();
        //adc_periodic_read_scan(&g_sf_adc_periodic0);
        if (buffer_is_full == true) break;

    }
    APP_PRINTF("Buffer is full\n");
}


void adc0_callback(adc_callback_args_t *p_args)
{
    if(ADC_EVENT_WINDOW_COMPARE_A == p_args->event)
    {
        //g_window_comp_event = true;
        IRQn_Type irq = R_FSP_CurrentIrqGet();
        R_BSP_IrqDisable(irq);
    }
}

void adc_start_scan(void)
{
    fsp_err_t err = FSP_SUCCESS;
    FSP_PARAMETER_NOT_USED(err);
    err = R_ADC_Open(g_adc0.p_ctrl, g_adc0.p_cfg);
    err = R_ADC_ScanCfg(g_adc0.p_ctrl, &g_adc0_channel_cfg); //what is the purpose if you already configured it to a certain channel
    //check the vlaue
    //R_ADC0->VREFAMPCNT |= (uint8_t)00011110;
    R_ADC0->VREFAMPCNT |= ((VREFADCG_VALUE << SHIFT_BY_ONE) | (VREFADCG_ENABLE << SHIFT_BY_THREE));
}

void adc_read_value(void)
{
    fsp_err_t err = FSP_SUCCESS;
    FSP_PARAMETER_NOT_USED(err);

    err = R_ADC_Read(g_adc0.p_ctrl, ADC_CHANNEL_1, &raw_adc_digital_data);
    //adc_volt = (float)((raw_adc_digital_data * V_ref)/ADC_16_BIT);
    //snprintf(adc_str, sizeof(adc_str), "%0.2f", adc_volt);
    snprintf(adc_str, sizeof(adc_str), "%0.2f", (float)raw_adc_digital_data);
    APP_PRINTF("The value of the adc_volt is = %s\n", adc_str);

    //R_BSP_SoftwareDelay (ADC_READ_DELAY, BSP_DELAY_UNITS_SECONDS);
    //err = R_ADC_ScanStop(g_adc.p_ctrl);
    //err = R_ADC_Close(g_adc.p_ctrl);
}
void adc_start_calibration(void)
{
    fsp_err_t err = FSP_SUCCESS;



    err = R_ADC_Calibrate(g_adc0.p_ctrl, NULL);

    do
    {
        err = R_ADC_StatusGet(g_adc0.p_ctrl, &adc0_status);
        if (err != FSP_SUCCESS)
        {
            APP_PRINTF("Status Get failed\n");
        }


    }
    while(ADC_STATE_IDLE != adc0_status.state);
    APP_PRINTF("\r\nADC Calibration Successful..\r\n");
}

void adc_periodic_read_scan(g_sf_adc0_period_t * g_sf_adc0_period_t_ptr)
{
    for (uint32_t i =0; i < g_sf_adc_periodic0.p_cfg->sample_count; i++)
    {
        static fsp_err_t err = FSP_SUCCESS;
        err =R_ADC_Read(g_adc0.p_ctrl, ADC_CHANNEL_1, g_sf_adc0_period_t_ptr->p_cfg->p_data_buffer + i);
        if ( err != FSP_SUCCESS)
        {
            APP_PRINTF("R_ADC_Read failed for i = %lu", i);

        }
        APP_PRINTF("The value of the adc_volt is = %lu\n", *(g_sf_adc0_period_t_ptr->p_cfg->p_data_buffer + i));

        data[i] = *(g_sf_adc0_period_t_ptr->p_cfg->p_data_buffer + i);
    }
    buffer_is_full = true;
}
