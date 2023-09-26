/***********************************************************************************************************************
 * File Name    : hal_entry.c
 * Description  : Contains functions
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2022 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
#include "common_utils.h"
#include "poeg_ep.h"

/*******************************************************************************************************************//**
 * @addtogroup poeg_ep
 * @{
 **********************************************************************************************************************/
FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
FSP_CPP_FOOTER

/* Global variable */
static volatile bool b_comparator_state_flag = false;
uint8_t g_num_bytes = RESET_VALUE;
uint16_t g_dac_val = RESET_VALUE;
comparator_info_t g_stabilize_time = {RESET_VALUE};
static volatile uint8_t g_interrupt_pin_trigger_flag = RESET_VALUE;
static volatile uint8_t g_interrupt_output_level_flag = RESET_VALUE;
static volatile uint8_t g_interrupt_acmphs_flag = RESET_VALUE;
static volatile uint8_t g_mode_flag = RESET_VALUE;


/*******************************************************************************************************************//**
 * main() is generated by the RA Configuration editor and is used to generate threads if an RTOS is used.  This function
 * is called by main() when no RTOS is used.
 **********************************************************************************************************************/

void hal_entry(void)
{
    fsp_err_t err = FSP_SUCCESS;
    fsp_pack_version_t version = {RESET_VALUE};

    /* version get API for FLEX pack information */
    R_FSP_VersionGet(&version);

    /* Example Project information printed on the Console */
    APP_PRINT(BANNER_INFO, EP_VERSION, version.version_id_b.major, version.version_id_b.minor, version.version_id_b.patch);
    APP_PRINT(EP_INFO);

    /* Initialize the POEG0 */
    err = init_poeg0_module();
    /* Handle error */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\nPOEG0 initialization for GPT output level mode failed\r\n");
        APP_ERR_TRAP(err);
    }
    else
    {
        APP_PRINT("POEG0 initialized successfully for GPT output level mode\r\n");
    }

    /* Initialize the POEG1 */
    err = init_poeg1_module();
    /* Handle error */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\nPOEG1 initialization for GTETRG pin trigger,software api and acmphs mode failed\r\n");
        APP_ERR_TRAP(err);
    }
    else
    {
        APP_PRINT("POEG1 initialized successfully for  GTETRG pin trigger,software api and acmphs mode\r\n");
    }

    /* Initialize the Timer1 in PWM mode */
    err = init_gpt_timer_pwm1();
    /* Handle error */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\nGPT1 TIMER start failed\r\n");
        /*Close PWM Timer instance */
        deinit_gpt_timer(&g_timer_pwm1_ctrl);
        APP_ERR_TRAP(err);
    }
    else
    {
        APP_PRINT("GPT1 initialized successfully for PWM mode\r\n");
    }

    /* Initialize the Timer2 in PWM mode */
    err = init_gpt_timer_pwm2();
    /* Handle error */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\nGPT2 TIMER start failed\r\n");
        deinit_gpt_timer(&g_timer_pwm2_ctrl);
        APP_ERR_TRAP(err);
    }
    else
    {
        APP_PRINT("GPT2 initialized successfully for PWM mode\r\n");
    }

    /* Initialize the Timer3 in PWM mode */
    err = init_gpt_timer_pwm3();
    /* Handle error */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\nGPT3 TIMER start failed\r\n");
        deinit_gpt_timer(&g_timer_pwm3_ctrl);
        APP_ERR_TRAP(err);
    }
    else
    {
        APP_PRINT("GPT3 initialized successfully for PWM mode\r\n");
    }

    /* Initialize the ACMPHS */
    err = enable_acmphs_mode_modules();
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\nACMPHS initialization failed\r\n");
        APP_ERR_TRAP(err);
    }
    else
    {
        APP_PRINT("ACMPHS initialized successfully\r\n");
    }

    while(true)
    {
        APP_PRINT(MENU_INFO);
        /* Process input only when User has provided one */
        while(!APP_CHECK_DATA);
        if (APP_CHECK_DATA)
        {
            poeg_ouput_disable_and_reset_options();
        }
    }
#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
}


/*******************************************************************************************************************//**
 * @brief This function reads the command(input) for RTT and processes the command for poeg output disable.
 *
 * @param[in] None
 * @retval    FSP_SUCCESS                  Upon successful
 * @retval    Any Other Error code apart from FSP_SUCCESS  Upon Unsuccessful
 **********************************************************************************************************************/
