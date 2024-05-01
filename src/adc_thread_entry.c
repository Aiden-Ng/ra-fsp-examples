#include "hal_data.h"
#include "Initialization.h"
#include "adc_thread_entry.h"
#include "ADC_Module/ADC_Handler.h"
#include "IRQ_Module/IRQ_Handler.h"

//extended stack for adc framework
#define ADC_MODULE          1//Note that ADC_MODULE and ADC_FRAMEWORK must be activated together
#define ADC_FRAMEWORK       1
#define GPT_MODULE          1
#define IRQ_MODULE          0
#define GPT_IN_ADC_MODULE   0
#define GPT1_MODULE         1
#define NORMAL_CODE         0
#define LED_PIN             1

//======================================================================================================
#if ADC_MODULE
void adc_start_calibration(void);
void adc_start_scan(void);
void adc_read_value(void);
void adc_periodic_read_scan(g_sf_adc0_period_t * g_sf_adc0_period_t_ptr);

#define ADC_16_BIT                      32768u
#define V_ref                           3.3f
#define ADC_READ_DELAY                  2
#define VREFADCG_VALUE                  0x03
#define VREFADCG_ENABLE                 0x03
#define SHIFT_BY_ONE                    0x01
#define SHIFT_BY_THREE                  0x03

char adc_str[128] = {0};
uint16_t raw_adc_digital_data = 0;
adc_status_t adc0_status = {.state = ADC_STATE_IDLE}; //to store the adc status //please put it together with the R_ADC_StatusGet
bool adc_call_status = false; //forgot ady
#endif

#if ADC_FRAMEWORK
//create a adc0 framework object
//#define ADC_PERIODIC_BUFFER_SIZE (4096u)
#define ADC_PERIODIC_BUFFER_SIZE (4096u)
//ignore
#define ADC_PERIODIC_NUMBER_SAMPING_ITERATION 4000

uint16_t buffer_array_index =0;
uint16_t data[ADC_PERIODIC_BUFFER_SIZE] = {0};
uint16_t p_buffer[ADC_PERIODIC_BUFFER_SIZE] = {0};
adc_data_size_t buffer_array[ADC_PERIODIC_BUFFER_SIZE] = {0};
sf_adc_periodic_cfg_t g_sf_adc_periodic0_cfg = {.p_data_buffer = p_buffer,
                                                .data_buffer_length = ADC_PERIODIC_BUFFER_SIZE,
                                                .sample_count = ADC_PERIODIC_NUMBER_SAMPING_ITERATION};

g_sf_adc0_period_t g_sf_adc_periodic0 = {.p_cfg = &g_sf_adc_periodic0_cfg};
//check if the buffer is full for adc (condition to leave)
bool buffer_is_full = false;

#endif

//======================================================================================================

#if GPT_MODULE
void timer0_Init(void);
void timer0_Start(void);
void timer0_InfoGet(void);
void timer0_StatusGet(void);
void timer0_callback(timer_callback_args_t *p_args);

//initialization
uint32_t timer0_count = 0;

timer_info_t g_timer0_info = {0};
timer_status_t g_timer0_status = {0};
bool timer0_is_full = false;
#endif

//======================================================================================================
#if GPT_IN_ADC_MODULE

#define ADC_SAMPLING_RATE 4000
uint16_t adc_read_count = 0;

#endif

//======================================================================================================
#if GPT1_MODULE

void timer1_callback(timer_callback_args_t *p_args);
uint32_t timer1_counter = 0;
timer_info_t g_timer1_info = {0};
timer_status_t g_timer1_status = {0};
bool timer1_is_full = false;

#endif
//======================================================================================================

#if LED_PIN
#include "r_ioport.h"
#include "bsp_pin_cfg.h"

#define IOPORT_CFG_NAME g_bsp_pin_cfg
#define IOPORT_CFG_OPEN R_IOPORT_Open
#define IOPORT_CFG_CTRL g_ioport_ctrl

/* Define the units to be used with the software delay function */
const bsp_delay_units_t bsp_delay_units = BSP_DELAY_UNITS_MILLISECONDS;

/* Set the blink frequency (must be <= bsp_delay_units */
const uint32_t freq_in_hz = 2;

/* Calculate the delay in terms of bsp_delay_units */
const uint32_t delay = bsp_delay_units / freq_in_hz;

bsp_io_level_t pin_level_low = BSP_IO_LEVEL_LOW;
bsp_io_level_t pin_level_high = BSP_IO_LEVEL_HIGH;
uint32_t pin;

#endif

fsp_err_t err = FSP_SUCCESS;


