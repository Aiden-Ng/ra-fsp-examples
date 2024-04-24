/*
 * icu_ep.c
 *
 *  Created on: 24 Apr 2024
 *      Author: Ng Hong Xi
 */
#include "icu_ep.h"
#include "IRQ_Handler.h"
#include "common_utils.h"



char SEGGER_STR_BUFFER[DEBUG_STR_SIZE] = {0};
//char debug_str[DEBUG_STR_SIZE] = "johnson_control";
//do i need to extern the instance

extern int x;

void icu_ep_entry(void)
{
    //init the SEGGER_MODULE
    SEGGER_RTT_Init();
    SEGGER_RTT_ConfigDownBuffer(SEGGER_BUFFER_INDEX, "BUFFER_1", NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);

    IRQ_Open();
    IRQ_Enable();

    while (1)
    {

        APP_PRINTF("This is the value x = %d\n", x);
        //SEGGER_RTT_printf(SEGGER_BUFFER_INDEX,"Hello\n");

    }
}

void icu_init(void)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_ICU_ExternalIrqOpen(g_external_irq0.p_ctrl, g_external_irq0.p_cfg);
    if (err != FSP_SUCCESS)
    {
        return;
    }
}




