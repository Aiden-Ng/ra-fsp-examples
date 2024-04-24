/*
 * IRQ_Handler.c
 *
 *  Created on: 24 Apr 2024
 *      Author: Ng Hong Xi
 */


#include "common_utils.h"
#include "IRQ_Handler.h"

int x = 0;

int IRQ_Open(void)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_ICU_ExternalIrqOpen(g_external_irq0.p_ctrl, g_external_irq0.p_cfg);
    if (err != FSP_SUCCESS)
    {
        APP_PRINTF("External Irq Open failed\n");
        return -1;

    }
    return 0;
}

int IRQ_Enable(void)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_ICU_ExternalIrqEnable(g_external_irq0.p_ctrl);
    if (err != FSP_SUCCESS)
    {
        APP_PRINTF("External Irq Enable failed\n");
        return -1;

    }
    return 0;
}

int IRQ_Disable(void)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_ICU_ExternalIrqDisable(g_external_irq0.p_ctrl);
    if (err != FSP_SUCCESS)
    {
        APP_PRINTF("External Irq Disable failed\n");
        return -1;

    }
    return 0;
}

int IRQ_Close(void)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_ICU_ExternalIrqClose(g_external_irq0.p_ctrl);
    if (err != FSP_SUCCESS)
    {
        APP_PRINTF("External Irq Close failed\n");
        return -1;

    }
    return 0;
}

void external_irq0_callback(external_irq_callback_args_t * p_args)
{
    if (p_args != NULL) APP_PRINTF("p_args is empty\n");
    else APP_PRINTF("yay\n");
    x++;
    return;

}


