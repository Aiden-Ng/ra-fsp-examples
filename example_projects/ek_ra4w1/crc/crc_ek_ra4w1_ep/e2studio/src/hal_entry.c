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
 * Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/

#include "common_utils.h"
#include "crc_ep.h"

/*******************************************************************************************************************//**
 * @addtogroup crc_ep
 * @{
 **********************************************************************************************************************/

/* IRQ callback */
static volatile bool b_switch_count =  false;
static volatile bool b_uart_rxflag  =  false;
static volatile bool b_uart_txflag  =  false;

/* for on board LEDs */
extern bsp_leds_t g_bsp_leds;

/* private functions */
static fsp_err_t crc_operation(void);
static void set_led(bool b_value);

void R_BSP_WarmStart(bsp_warm_start_event_t event);

/*******************************************************************************************************************//**
 * The RA Configuration tool generates main() and uses it to generate threads if an RTOS is used.  This function is
 * called by main() when no RTOS is used.
 **********************************************************************************************************************/

void hal_entry(void)
{
    fsp_err_t          err        = FSP_SUCCESS;
    fsp_pack_version_t version    = {RESET_VALUE};

    /* version get API for FLEX pack information */
    R_FSP_VersionGet(&version);

    /* Project information printed on the Console */
    APP_PRINT(BANNER_1);
	APP_PRINT(BANNER_2);
	APP_PRINT(BANNER_3, EP_VERSION);
	APP_PRINT(BANNER_4, version.major, version.minor, version.patch);
	APP_PRINT(BANNER_5);
	APP_PRINT(BANNER_6);
    APP_PRINT(EP_INFO);

    /* Open uart module */
    err = R_SCI_UART_Open(&g_uart_ctrl, &g_uart_cfg);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        /* Display failure message in RTT */
        APP_ERR_PRINT ("R_SCI_Uart_Open API FAILED \r\n");
        APP_ERR_TRAP(err);
    }

    /* Open CRC module*/
    err = R_CRC_Open(&g_crc_ctrl, &g_crc_cfg);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        /* close opened uart module*/
        deinit_uart();
        /* Display failure message in RTT */
        APP_ERR_PRINT ("R_CRC_Open API FAILED \r\n");
        APP_ERR_TRAP(err);
    }

    /* Open External IRQ module*/
    err = R_ICU_ExternalIrqOpen(&g_external_irq_ctrl, &g_external_irq_cfg);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        /* close all opened modules */
        deinit_crc();
        deinit_uart();
        /* Display failure message in RTT */
        APP_ERR_PRINT ("R_ICU_ExternalIrqOpen API FAILED \r\n");
        APP_ERR_TRAP(err);
    }

    /* Enable External interrupt for specified pin */
    err = R_ICU_ExternalIrqEnable(&g_external_irq_ctrl);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        /* close all the opened modules */
        cleanup();
        /* Display failure message in RTT */
        APP_ERR_PRINT ("R_ICU_ExternalIrqEnable API FAILED \r\n");
        APP_ERR_TRAP(err);
    }

    while(true)
    {
        if (true == b_switch_count)
        {
            /* Clear user pushbutton flag */
            b_switch_count = false;
            /* Notify user the start of CRC operation*/
            APP_PRINT("\r\nStart CRC Operation\r\n");

            /*Perform CRC operation in normal and snoop mode*/
            err = crc_operation();
            /* Handle error */
            if (FSP_SUCCESS != err)
            {
                /* Turn on LED as sign of CRC operation failure */
                set_led(LED_ON);

                /* print RTT message */
                APP_ERR_PRINT ("\r\n ** CRC operation failed ** \r\n");
                /* close all the opened modules before trap */
                cleanup();
                APP_ERR_TRAP(err);
            }
        }
    }
}

/*******************************************************************************************************************//**
 *  @brief      Performs CRC calculation in normal and snoop mode and toggle LED on successful operation
 *              else Turn LED ON on failure. Also displays failure messages in RTT.
 *  @param[IN]  None
 *  @retval     FSP_SUCCESS    On successfully CRC result in snoop and normal operation mode.
 *  @retval     err            Any Other Error code apart from FSP_SUCCES  Unsuccessful operation.
 **********************************************************************************************************************/
