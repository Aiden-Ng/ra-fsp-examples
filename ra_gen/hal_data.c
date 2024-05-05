/* generated HAL source file - do not edit */
#include "hal_data.h"
#if BSP_TZ_NONSECURE_BUILD
 #if defined(BSP_CFG_CLOCKS_SECURE) && BSP_CFG_CLOCKS_SECURE
  #error "The LPM module requires CGC registers to be non-secure when it is used in a TrustZone Non-secure project."
 #endif
#endif

lpm_instance_ctrl_t g_lpm_sw_standby_with_snooze_ctrl;

const lpm_cfg_t g_lpm_sw_standby_with_snooze_cfg =
{ .low_power_mode = LPM_MODE_STANDBY_SNOOZE, .standby_wake_sources = LPM_STANDBY_WAKE_SOURCE_IRQ6
        | (lpm_standby_wake_source_t) 0,
#if BSP_FEATURE_LPM_HAS_SNOOZE
    .snooze_cancel_sources      = LPM_SNOOZE_CANCEL_SOURCE_DTC_COMPLETE,
    .snooze_request_source      = LPM_SNOOZE_REQUEST_AGT1_UNDERFLOW,
    .snooze_end_sources         =  (lpm_snooze_end_t) 0,
    .dtc_state_in_snooze        = LPM_SNOOZE_DTC_ENABLE,
#endif
#if BSP_FEATURE_LPM_HAS_SBYCR_OPE
    .output_port_enable         = 0,
#endif
#if BSP_FEATURE_LPM_HAS_DEEP_STANDBY
    .io_port_state              = 0,
    .power_supply_state         = 0,
    .deep_standby_cancel_source =  (lpm_deep_standby_cancel_source_t) 0,
    .deep_standby_cancel_edge   =  (lpm_deep_standby_cancel_edge_t) 0,
#endif
#if BSP_FEATURE_LPM_HAS_PDRAMSCR
    .ram_retention_cfg.ram_retention = (uint8_t) ( 0),
    .ram_retention_cfg.tcm_retention = false,
#endif
#if BSP_FEATURE_LPM_HAS_DPSBYCR_SRKEEP
    .ram_retention_cfg.standby_ram_retention = false,
#endif
#if BSP_FEATURE_LPM_HAS_LDO_CONTROL
    .ldo_standby_cfg.pll1_ldo = false,
    .ldo_standby_cfg.pll2_ldo = false,
    .ldo_standby_cfg.hoco_ldo = false,
#endif
  .p_extend = NULL, };

const lpm_instance_t g_lpm_sw_standby_with_snooze =
{ .p_api = &g_lpm_on_lpm, .p_ctrl = &g_lpm_sw_standby_with_snooze_ctrl, .p_cfg = &g_lpm_sw_standby_with_snooze_cfg };
#if BSP_TZ_NONSECURE_BUILD
 #if defined(BSP_CFG_CLOCKS_SECURE) && BSP_CFG_CLOCKS_SECURE
  #error "The LPM module requires CGC registers to be non-secure when it is used in a TrustZone Non-secure project."
 #endif
#endif

lpm_instance_ctrl_t g_lpm_sw_standby_ctrl;

const lpm_cfg_t g_lpm_sw_standby_cfg =
{ .low_power_mode = LPM_MODE_STANDBY, .standby_wake_sources = LPM_STANDBY_WAKE_SOURCE_IRQ6
        | (lpm_standby_wake_source_t) 0,
#if BSP_FEATURE_LPM_HAS_SNOOZE
    .snooze_cancel_sources      = LPM_SNOOZE_CANCEL_SOURCE_NONE,
    .snooze_request_source      = LPM_SNOOZE_REQUEST_RXD0_FALLING,
    .snooze_end_sources         =  (lpm_snooze_end_t) 0,
    .dtc_state_in_snooze        = LPM_SNOOZE_DTC_DISABLE,
#endif
#if BSP_FEATURE_LPM_HAS_SBYCR_OPE
    .output_port_enable         = 0,
#endif
#if BSP_FEATURE_LPM_HAS_DEEP_STANDBY
    .io_port_state              = 0,
    .power_supply_state         = 0,
    .deep_standby_cancel_source =  (lpm_deep_standby_cancel_source_t) 0,
    .deep_standby_cancel_edge   =  (lpm_deep_standby_cancel_edge_t) 0,
#endif
#if BSP_FEATURE_LPM_HAS_PDRAMSCR
    .ram_retention_cfg.ram_retention = (uint8_t) ( 0),
    .ram_retention_cfg.tcm_retention = false,
#endif
#if BSP_FEATURE_LPM_HAS_DPSBYCR_SRKEEP
    .ram_retention_cfg.standby_ram_retention = false,
#endif
#if BSP_FEATURE_LPM_HAS_LDO_CONTROL
    .ldo_standby_cfg.pll1_ldo = false,
    .ldo_standby_cfg.pll2_ldo = false,
    .ldo_standby_cfg.hoco_ldo = false,
#endif
  .p_extend = NULL, };

const lpm_instance_t g_lpm_sw_standby =
{ .p_api = &g_lpm_on_lpm, .p_ctrl = &g_lpm_sw_standby_ctrl, .p_cfg = &g_lpm_sw_standby_cfg };
#if BSP_TZ_NONSECURE_BUILD
 #if defined(BSP_CFG_CLOCKS_SECURE) && BSP_CFG_CLOCKS_SECURE
  #error "The LPM module requires CGC registers to be non-secure when it is used in a TrustZone Non-secure project."
 #endif
#endif

lpm_instance_ctrl_t g_lpm_sleep_ctrl;

const lpm_cfg_t g_lpm_sleep_cfg =
{ .low_power_mode = LPM_MODE_SLEEP, .standby_wake_sources = (lpm_standby_wake_source_t) 0,
#if BSP_FEATURE_LPM_HAS_SNOOZE
    .snooze_cancel_sources      = LPM_SNOOZE_CANCEL_SOURCE_NONE,
    .snooze_request_source      = LPM_SNOOZE_REQUEST_RXD0_FALLING,
    .snooze_end_sources         =  (lpm_snooze_end_t) 0,
    .dtc_state_in_snooze        = LPM_SNOOZE_DTC_DISABLE,
#endif
#if BSP_FEATURE_LPM_HAS_SBYCR_OPE
    .output_port_enable         = 0,
#endif
#if BSP_FEATURE_LPM_HAS_DEEP_STANDBY
    .io_port_state              = 0,
    .power_supply_state         = 0,
    .deep_standby_cancel_source =  (lpm_deep_standby_cancel_source_t) 0,
    .deep_standby_cancel_edge   =  (lpm_deep_standby_cancel_edge_t) 0,
#endif
#if BSP_FEATURE_LPM_HAS_PDRAMSCR
    .ram_retention_cfg.ram_retention = (uint8_t) ( 0),
    .ram_retention_cfg.tcm_retention = false,
#endif
#if BSP_FEATURE_LPM_HAS_DPSBYCR_SRKEEP
    .ram_retention_cfg.standby_ram_retention = false,
#endif
#if BSP_FEATURE_LPM_HAS_LDO_CONTROL
    .ldo_standby_cfg.pll1_ldo = false,
    .ldo_standby_cfg.pll2_ldo = false,
    .ldo_standby_cfg.hoco_ldo = false,
#endif
  .p_extend = NULL, };

const lpm_instance_t g_lpm_sleep =
{ .p_api = &g_lpm_on_lpm, .p_ctrl = &g_lpm_sleep_ctrl, .p_cfg = &g_lpm_sleep_cfg };
void g_hal_init(void)
{
    g_common_init ();
}