fsp_err_t poeg_ouput_disable_and_reset_options(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Variable to store user input */
    uint8_t rByte[BUFFER_SIZE_DOWN] = {NULL_CHAR};
    uint8_t converted_rtt_input = RESET_VALUE;

    APP_READ(rByte);
    /* User input selection */
    converted_rtt_input = (uint8_t)atoi((char *)rByte);

    switch (converted_rtt_input)
    {
        /* POEG_TRIGGER_ON_GTETRG_INPUT_PIN_LEVEL - Disables GPT output pins based
         * on GTETRG input pin level */
        case POEG_TRIGGER_ON_GTETRG_INPUT_PIN_LEVEL :
        {
            /* Start PWM Timer*/
            err = R_GPT_Start(&g_timer_pwm3_ctrl);
            /* Handle error */
            if (FSP_SUCCESS != err)
            {
                APP_ERR_PRINT ("\r\nR_GPT_Start API failed\r\n");
                return(err);
            }
            else
            {
                APP_PRINT("Started Timer3 in PWM Mode\r\n");
            }
            APP_PRINT("Enter any Key to Disable GPT output using GTETRG trigger pin mode\r\n");
            while(true)
            {
                if (APP_CHECK_DATA)
                {
                    APP_READ(rByte);
                    break;
                }
            }
            g_mode_flag = POEG_TRIGGER_ON_GTETRG_INPUT_PIN_LEVEL;
            /* Enable IRQ */
            NVIC_EnableIRQ(VECTOR_NUMBER_POEG1_EVENT);
            APP_PRINT("\r\nGive active LOW signal at "GTETRG_PIN"\r\n");
            while(!g_interrupt_pin_trigger_flag)
            {
                /* waiting for interrupt flag */
            }
            APP_PRINT("\r\nPOEG trigger on GTETRG input pin level successful\r\n");
            break;
        }

        /* POEG_OUTPUT_DISABLE_USING_SOFTWARE_API - Disables GPT output pins
         * by software API */
        case POEG_OUTPUT_DISABLE_USING_SOFTWARE_API:
        {
            /* Start PWM Timer*/
            err = R_GPT_Start(&g_timer_pwm3_ctrl);
            /* Handle error */
            if (FSP_SUCCESS != err)
            {
                APP_ERR_PRINT ("\r\nR_GPT_Start API failed\r\n");
                return(err);
            }
            else
            {
                APP_PRINT("\r\nStarted Timer3 in PWM Mode\r\n");
            }
            APP_PRINT("Enter any Key to Disable GPT output using API\r\n");
            while(true)
            {
                if (APP_CHECK_DATA)
                {
                    APP_READ(rByte);
                    /* Disable POEG1 GPT output pins using software api */
                    err = R_POEG_OutputDisable(&g_poeg1_ctrl);
                    break;
                }
            }
            /* Handle error */
            if (FSP_SUCCESS != err)
            {
                APP_ERR_PRINT("\r\nPOEG Output disable API failed\r\n");
            }
            APP_PRINT("\r\nPOEG output disable using software API successful\r\n");
            g_mode_flag     =  POEG_OUTPUT_DISABLE_USING_SOFTWARE_API;
            break;
        }

        /* POEG_OUTPUT_DISABLE_ON_GTIOC_OUTPUT_LEVEL - Disables GPT output pins
         * on GTIOC pins level */
        case POEG_OUTPUT_DISABLE_ON_GTIOC_OUTPUT_LEVEL:
        {
            err = R_GPT_Start(&g_timer_pwm1_ctrl);
            /* Handle error */
            if (FSP_SUCCESS != err)
            {
                APP_ERR_PRINT ("\r\nR_GPT_Start API failed\r\n");
                return(err);
            }
            else
            {
                APP_PRINT("\r\nStarted Timer1 in PWM Mode\r\n");
            }
            err = R_GPT_Start(&g_timer_pwm2_ctrl);
            /* Handle error */
            if (FSP_SUCCESS != err)
            {
                APP_ERR_PRINT ("\r\nR_GPT_Start API failed\r\n");
                return(err);
            }
            else
            {
                APP_PRINT("\r\nStarted Timer2 in PWM Mode\r\n");
            }
            APP_PRINT("\r\nEnter any Key to Disable GPT PWM1 output\r\n");
            while(true)
            {
                if (APP_CHECK_DATA)
                {
                    APP_READ(rByte);
                    break;
                }
            }
            g_mode_flag     = POEG_OUTPUT_DISABLE_ON_GTIOC_OUTPUT_LEVEL;
            /* Enable IRQ */
            NVIC_EnableIRQ(VECTOR_NUMBER_POEG0_EVENT);
            while(!g_interrupt_output_level_flag)
            {
                /* waiting for interrupt flag */
            }
            APP_PRINT("\r\nPOEG output disable on GPT output level successful\r\n");
            break;
        }

        /* POEG_OUTPUT_DISABLE_ON_ACMPHS_EVENTS - Disables GPT output pins based
         * on comparator crossing events */
        case POEG_OUTPUT_DISABLE_ON_ACMPHS_EVENTS:
        {
            err = R_GPT_Start(&g_timer_pwm3_ctrl);
            /* Handle error */
            if (FSP_SUCCESS != err)
            {
                APP_ERR_PRINT ("\r\nR_GPT_Start API failed\r\n");
                return(err);
            }
            else
            {
                APP_PRINT("\r\nStarted Timer3 in PWM Mode\r\n");
            }
            /* Enable IRQ */
            NVIC_EnableIRQ(VECTOR_NUMBER_POEG1_EVENT);
            g_mode_flag     =  POEG_OUTPUT_DISABLE_ON_ACMPHS_EVENTS;
            while(!g_interrupt_acmphs_flag)
            {
                g_num_bytes = RESET_VALUE;
                g_dac_val   = RESET_VALUE;
                /* Reset buffer*/
                memset(rByte,NULL_CHAR,sizeof(rByte));
                APP_PRINT("\r\n Enter the DAC1 Value between (0 - 2000) or (2100 - 4095) to compare:");
                while (RESET_VALUE == g_num_bytes)
                {
                    if (APP_CHECK_DATA)
                    {
                        /* Take User input */
                        g_num_bytes = (uint8_t)APP_READ(rByte);
                        if (RESET_VALUE == g_num_bytes)
                        {
                            APP_PRINT("\r\nInvalid Input\r\n");
                        }
                    }
                }

                /* Conversion from input string to integer value */
                g_dac_val =  (uint16_t) (atoi((char *)rByte));
                APP_PRINT("\r\nInput DAC value %d", g_dac_val);
                /* Check for out of range value  */
                if (DAC_MAX_VAL < g_dac_val)
                {
                    APP_ERR_PRINT(" \r\nInvalid input, DAC value is out of range(0 - 4095)\r\n");
                }
                else if ((LOW_VAL < g_dac_val) &&  (HIGH_VAL > g_dac_val))
                {
                    APP_ERR_PRINT(" \r\nFluctuating voltage range\r\n");
                }
                else
                {
                    /* Write to DAC1 channel*/
                    err = R_DAC_Write(&g_dac1_ctrl, g_dac_val);
                    /* Handle error */
                    if (FSP_SUCCESS != err)
                    {
                        APP_ERR_PRINT ("\r\nR_DAC_Write API failed for DAC1\r\n");
                        deinit_dac_and_acmphs();
                        APP_ERR_TRAP(err);
                    }

                    /* Wait for the minimum stabilization wait time   */
                    R_BSP_SoftwareDelay(g_stabilize_time.min_stabilization_wait_us, BSP_DELAY_UNITS_MICROSECONDS);
                    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_SECONDS);
                }
            }
            APP_PRINT("\r\nPOEG output disable successful on ACMPHS crossing events ");
            break;
        }

        /* POEG_RESET - Resets the POEG status */
        case  POEG_RESET:
        {
            err = reset_poeg_module() ;
            /* Handle error */
            if (FSP_SUCCESS != err)
            {
                APP_ERR_PRINT("\r\nFailed to reset POEG with error code: 0x%x",err);
            }
            break;
        }

        default:
        {
            APP_PRINT("\r\nInvalid input, Please enter the value between 1-5\r\n");
            break;
        }
    }
    return err;
}