static fsp_err_t crc_operation (void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* CRC inputs structure */
    crc_input_t input_data;
    uint32_t normal_crc_value      = RESET_VALUE;
    uint32_t snoop_crc_value       = RESET_VALUE;
    uint32_t uart_time_out         = UINT32_MAX;
    uint32_t seed_value            = RESET_VALUE;
    uint8_t input_buffer[BUF_LEN]  = {0x05,0x02,0x03,0x04};
    uint8_t dest_buffer[BUF_LEN]   = {RESET_VALUE};
    uint8_t  uart_data_len         = RESET_VALUE;

    /* Before beginning the operation turn off LED */
    set_led(LED_OFF);

    /*clear callback event flag */
    b_uart_rxflag  = false;
    b_uart_txflag  = false;

    /* update seed value and transfer uart_data_len as per the polynomial used */
    if(CRC_POLYNOMIAL_CRC_8 == g_crc_cfg.polynomial)
    {
        seed_value      = EIGHT_BIT_SEED;     //seed value for 8 bit polynomial
        uart_data_len   = EIGHT_BIT_DATA_LEN; //Data length for 8 bit polynomial operation
    }
    else if ((CRC_POLYNOMIAL_CRC_16 == g_crc_cfg.polynomial) || (CRC_POLYNOMIAL_CRC_CCITT == g_crc_cfg.polynomial))
    {
        seed_value      = SIXTEEN_BIT_SEED;      //seed value for 16 bit polynomial
        uart_data_len   = SIXTEEN_BIT_DATA_LEN;  //Data length for 16 bit polynomial operation
    }
    else
    {
    	/* Display failure message in RTT */
    	APP_ERR_PRINT ("UNSUPPORTED CRC POLYNOMIAL SELECECTED \r\n");
    	return FSP_ERR_UNSUPPORTED;
    }

    /* update CRC input structure for normal mode */
    input_data.num_bytes      = NUM_BYTES;
    input_data.crc_seed       = seed_value;
    input_data.p_input_buffer = &input_buffer;

    /* calculate crc value for input data in Normal mode */
    err = R_CRC_Calculate(&g_crc_ctrl, &input_data , &normal_crc_value);
    if (FSP_SUCCESS != err)
    {
        /* Display failure message in RTT */
        APP_ERR_PRINT ("R_CRC_Calculate API FAILED \r\n");
        return err;
    }

    /* append calculated CRC value from normal mode to input buffer */
    if (CRC_POLYNOMIAL_CRC_8 == g_crc_cfg.polynomial)
    {
    	/* append 8 bit CRC value to input data*/
        input_buffer[4] = (uint8_t) normal_crc_value;
    }
    else if ((CRC_POLYNOMIAL_CRC_16 == g_crc_cfg.polynomial) || (CRC_POLYNOMIAL_CRC_CCITT == g_crc_cfg.polynomial))
    {
    	/* extract the bytes from 16 bit CRC value and append to input buffer as per the selected byte order
    	 * in CRC configuration.*/
    	if(CRC_BIT_ORDER_LMS_LSB == g_crc_cfg.bit_order)
    	{
    		input_buffer[4] = (uint8_t) (normal_crc_value & 0xFF);       //extract first byte
    		input_buffer[5] = (uint8_t) ((normal_crc_value >>8) & 0xFF); //extract second byte
    	}
    	else
    	{
    		input_buffer[5] = (uint8_t) (normal_crc_value & 0xFF);       //extract first byte
    		input_buffer[4] = (uint8_t) ((normal_crc_value >>8) & 0xFF); //extract second byte
    	}
    }
    else
    {
        /*do nothing */
    }

    /*Enable snoop mode*/
    err = R_CRC_SnoopEnable(&g_crc_ctrl , seed_value);
    if (FSP_SUCCESS != err)
    {
        /* Display failure message in RTT */
        APP_ERR_PRINT ("R_CRC_SnoopEnable API FAILED \r\n");
        return err;
    }

    /* Perform SCI UART loop-back transmission from TX to RX*/
    /* Perform uart write operation */
    err =  R_SCI_UART_Write(&g_uart_ctrl,input_buffer,uart_data_len);
    if (FSP_SUCCESS != err)
    {
        /* Display failure message in RTT */
        APP_ERR_PRINT ("R_SCI_UART_Write API FAILED \r\n");
        return err;
    }

    /* Perform uart read operation */
    err =  R_SCI_UART_Read(&g_uart_ctrl,dest_buffer,uart_data_len);
    if (FSP_SUCCESS != err)
    {
        /* Display failure message in RTT */
        APP_ERR_PRINT ("R_SCI_UART_Read API FAILED \r\n");
        return err;
    }

    /* wait for tx and rx complete event */
    while((true != b_uart_txflag) || (true != b_uart_rxflag))
    {
        /*start checking for timeout to avoid infinite loop*/
        --uart_time_out;

        /*check for time elapse*/
        if (RESET_VALUE == uart_time_out)
        {
            /*we have reached to a scenario where uart tx and rx events not occurred*/
            APP_ERR_PRINT (" ** Uart tx and rx events not received during uart write or read operation **\r\r");
            return FSP_ERR_TIMEOUT;
        }
    }

    /* Get CRC value in snoop mode for receive data */
    err = R_CRC_CalculatedValueGet(&g_crc_ctrl, &snoop_crc_value);
    if (FSP_SUCCESS != err)
    {
        /* Display failure message in RTT */
        APP_ERR_PRINT ("R_CRC_CalculatedValueGet API FAILED \r\n");
        return err;
    }

    /* Disable snoop operation */
    err = R_CRC_SnoopDisable(&g_crc_ctrl);
    if (FSP_SUCCESS != err)
    {
        /* Display failure message in RTT */
        APP_ERR_PRINT ("R_CRC_SnoopDisable API FAILED \r\n");
        return err;
    }

    /* validate the CRC results */
    if (RESET_VALUE == snoop_crc_value)
    {
        APP_PRINT ("\r\nCRC Operation is successful.  \r\n");

        /* compare uart write and read data buffer */
        if ( RESET_VALUE == memcmp(dest_buffer, input_buffer , uart_data_len))
        {
            APP_PRINT ("Uart transmitted and received data successfully. \r\n");
            /* toggle led as sign of successful operation */
            toggle_led();
        }
    }
    else
    {
        APP_ERR_PRINT ("UART loop-back transmission error \r\n");
        return FSP_ERR_ABORTED;
    }
    return err;
}

