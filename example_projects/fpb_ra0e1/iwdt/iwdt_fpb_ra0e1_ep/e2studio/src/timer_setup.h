/***********************************************************************************************************************
 * File Name    : timer_setup.h
 * Description  : Contains data structures and functions used in timer_setup.c
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
 * Copyright (C) [2020-2024] Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/

#ifndef TIMER_SETUP_H_
#define TIMER_SETUP_H_

/* IWDT/NMI detect reset value */
#define SYSTEM_RSTSR1_IWDTRF_DETECT_RESET       (1u)
#define SYSTEM_RSTSR1_SWRF_DETECT_RESET         (1u)

/* Number of counts for printing IWDT Refresh status */
#define IWDT_REFRESH_COUNTER_VALUE              (2u)

#define BUFFER_SIZE                             (16u)

#ifdef BOARD_RA0E1_FPB
#define USED_TIMER                              "TAU"
#else
#define USED_TIMER                              "GPT"
#endif

/* User command input value */
#define ENABLE_IWDT                             (1u)
#define STOP_IWDT_REFRESH                       (2u)

/* function declarations  */
#ifdef BOARD_RA0E1_FPB
fsp_err_t init_tau_module(void);
void deinit_tau_module(void);
#else
fsp_err_t init_gpt_module(void);
void deinit_gpt_module(void);
#endif
fsp_err_t timer_start(void);


#endif /* TIMER_SETUP_H_ */
