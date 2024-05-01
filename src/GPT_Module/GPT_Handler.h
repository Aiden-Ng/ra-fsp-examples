/*
 * GPT_Timer_Handler.h
 *
 *  Created on: 1 May 2024
 *      Author: Ng Hong Xi
 */

#ifndef GPT_TIMER_MODULES_GPT_TIMER_HANDLER_H_
#define GPT_TIMER_MODULES_GPT_TIMER_HANDLER_H_

fsp_err_t Timer_Open(timer_instance_t const * g_timer_instance);
fsp_err_t Timer_Enable(timer_instance_t const * g_timer_instance);
fsp_err_t Timer_Start(timer_instance_t const * g_timer_instance);
fsp_err_t Timer_Reset(timer_instance_t const * g_timer_instance);
fsp_err_t Timer_Disable(timer_instance_t const * g_timer_instance);
fsp_err_t Timer_Stop(timer_instance_t const * g_timer_instance);
fsp_err_t Timer_Close(timer_instance_t const * g_timer_instance);
fsp_err_t Timer_InfoGet(timer_instance_t const * g_timer_instance, timer_info_t * g_timer_info);
fsp_err_t Timer_StatusGet(timer_instance_t const * g_timer_instance, timer_status_t * g_timer_status);
fsp_err_t Timer_CallbackSet(timer_instance_t const * g_timer_instance,
                            void (                      * p_callback)(timer_callback_args_t *),
                            void const * const            p_context,
                            timer_callback_args_t * const p_callback_memory);

#endif /* GPT_TIMER_MODULES_GPT_TIMER_HANDLER_H_ */