/*******************************************************************************************************************//**
 *  @brief           User defined sci uart driver callback function
 *  @param[IN]       p_args
 *  @retval          None
 **********************************************************************************************************************/
void uart_cb(uart_callback_args_t *p_args)
{
    if (NULL != p_args)
    {
        switch(p_args->event)
        {
            case UART_EVENT_RX_COMPLETE:
                b_uart_rxflag = true;
                break;
            case UART_EVENT_TX_COMPLETE:
                b_uart_txflag = true;
                break;
            default:
                break;
        }
    }
}

/*******************************************************************************************************************//**
 *  @brief           User defined External IRQ driver callback function
 *  @param[IN]       p_args
 *  @retval          None
 **********************************************************************************************************************/
void ext_irq_cb(external_irq_callback_args_t *p_args)
{
    /* Make sure its a right interrupt  */
    if ( (NULL != p_args) && (IRQ_CHANNEL == p_args->channel) )
    {
        b_switch_count = true;
    }
}

/*******************************************************************************************************************//**
 * This function is called to do closing of external irq module using its HAL level API.
 * @brief     Close the external irq module. Handle the Error internally with Proper Message.
 *            Application handles the rest.
 * @param[IN] None
 * @retval    None
 **********************************************************************************************************************/
 void deinit_external_irq(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* close opened External IRQ module */
    err = R_ICU_ExternalIrqClose(&g_external_irq_ctrl);
    /* Handle error */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("** R_ICU_ExternalIrqClose API FAILED **\r\n");
    }
}

/*******************************************************************************************************************//**
 * This function is called to do closing of crc module using its HAL level API.
 * @brief     Close the crc module. Handle the Error internally with Proper Message.
 *            Application handles the rest.
 * @param[IN] None
 * @retval    None
 **********************************************************************************************************************/
void deinit_crc(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* close opened crc module */
    err = R_CRC_Close(&g_crc_ctrl);
    /* Handle error */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("** R_CRC_Close API FAILED **\r\n");
    }
}

/*******************************************************************************************************************//**
 * This function is called to do closing of sci uart module using its HAL level API.
 * @brief     Close the sci uart module. Handle the Error internally with Proper Message.
 *            Application handles the rest.
 * @param[IN] None
 * @retval    None
 **********************************************************************************************************************/
void deinit_uart(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* close opened External IRQ module */
    err = R_SCI_UART_Close(&g_uart_ctrl);
    /* Handle error */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("** R_SCI_UART_Close API FAILED **\r\n");
    }
}

/*******************************************************************************************************************//**
 * @brief     This function is called to do closing of all opened module.
 * @param[IN] None
 * @retval    None
 **********************************************************************************************************************/
void cleanup(void)
{
    /* close all the opened modules  */
    deinit_crc();
    deinit_uart();
    deinit_external_irq();
}

/*******************************************************************************************************************//**
 * @brief     Toggle on board LED, which are connected and supported by BSP
 * @param[IN] None
 * @retval    None
 **********************************************************************************************************************/
void toggle_led(void)
{
	VALIDATE_IO_PORT_API(R_IOPORT_PinWrite(g_ioport.p_ctrl,g_bsp_leds.p_leds[RESET_VALUE], LED_ON));
	R_BSP_SoftwareDelay(TOGGLE_DELAY, BSP_DELAY_UNITS_MILLISECONDS);
	VALIDATE_IO_PORT_API(R_IOPORT_PinWrite(g_ioport.p_ctrl,g_bsp_leds.p_leds[RESET_VALUE], LED_OFF));
}

/*******************************************************************************************************************//**
 *  @brief       Turn on_board LED ON or OFF.
 *  @param[IN]   b_value     LED_ON or LED_OFF
 *  @retval      None
 **********************************************************************************************************************/
static void set_led(bool b_value)
{
	VALIDATE_IO_PORT_API(R_IOPORT_PinWrite(g_ioport.p_ctrl,g_bsp_leds.p_leds[RESET_VALUE], b_value));
}

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart(bsp_warm_start_event_t event) {
    if (BSP_WARM_START_POST_C == event) {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open(&g_ioport_ctrl, &g_bsp_pin_cfg);
    }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup crc_ep)
 **********************************************************************************************************************/
