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
#include "can_fd_ep.h"


/* Timeout value */
volatile uint32_t g_time_out = WAIT_TIME;
extern bsp_leds_t g_bsp_leds;

/* User defined function */
static void led_pin_initialisation(void);

/* Flags to be set in Callback function */
bool g_canfd_tx_complete = false;
bool g_canfd_rx_complete = false;
bool g_canfd_err_status = false;


/* Acceptance filter array parameters */
const canfd_afl_entry_t p_canfd0_afl[CANFD_CFG_AFL_CH0_RULE_NUM] =
{
 { /* Accept all messages with Extended ID 0x1000-0x1FFF */
   .id =
   {
    /* Specify the ID, ID type and frame type to accept. */
    .id         = CANFD_FILTER_ID,
    .frame_type = CAN_FRAME_TYPE_DATA,
    .id_mode    = CAN_ID_MODE_EXTENDED
   },

   .mask =
   {
    /* These values mask which ID/mode bits to compare when filtering messages. */
    .mask_id         = MASK_ID,
    .mask_frame_type = ZERO,
    .mask_id_mode    = MASK_ID_MODE
   },

   .destination =
   {
    /* If DLC checking is enabled any messages shorter than the below setting will be rejected. */
    .minimum_dlc = (canfd_minimum_dlc_t)ZERO,

    /* Optionally specify a Receive Message Buffer (RX MB) to store accepted frames. RX MBs do not have an
     * interrupt or overwrite protection and must be checked with R_CANFD_InfoGet and R_CANFD_Read. */
    .rx_buffer   = CANFD_RX_MB_0,

    /* Specify which FIFO(s) to send filtered messages to. Multiple FIFOs can be OR'd together. */
    .fifo_select_flags = CANFD_RX_FIFO_0,
   }
 },
};


FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
FSP_CPP_FOOTER



/*******************************************************************************************************************//**
 * main() is generated by the RA Configuration editor and is used to generate threads if an RTOS is used.  This function
 * is called by main() when no RTOS is used.
 **********************************************************************************************************************/
void hal_entry(void)
{
    fsp_err_t err = FSP_SUCCESS;
    fsp_pack_version_t version = {RESET_VALUE};
    char rtt_input_buf[BUFFER_SIZE_DOWN] = {NULL_CHAR};


    /* Initialization of LED Pins*/
    led_pin_initialisation();

    /* version get API for FLEX pack information */
    R_FSP_VersionGet(&version);

    /* Example Project information printed on the Console */
    APP_PRINT(BANNER_INFO, EP_VERSION, version.version_id_b.major, version.version_id_b.minor, version.version_id_b.patch);
    APP_PRINT(EP_INFO);

    /* Initialize canfd module */
    err = R_CANFD_Open(&g_canfd0_ctrl, &g_canfd0_cfg);
    /* Error trap */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\nCANFD Open API failed");
        APP_ERR_TRAP(err);
    }

    APP_PRINT("\nPlease enter any key on RTT Viewer to initiate CAN transmission.\n");


    while(1)
    {
        /* Check for user input */
        if (APP_CHECK_DATA)
        {
            APP_READ(rtt_input_buf);
            /* Update transmit frame and initiate transmission on CAN frame */
            canfd_operation();
        }

        /* Get the status of transmitted frame and read the data */
        can_read_operation();
        if(true == g_canfd_err_status)
        {
            g_canfd_err_status = false;
            APP_ERR_PRINT("\nCAN ERR status");
            APP_ERR_TRAP(true);
        }

        /* Re initializing time out value */
        g_time_out = WAIT_TIME;
    }


#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
}

/*******************************************************************************************************************//**
 * @brief       This function is to initialize state of LED pins.
 * @param[in]   None
 * @return      None
 **********************************************************************************************************************/
static void led_pin_initialisation(void)
{
    /* Set the LED pin state high */
    R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[0], BSP_IO_LEVEL_HIGH); //Blue LED
    R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[1], BSP_IO_LEVEL_HIGH); //Green LED
    R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[2], BSP_IO_LEVEL_HIGH); //Red LED

    R_BSP_SoftwareDelay(WAIT_TIME, BSP_DELAY_UNITS_MICROSECONDS);

    /* Set the LED pin state low */
    R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[0], BSP_IO_LEVEL_LOW);
    R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[1], BSP_IO_LEVEL_LOW);
    R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[2], BSP_IO_LEVEL_LOW);
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
        R_IOPORT_Open (&g_ioport_ctrl, &g_bsp_pin_cfg);
    }
}

#if BSP_TZ_SECURE_BUILD

BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ();

/* Trustzone Secure Projects require at least one nonsecure callable function in order to build (Remove this if it is not required to build). */
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ()
{

}
#endif