/* New Thread entry function */
void adc_thread_entry(void)
{
    SEGGER_RTT_Init();
    fsp_pack_version_t version = {RESET_VALUE};
    //get the version of the FSP
    R_FSP_VersionGet(&version);
    APP_PRINTF("The version is = %d\n",version.version_id);

#if LED_PIN

    pin = 517;
    R_BSP_PinAccessEnable();
    R_BSP_PinWrite((bsp_io_port_pin_t) pin, pin_level_low);

#endif

#if GPT_MODULE

    APP_PRINTF("Entered GPT_MODULE\n");
    //timer0_InfoGet();
    err = R_GPT_Open(g_timer0.p_ctrl, g_timer0.p_cfg);
    err = R_GPT_Enable(g_timer0.p_ctrl);
    err = R_GPT_CallbackSet(g_timer0.p_ctrl, timer0_callback, NULL, NULL);
    err = R_GPT_Start(g_timer0.p_ctrl);
    //err = R_GPT_InfoGet(g_timer0.p_ctrl, &g_timer0_info);

#endif

#if GPT1_MODULE

    err = R_GPT_Open(g_timer1.p_ctrl, g_timer1.p_cfg);
    err = R_GPT_Enable(g_timer1.p_ctrl);
    err = R_GPT_CallbackSet(g_timer1.p_ctrl, timer1_callback, NULL, NULL);


#endif

#if NORMAL_CODE
    if (timer0_is_full == true)
    {
        err = R_GPT_Reset(g_timer1.p_ctrl);
    }
    else if (timer1_is_full == true)
    {
        err = R_GPT_Reset(g_timer1.p_ctrl);
    }
#endif



#if ADC_MODULE
    adc_start_scan();
    adc_start_calibration();
    //while (1)
    //R_SYSTEM->SCKDIVCR_b.ICK = 0x00;
    FSP_PARAMETER_NOT_USED(err);
    //calibrate the adc module

    err = R_ADC_ScanStart(g_adc0.p_ctrl);
    R_BSP_IrqDisable((IRQn_Type)ADC_EVENT_SCAN_COMPLETE);

    err = R_GPT_Start(g_timer1.p_ctrl);
    //must be called after R_ADC_ScanStart because you cannot disable it

    APP_PRINTF("Scan is started\n");

    while(1)
    {

        APP_PRINTF("This is the value of the raw acd = %lu\n", *(buffer_array + buffer_array_index));

    }
    //adc_read_value();
    //adc_periodic_read_scan(&g_sf_adc_periodic0);

    if (buffer_is_full == true)
        {
            err = R_GPT_Stop(g_timer1.p_ctrl);
            APP_PRINTF("Buffer is full\n");
        }

#endif

}

#if ADC_MODULE
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
    FSP_PARAMETER_NOT_USED(err);
    err = R_ADC_Open(g_adc0.p_ctrl, g_adc0.p_cfg);
    err = R_ADC_ScanCfg(g_adc0.p_ctrl, &g_adc0_channel_cfg); //what is the purpose if you already configured it to a certain channel
    //check the vlaue
    //R_ADC0->VREFAMPCNT |= (uint8_t)00011110;
    R_ADC0->VREFAMPCNT |= ((VREFADCG_VALUE << SHIFT_BY_ONE) | (VREFADCG_ENABLE << SHIFT_BY_THREE));
}

void adc_read_value(void)
{
    FSP_PARAMETER_NOT_USED(err);

#if GPT_IN_ADC_MODULE

    err = R_GPT_Start(g_timer0.p_ctrl);


#endif

    //err = R_ADC_Read(g_adc0.p_ctrl, ADC_CHANNEL_1, &raw_adc_digital_data);

    //snprintf(adc_str, sizeof(adc_str), "%0.2f", (float)raw_adc_digital_data);
    //APP_PRINTF("The value of the adc_volt is = %s\n", adc_str);

    //R_BSP_SoftwareDelay (ADC_READ_DELAY, BSP_DELAY_UNITS_SECONDS);
    //err = R_ADC_ScanStop(g_adc.p_ctrl);
    //err = R_ADC_Close(g_adc.p_ctrl);
}
void adc_start_calibration(void)
{

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
#endif

#if GPT_MODULE
void timer0_Init(void)
{
    err = R_GPT_Open(g_timer0.p_ctrl, g_timer0.p_cfg);

    //this one can be seperated and used else where
    err = R_GPT_Enable(g_timer0.p_ctrl);
}

void timer0_Start(void)
{
    err = R_GPT_Start(g_timer0.p_ctrl);

    //set callback
    err = R_GPT_CallbackSet(g_timer0.p_ctrl, timer0_callback, NULL, NULL);
}

void timer0_InfoGet(void)
{
    err = R_GPT_InfoGet(g_timer0.p_ctrl, &g_timer0_info);
}

void timer0_StatusGet(void)
{
    err = R_GPT_StatusGet(g_timer0.p_ctrl, &g_timer0_status);
}

void timer0_callback(timer_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);

#if GPT_IN_ADC_MODULE

    err = R_ADC_Read(g_adc0.p_ctrl, ADC_CHANNEL_1, &raw_adc_digital_data);
    snprintf(adc_str, sizeof(adc_str), "%0.2f", (float)raw_adc_digital_data);
    APP_PRINTF("The value of the adc_volt is = %s\n", adc_str);
    adc_read_count++;
#endif

    timer0_count++;




}

#endif


#if GPT1_MODULE

void timer1_callback(timer_callback_args_t *p_args)
{

        FSP_PARAMETER_NOT_USED(p_args);


        //read the adc signal calibrated at 4khz
        err = R_ADC_Read(g_adc0.p_ctrl, ADC_CHANNEL_1, (buffer_array + buffer_array_index));
//        err = R_ADC_Read(g_adc0.p_ctrl, ADC_CHANNEL_1, NULL);
        buffer_array_index++;
        timer1_counter++;

        if(timer1_counter % 2 == 0)
        {
            R_BSP_PinWrite((bsp_io_port_pin_t) pin, pin_level_high);
        }
        else
        {
            R_BSP_PinWrite((bsp_io_port_pin_t) pin, pin_level_low);
        }

        buffer_array_index %= 4096;

        //This is to prevent buffer overflow
//        if (buffer_array_index >=4095)
//        {
//            err = R_ADC_ScanStop(g_adc0.p_ctrl);
//            err= R_GPT_Stop(g_timer1.p_ctrl);
//        }
}

#endif