/*******************************************************************************************************************//**
 * @brief       This function is used for POEG Channel0 callback to disable the IRQ and set the Mode flags
 * @param[in]   poeg_callback_args_t * p_arg
 * @return      None
 **********************************************************************************************************************/
void channel0_user_callback (poeg_callback_args_t * p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    #if defined(BOARD_RA4T1_MCK) || defined(BOARD_RA6T3_MCK)
        R_IOPORT_PinWrite(&g_ioport_ctrl, LED_PIN, BSP_IO_LEVEL_LOW);
    #else
        R_IOPORT_PinWrite(&g_ioport_ctrl, LED_PIN, BSP_IO_LEVEL_HIGH);
    #endif
    if(POEG_OUTPUT_DISABLE_ON_GTIOC_OUTPUT_LEVEL == g_mode_flag)
    {
        APP_PRINT("\r\nInterrupt occur in GPT OUTPUT LEVEL Mode\r\n");
        g_interrupt_output_level_flag = SET_FLAG;
    }

    /* If the POEG0 cannot be reset, disable the POEG0 interrupt to prevent
     * it from firing continuously */
    NVIC_DisableIRQ(VECTOR_NUMBER_POEG0_EVENT);
}


/*******************************************************************************************************************//**
 * @brief       This function is used for POEG Channel1 callback to disable the IRQ and set the Mode flag
 * @param[in]   poeg_callback_args_t * p_arg
 * @return      None
 **********************************************************************************************************************/
