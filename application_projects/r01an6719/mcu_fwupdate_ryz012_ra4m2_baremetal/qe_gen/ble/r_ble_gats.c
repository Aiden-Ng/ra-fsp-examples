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
* Copyright (C) 2019-2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name: r_ble_gats.c
 * Version : 1.0
 * Description : The source file for GATT Service service.
 **********************************************************************************************************************/

#include "r_ble_gats.h"
#include "profile_cmn/r_ble_servs_if.h"
#include "gatt_db.h"

static st_ble_servs_info_t gs_servs_info;

/*----------------------------------------------------------------------------------------------------------------------
    Service Changed Client Characteristic Configuration descriptor : Client Characteristic Configuration Descriptor
----------------------------------------------------------------------------------------------------------------------*/

static const st_ble_servs_desc_info_t gs_serv_chged_cli_cnfg = {
    .attr_hdl = BLE_GATS_SERV_CHGED_CLI_CNFG_DESC_HDL,
    .app_size = sizeof(uint16_t),
    .desc_idx = BLE_GATS_SERV_CHGED_CLI_CNFG_IDX,
    .db_size  = BLE_GATS_SERV_CHGED_CLI_CNFG_LEN,
    .decode   = (ble_servs_attr_decode_t)decode_uint16_t,
    .encode   = (ble_servs_attr_encode_t)encode_uint16_t,
};

ble_status_t R_BLE_GATS_SetServChgedCliCnfg(uint16_t conn_hdl, const uint16_t *p_value)
{
    return R_BLE_SERVS_SetDesc(&gs_serv_chged_cli_cnfg, conn_hdl, (const void *)p_value);
}

ble_status_t R_BLE_GATS_GetServChgedCliCnfg(uint16_t conn_hdl, uint16_t *p_value)
{
    return R_BLE_SERVS_GetDesc(&gs_serv_chged_cli_cnfg, conn_hdl, (void *)p_value);
}

/*----------------------------------------------------------------------------------------------------------------------
    Service Changed characteristic : The Service Changed characteristic is a control-point attribute that shall be used to indicate to connected devices that services have changed.
----------------------------------------------------------------------------------------------------------------------*/

static ble_status_t decode_st_ble_gats_serv_chged_t(st_ble_gats_serv_chged_t *p_app_value, const st_ble_gatt_value_t *p_gatt_value)
{
    /* Start user code for Service Changed characteristic value decode function. Do not edit comment generated here */
    FSP_PARAMETER_NOT_USED (p_app_value);  // silence compiler warnings
    FSP_PARAMETER_NOT_USED (p_gatt_value);
    /* End user code. Do not edit comment generated here */
    return BLE_SUCCESS;
}

static ble_status_t encode_st_ble_gats_serv_chged_t(const st_ble_gats_serv_chged_t *p_app_value, st_ble_gatt_value_t *p_gatt_value)
{
    /* Start user code for Service Changed characteristic value encode function. Do not edit comment generated here */
    FSP_PARAMETER_NOT_USED (p_app_value);  // silence compiler warnings
    FSP_PARAMETER_NOT_USED (p_gatt_value);
    /* End user code. Do not edit comment generated here */
    return BLE_SUCCESS;
}

/* Service Changed characteristic descriptor definition */
static const st_ble_servs_desc_info_t *gspp_serv_chged_descs[] = { 
    &gs_serv_chged_cli_cnfg,
};

/* Service Changed characteristic definition */
static const st_ble_servs_char_info_t gs_serv_chged_char = {
    .start_hdl    = BLE_GATS_SERV_CHGED_DECL_HDL,
    .end_hdl      = BLE_GATS_SERV_CHGED_CLI_CNFG_DESC_HDL,
    .char_idx     = BLE_GATS_SERV_CHGED_IDX,
    .app_size     = sizeof(st_ble_gats_serv_chged_t),
    .db_size      = BLE_GATS_SERV_CHGED_LEN,
    .decode       = (ble_servs_attr_decode_t)decode_st_ble_gats_serv_chged_t,
    .encode       = (ble_servs_attr_encode_t)encode_st_ble_gats_serv_chged_t,
    .pp_descs     = gspp_serv_chged_descs,
    .num_of_descs = ARRAY_SIZE(gspp_serv_chged_descs),
};

ble_status_t R_BLE_GATS_IndicateServChged(uint16_t conn_hdl, const st_ble_gats_serv_chged_t *p_value)
{
    return R_BLE_SERVS_SendHdlVal(&gs_serv_chged_char, conn_hdl, (const void *)p_value, false);
}

/*----------------------------------------------------------------------------------------------------------------------
    GATT Service server
----------------------------------------------------------------------------------------------------------------------*/

/* GATT Service characteristics definition */
static const st_ble_servs_char_info_t *gspp_chars[] = {
    &gs_serv_chged_char,
};

/* GATT Service service definition */
static st_ble_servs_info_t gs_servs_info = {
    .pp_chars     = gspp_chars,
    .num_of_chars = ARRAY_SIZE(gspp_chars),
};

ble_status_t R_BLE_GATS_Init(ble_servs_app_cb_t cb)
{
    if (NULL == cb)
    {
        return BLE_ERR_INVALID_PTR;
    }

    gs_servs_info.cb = cb;

    return R_BLE_SERVS_RegisterServer(&gs_servs_info);
}
