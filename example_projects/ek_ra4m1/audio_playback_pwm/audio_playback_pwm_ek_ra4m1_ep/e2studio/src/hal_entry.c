/***********************************************************************************************************************
 * File Name    : hal_entry.c
 * Description  : Contains data structures and functions used in hal_entry.c.
 **********************************************************************************************************************/
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
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
#include "common_utils.h"
#include "audio_playback_pwm_ep.h"
#include "adpcm_decoder_ep.h"

FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
FSP_CPP_FOOTER

/* User declared global variable */
extern volatile bool g_playback_started ;
extern volatile bool g_audio_stop ;


/*******************************************************************************************************************//**
 * main() is generated by the RA Configuration editor and is used to generate threads if an RTOS is used.  This function
 * is called by main() when no RTOS is used.
 **********************************************************************************************************************/
void hal_entry(void)
{
    fsp_err_t err = FSP_SUCCESS;
    fsp_pack_version_t version =   { RESET_VALUE };
    static uint8_t rtt_input_buf[BUFFER_SIZE_DOWN] = {RESET_VALUE};
    uint8_t converted_rtt_input = RESET_VALUE;

    /* Version get API for FLEX pack information */
    R_FSP_VersionGet(&version);

    /* Example Project information printed on the Console */
    APP_PRINT(BANNER_INFO, EP_VERSION, version.major, version.minor, version.patch);
    APP_PRINT(EP_INFO);

    /* Initialize ADPCM module  */
    err = init_adpcm();
    /* Error trap */
    if(FSP_SUCCESS != err)
    {
        /* init_adpcm failure message */
        APP_ERR_PRINT("** init_adpcm function failed ** \r\n");
        APP_ERR_TRAP(err);
    }
    /* Initialize audio playback pwm module  */
     err = init_audio_playback_pwm();
     /* Error trap */
     if(FSP_SUCCESS != err)
     {
         /* init_adpcm_audio failure message */
         APP_ERR_PRINT("** init_audio_playback_pwm function failed ** \r\n");
         /* deinit the adpcm decoder */
         deinit_adpcm();
         APP_ERR_TRAP(err);
     }
    APP_PRINT("Init operation is completed successfully\r\n");
    /* Decoding the ADPCM data into 16-bit signed PCM data */
    err = decode_adpcm();
    /* Error trap */
    if(FSP_SUCCESS != err)
    {
        /* decode_adpcm failure message */
        APP_ERR_PRINT("** decode_adpcm function failed ** \r\n");
        /* deinit ADPCM decoder */
        deinit_adpcm();
        /* deinit audio playback pwm */
        deinit_audio_playback_pwm();
        APP_ERR_TRAP(err);
    }

    /* Convert signed PCM data into unsigned PCM data */
    sign_to_unsign();

    /* Menu options */
    APP_PRINT(MENU);

    while(true)
    {
        if (APP_CHECK_DATA)
        {
            APP_READ (rtt_input_buf);
            converted_rtt_input = (uint8_t)atoi((char *)rtt_input_buf);
            /* Process user input  */
            err = process_user_input (converted_rtt_input);
            /* Error trap */
            if(FSP_SUCCESS != err)

            {   /* process_user_input failure message */
                APP_ERR_PRINT("** process_user_input function failed ** \r\n");
                /* deinit ADPCM decoder */
                deinit_adpcm();
                /* deinit audio playback pwm */
                deinit_audio_playback_pwm();
                APP_ERR_TRAP(err);
            }
        }
        /*Play continuous audio until user selects audio stop*/
        if(g_playback_started && (!g_audio_stop))
        {
            /* Clear the playback started flag */
            g_playback_started = false;
            /* Start playing audio */
            err = play_audio();
            /* Error trap */
            if(FSP_SUCCESS != err)
            {
                /* play_audio failure message */
                APP_ERR_PRINT("** play_audio function failed ** \r\n");
                /* deinit ADPCM decoder*/
                deinit_adpcm();
                /* deinit audio playback module  */
                deinit_audio_playback_pwm();
                APP_ERR_TRAP(err);
            }
            APP_PRINT("\nPlaying continuous audio");
        }
    }
#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
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