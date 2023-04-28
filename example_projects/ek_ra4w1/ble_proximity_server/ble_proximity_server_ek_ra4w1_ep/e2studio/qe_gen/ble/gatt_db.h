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
* Copyright (C) 2019-2022 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

#ifndef GATT_DB_H
#define GATT_DB_H

#include "profile_cmn/r_ble_serv_common.h"

extern st_ble_gatts_db_cfg_t g_gatt_db_table;

typedef enum
{
    BLE_INVALID_ATTR_HDL = 0x0000,
    BLE_GAPS_DECL_HDL = 0x0001,
    BLE_GAPS_IA_INC_HDL = 0x0002,
    BLE_GAPS_LL_INC_HDL = 0x0003,
    BLE_GAPS_TP_INC_HDL = 0x0004,
    BLE_GAPS_DEV_NAME_DECL_HDL = 0x0005,
    BLE_GAPS_DEV_NAME_VAL_HDL = 0x0006,
    BLE_GAPS_APPEARANCE_DECL_HDL = 0x0007,
    BLE_GAPS_APPEARANCE_VAL_HDL = 0x0008,
    BLE_GAPS_PER_PREF_CONN_PARAM_DECL_HDL = 0x0009,
    BLE_GAPS_PER_PREF_CONN_PARAM_VAL_HDL = 0x000A,
    BLE_GAPS_CENT_ADDR_RSLV_DECL_HDL = 0x000B,
    BLE_GAPS_CENT_ADDR_RSLV_VAL_HDL = 0x000C,
    BLE_GAPS_RSLV_PRIV_ADDR_ONLY_DECL_HDL = 0x000D,
    BLE_GAPS_RSLV_PRIV_ADDR_ONLY_VAL_HDL = 0x000E,
    BLE_GATS_DECL_HDL = 0x000F,
    BLE_GATS_GAP_INC_HDL = 0x0010,
    BLE_GATS_IA_INC_HDL = 0x0011,
    BLE_GATS_LL_INC_HDL = 0x0012,
    BLE_GATS_TP_INC_HDL = 0x0013,
    BLE_GATS_SERV_CHGED_DECL_HDL = 0x0014,
    BLE_GATS_SERV_CHGED_VAL_HDL = 0x0015,
    BLE_GATS_SERV_CHGED_CLI_CNFG_DESC_HDL = 0x0016,
    BLE_IAS_DECL_HDL = 0x0017,
    BLE_IAS_TP_INC_HDL = 0x0018,
    BLE_IAS_LL_INC_HDL = 0x0019,
    BLE_IAS_GAT_INC_HDL = 0x001A,
    BLE_IAS_ALERT_LEVEL_DECL_HDL = 0x001B,
    BLE_IAS_ALERT_LEVEL_VAL_HDL = 0x001C,
    BLE_LLS_DECL_HDL = 0x001D,
    BLE_LLS_GAP_INC_HDL = 0x001E,
    BLE_LLS_IA_INC_HDL = 0x001F,
    BLE_LLS_TP_INC_HDL = 0x0020,
    BLE_LLS_GAT_INC_HDL = 0x0021,
    BLE_LLS_ALERT_LEVEL_DECL_HDL = 0x0022,
    BLE_LLS_ALERT_LEVEL_VAL_HDL = 0x0023,
    BLE_TPS_DECL_HDL = 0x0024,
    BLE_TPS_GAP_INC_HDL = 0x0025,
    BLE_TPS_IA_INC_HDL = 0x0026,
    BLE_TPS_LL_INC_HDL = 0x0027,
    BLE_TPS_GAT_INC_HDL = 0x0028,
    BLE_TPS_TX_POWER_LEVEL_DECL_HDL = 0x0029,
    BLE_TPS_TX_POWER_LEVEL_VAL_HDL = 0x002A,
} e_ble_attr_hdl_t;

#define BLE_GAPS_DEV_NAME_LEN (128)
#define BLE_GAPS_APPEARANCE_LEN (2)
#define BLE_GAPS_PER_PREF_CONN_PARAM_LEN (8)
#define BLE_GAPS_CENT_ADDR_RSLV_LEN (1)
#define BLE_GAPS_RSLV_PRIV_ADDR_ONLY_LEN (1)
#define BLE_GATS_SERV_CHGED_LEN (4)
#define BLE_GATS_SERV_CHGED_CLI_CNFG_LEN (2)
#define BLE_IAS_ALERT_LEVEL_LEN (1)
#define BLE_LLS_ALERT_LEVEL_LEN (1)
#define BLE_TPS_TX_POWER_LEVEL_LEN (1)

#endif /* GATT_DB_H */