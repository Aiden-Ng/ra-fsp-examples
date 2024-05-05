/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_lpm.h"
#include "r_lpm_api.h"
FSP_HEADER
/** lpm Instance */
extern const lpm_instance_t g_lpm_sw_standby_with_snooze;

/** Access the LPM instance using these structures when calling API functions directly (::p_api is not used). */
extern lpm_instance_ctrl_t g_lpm_sw_standby_with_snooze_ctrl;
extern const lpm_cfg_t g_lpm_sw_standby_with_snooze_cfg;
/** lpm Instance */
extern const lpm_instance_t g_lpm_sw_standby;

/** Access the LPM instance using these structures when calling API functions directly (::p_api is not used). */
extern lpm_instance_ctrl_t g_lpm_sw_standby_ctrl;
extern const lpm_cfg_t g_lpm_sw_standby_cfg;
/** lpm Instance */
extern const lpm_instance_t g_lpm_sleep;

/** Access the LPM instance using these structures when calling API functions directly (::p_api is not used). */
extern lpm_instance_ctrl_t g_lpm_sleep_ctrl;
extern const lpm_cfg_t g_lpm_sleep_cfg;
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