void channel1_user_callback(poeg_callback_args_t * p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    #if defined(BOARD_RA4T1_MCK) || defined(BOARD_RA6T3_MCK)
        R_IOPORT_PinWrite(&g_ioport_ctrl, LED_PIN, BSP_IO_LEVEL_LOW);
    #else
        R_IOPORT_PinWrite(&g_ioport_ctrl, LED_PIN, BSP_IO_LEVEL_HIGH);
    #endif
    if(POEG_OUTPUT_DISABLE_ON_ACMPHS_EVENTS == g_mode_flag)
    {
        APP_PRINT("\r\nInterrupt occur in ACMPHS Mode\r\n");
        g_interrupt_acmphs_flag = SET_FLAG;
    }
    if (POEG_TRIGGER_ON_GTETRG_INPUT_PIN_LEVEL == g_mode_flag)
    {
        APP_PRINT("\r\nInterrupt occur in Pin Trigger Mode\r\n");
        g_interrupt_pin_trigger_flag = SET_FLAG;
    }

    /* If the POEG1 cannot be reset, disable the POEG1 interrupt to prevent
     * it from firing continuously */
    NVIC_DisableIRQ(VECTOR_NUMBER_POEG1_EVENT);
}


/*******************************************************************************************************************//**
 * @brief       This function is used for acmphs callback
 * @param[in]   comparator_callback_args_t *p_args
 * @return      None
 **********************************************************************************************************************/
void acmphs_user_callback(comparator_callback_args_t *p_args)
{
    /* Check for the channel 0 of comparator */
    if(CHANNEL_ZERO == p_args->channel)
    {
        /* Toggle the flag */
        b_comparator_state_flag = !b_comparator_state_flag;
    }
}


/*******************************************************************************************************************//**
 * @brief       reset_poeg_module
 * @param[in]   None
 * @retval      FSP_SUCCESS                  Upon successful POEG Reset
 * @retval      Any Other Error code apart from FSP_SUCCESS  Upon Unsuccessful
 **********************************************************************************************************************/
fsp_err_t reset_poeg_module(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Variable to store user input */
    uint8_t rByte[BUFFER_SIZE_DOWN] = {NULL_CHAR};
    uint8_t converted_rtt_input = RESET_VALUE;

    APP_PRINT(RESET_MENU_INFO);
    /* Process input only when User has provided one */
    while(!APP_CHECK_DATA);
    if (APP_CHECK_DATA)
    {
        APP_READ(rByte);
        converted_rtt_input = (uint8_t)atoi((char *)rByte);
    }
    switch (converted_rtt_input)
    {
        case POEG_CHANNEL_0:
        {
            err = R_POEG_Reset(&g_poeg0_ctrl);
            /* Handle error */
            if (FSP_SUCCESS != err)
            {
                APP_ERR_PRINT("\r\n POEG 0 reset failed\r\n");
                return(err);
            }
            APP_PRINT("\r\n RESET POEG 0 successful\r\n");
            g_interrupt_output_level_flag = CLEAR_FLAG;
            break;
        }

        case POEG_CHANNEL_1:
        {
            err = R_POEG_Reset(&g_poeg1_ctrl);
            /* Handle error */
            if (FSP_SUCCESS != err)
            {
                APP_ERR_PRINT("\r\n POEG 1 is reset failed\r\n");
                return(err);
            }
            APP_PRINT("\r\n RESET POEG 1 successful\r\n");
            g_interrupt_acmphs_flag = CLEAR_FLAG;
            g_interrupt_pin_trigger_flag = CLEAR_FLAG;
            break;
        }

        default:
        {
            APP_PRINT("\r\nInvalid input, Please enter the value between 1-2\r\n");
            break;
        }
    }
    #if defined(BOARD_RA4T1_MCK) || defined(BOARD_RA6T3_MCK)
        R_IOPORT_PinWrite(&g_ioport_ctrl, LED_PIN, BSP_IO_LEVEL_HIGH);
    #else
        R_IOPORT_PinWrite(&g_ioport_ctrl, LED_PIN, BSP_IO_LEVEL_LOW);
    #endif
    return err;
}


/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart(bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
#if BSP_FEATURE_FLASH_LP_VERSION != 0

        /* Enable reading from data flash. */
        R_FACI_LP->DFLCTL = 1U;

        /* Would normally have to wait tDSTOP(6us) for data flash recovery. Placing the enable here, before clock and
         * C runtime initialization, should negate the need for a delay since the initialization will typically take more than 6us. */
#endif
    }

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open (&g_ioport_ctrl, g_ioport.p_cfg);
    }
}


#if BSP_TZ_SECURE_BUILD

BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ();

/* Trustzone Secure Projects require at least one nonsecure callable function in order to build (Remove this if it is not required to build). */
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ()
{

}
#endif


/*******************************************************************************************************************//**
 * @} (end addtogroup poeg_ep)
 **********************************************************************************************************************/
