/*
 * lp_entry.c
 *s
 *  Created on: 3 May 2024
 *      Author: Ng Hong Xi
 */

#include "lpm_entry.h"

#define IRQ_MODULE  1
#define LPM_MODULE  1
#define GPIO_MODULE 0
#define SLEEP 0
#define STANDBY 0


#if LPM_MODULE
//this is to enable access to this power array
extern lpm_instance_t const * g_lpm_instance_t[APP_LPM_MAX_STATE];
lpm_state_t lpm_state = APP_LPM_SLEEP_STATE;
#endif

#if GPIO_MODULE
bsp_io_level_t readLevel;

#endif

fsp_err_t err = FSP_SUCCESS;

#define REG (0xA502u) //write PCRC protet control register, remember to write a5 to the upper first 8 bit

void lpm_entry(void)
{

    SEGGER_RTT_Init();
    APP_PRINTF("LPM entry entered\n");

#if GPIO_MODULE

    err = R_IOPORT_Open(g_ioport.p_ctrl, g_ioport.p_cfg);
    err = R_IOPORT_PinCfg(g_ioport.p_ctrl, BSP_IO_PORT_02_PIN_06, BSP_IO_DIRECTION_INPUT);

#endif

#if IRQ_MODULE
    err = R_ICU_ExternalIrqOpen(g_external_irq0.p_ctrl, g_external_irq0.p_cfg);
    err = R_ICU_ExternalIrqEnable(g_external_irq0.p_ctrl);
#endif

    err = LPM_Open(g_lpm_instance_t[lpm_state]);
    err = LPM_Reconfigure(g_lpm_instance_t[lpm_state]);

    while(1)
    {

#if GPIO_MODULE
        err = R_IOPORT_PinRead(g_ioport.p_ctrl, BSP_IO_PORT_02_PIN_06, &readLevel);
#endif
        //lpm_operation(&lpm_state);
#if IRQ_MODULE
        R_BSP_SoftwareDelay(3, BSP_DELAY_UNITS_SECONDS);
        lpm_operation(&lpm_state);
#endif
    }


}
void lpm_operation(lpm_state_t * lpm_state_args_ptr)
{
    err = LPM_Open(g_lpm_instance_t[*lpm_state_args_ptr]);
    err = LPM_Reconfigure(g_lpm_instance_t[*lpm_state_args_ptr]);
    err = LPM_Enter(g_lpm_instance_t[*lpm_state_args_ptr]);

    //prevent state overflow
    *lpm_state_args_ptr %= APP_LPM_MAX_STATE;

#if SLEEP
    //APP_PRINTF("SSBY value = %lu\n",R_SYSTEM->SBYCR_b.SSBY);
    err = LPM_Open(g_lpm_instance_t[APP_LPM_SLEEP_STATE]);
    err = LPM_Reconfigure(g_lpm_instance_t[APP_LPM_SLEEP_STATE]);
    APP_PRINTF("Entering LPM\n");
    err = LPM_Enter(g_lpm_instance_t[APP_LPM_SLEEP_STATE]);
#endif

#if STANDBY
    err = LPM_Open(g_lpm_instance_t[APP_LPM_SW_STANDBY_STATE]);
    err = LPM_Reconfigure(g_lpm_instance_t[APP_LPM_SW_STANDBY_STATE]);
    APP_PRINTF("Entering LPM\n");
    err = LPM_Enter(g_lpm_instance_t[APP_LPM_SW_STANDBY_STATE]);

#endif

}

#if IRQ_MODULE
void external_irq0_callback(external_irq_callback_args_t *p_args)
{
    err = LPM_Close(g_lpm_instance_t[lpm_state]);
    lpm_state++;
#if SLEEP
        err = LPM_Close(g_lpm_instance_t[APP_LPM_SLEEP_STATE]);
#endif

#if STANDBY
        err = LPM_Close(g_lpm_instance_t[APP_LPM_SW_STANDBY_STATE]);
#endif




}
#endif


