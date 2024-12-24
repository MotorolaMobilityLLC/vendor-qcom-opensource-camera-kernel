/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _CAM_TFE1080_H_
#define _CAM_TFE1080_H_
#include "cam_vfe_top_ver4.h"
#include "cam_vfe_core.h"
#include "cam_vfe_bus_ver3.h"
#include "cam_irq_controller.h"

#define CAM_TFE_1080_NUM_TOP_DBG_REG          17
#define CAM_TFE_1080_NUM_BAYER_DBG_REG        11
#define CAM_TFE_BUS_VER3_1080_MAX_CLIENTS     28

static struct cam_vfe_top_ver4_module_desc tfe1080_ipp_mod_desc[] = {
	{
		.id = 0,
		.desc = "CLC_STATS_AWB_BG_TINTLESS",
	},
	{
		.id  = 1,
		.desc = "CLC_STATS_AWB_BG_AE",
	},
	{
		.id = 2,
		.desc = "CLC_STATS_BHIST_AEC",
	},
	{
		.id = 3,
		.desc = "CLC_STATS_RS",
	},
	{
		.id = 4,
		.desc = "CLC_STATS_BFW_AWB",
	},
	{
		.id = 5,
		.desc = "CLC_STATS_AWB_BG_AWB",
	},
	{
		.id = 6,
		.desc = "CLC_STATS_BHIST_AF",
	},
	{
		.id = 7,
		.desc = "CLC_STATS_AWB_BG_ALSC",
	},
	{
		.id = 8,
		.desc = "CLC_STATS_BHIST_TMC",
	},
	{
		.id = 9,
		.desc = "CLC_COMPDECOMP_FD",
	},
	{
		.id = 10,
		.desc = "CLC_BLS",
	},
	{
		.id = 11,
		.desc = "CLC_COLOR_CORRECT",
	},
	{
		.id = 12,
		.desc = "CLC_GTM",
	},
	{
		.id = 13,
		.desc = "CLC_GLUT",
	},
	{
		.id = 14,
		.desc = "CLC_COLOR_XFORM",
	},
	{
		.id  = 15,
		.desc = "CLC_DOWNSCALE_MN_Y",
	},
	{
		.id = 16,
		.desc = "CLC_DOWNSCALE_MN_C",
	},
	{
		.id = 17,
		.desc = "CLC_CROP_RND_CLAMP_FD_Y",
	},
	{
		.id = 18,
		.desc = "CLC_CROP_RND_CLAMP_FD_C",
	},
	{
		.id = 19,
		.desc = "CLC_BDS2_DEMO",
	},
	{
		.id = 20,
		.desc = "CLC_PUNCH_BDS2",
	},
	{
		.id = 21,
		.desc = "CLC_PUNCH_DS4_MUX",
	},
	{
		.id = 22,
		.desc = "CLC_BAYER_DS_4_DS4",
	},
	{
		.id = 23,
		.desc = "CLC_CROP_RND_CLAMP_DS4",
	},
	{
		.id = 24,
		.desc = "CLC_PUNCH_DS16",
	},
	{
		.id = 25,
		.desc = "CLC_BAYER_DS_4_DS16",
	},
	{
		.id = 26,
		.desc = "CLC_CROP_RND_CLAMP_DS16",
	},
	{
		.id = 27,
		.desc = "CLC_CROP_RND_CLAMP_DS2",
	},
	{
		.id = 28,
		.desc = "CLC_RCS_DS2",
	},
	{
		.id = 29,
		.desc = "CLC_CROP_RND_CLAMP_FULL_OUT",
	},
	{
		.id = 30,
		.desc = "CLC_COMPDECOMP_BYPASS",
	},
	{
		.id = 31,
		.desc = "CLC_CROP_RND_CLAMP_BYPASS",
	},
	{
		.id = 32,
		.desc = "CLC_RCS_FULL_OUT",
	},
	/**
	 * Main_PP status register does not capture CLC_HAF violation,
	 * but debug_err_vec + timestamp feature does. Since both use
	 * the same violation ID table, we add it here
	 */
	{
		.id = 33,
		.desc = "CLC_HAF",
	},
};

struct cam_vfe_top_ver4_module_desc tfe1080_bayer_mod_desc[] = {
	{
		.id = 0,
		.desc = "CLC_DEMUX",
	},
	{
		.id = 1,
		.desc = "CLC_UNIV_CHANNEL_GAINS",
	},
	{
		.id = 2,
		.desc = "CLC_QPDR",
	},
	{
		.id = 3,
		.desc = "CLC_BPC_PDPC_GIC",
	},
	{
		.id = 4,
		.desc = "CLC_PDPC_BPC_1D",
	},
	{
		.id = 5,
		.desc = "CLC_ABF_BINC",
	},
	{
		.id = 6,
		.desc = "CLC_CHANNEL_GAINS",
	},
	{
		.id = 7,
		.desc = "CLC_LSC",
	},
	{
		.id = 8,
		.desc = "CLC_FCG",
	},
	{
		.id = 9,
		.desc = "CLC_WB_GAIN",
	},
	{
		.id = 10,
		.desc = "CLC_COMPDECOMP_BAYER",
	},
};

static struct cam_vfe_top_ver4_wr_client_desc tfe1080_wr_client_desc[] = {
	{
		.wm_id = 0,
		.desc = "FULL",
	},
	{
		.wm_id = 1,
		.desc = "DS4_Y",
	},
	{
		.wm_id = 2,
		.desc = "DS4_C",
	},
	{
		.wm_id = 3,
		.desc  = "DS16_Y",
	},
	{
		.wm_id = 4,
		.desc = "DS16_C",
	},
	{
		.wm_id = 5,
		.desc = "DS2_Y",
	},
	{
		.wm_id = 6,
		.desc = "DS2_C",
	},
	{
		.wm_id = 7,
		.desc = "FD_Y",
	},
	{
		.wm_id = 8,
		.desc = "FD_C",
	},
	{
		.wm_id = 9,
		.desc = "PIXEL_RAW",
	},
	{
		.wm_id = 10,
		.desc = "AEC_BG",
	},
	{
		.wm_id = 11,
		.desc = "STATS_AEC_BHIST",
	},
	{
		.wm_id = 12,
		.desc = "STATS_TINTLESS_BG",
	},
	{
		.wm_id = 13,
		.desc = "STATS_AWB_BG",
	},
	{
		.wm_id = 14,
		.desc = "STATS_AWB_BFW",
	},
	{
		.wm_id = 15,
		.desc = "STATS_AF_BHIST",
	},
	{
		.wm_id = 16,
		.desc = "STATS_ALSC_BG",
	},
	{
		.wm_id = 17,
		.desc = "STATS_FLICKER_BAYERRS",
	},
	{
		.wm_id = 18,
		.desc = "STATS_TMC_BHIST",
	},
	{
		.wm_id = 19,
		.desc = "PDAF_0_STATS",
	},
	{
		.wm_id = 20,
		.desc = "PDAF_1_PREPROCESS_2PD",
	},
	{
		.wm_id = 21,
		.desc = "PDAF_2_PARSED_DATA",
	},
	{
		.wm_id = 22,
		.desc = "PDAF_3_CAF",
	},
	{
		.wm_id = 23,
		.desc = "RDI0",
	},
	{
		.wm_id = 24,
		.desc = "RDI1",
	},
	{
		.wm_id = 25,
		.desc = "RDI2",
	},
	{
		.wm_id = 26,
		.desc = "RDI3",
	},
	{
		.wm_id = 27,
		.desc = "RDI4",
	},
};

static struct cam_vfe_top_ver4_top_err_irq_desc tfe1080_top_irq_err_desc[] = {
	{
		.bitmask = BIT(2),
		.err_name = "BAYER_HM violation",
		.desc = "CLC CCIF Violation",
	},
	{
		.bitmask = BIT(24),
		.err_name = "DYNAMIC PDAF SWITCH VIOLATION",
		.desc =
			"HAF RDI exposure select changes dynamically, the common vbi is insufficient",
	},
	{
		.bitmask = BIT(25),
		.err_name  = "HAF violation",
		.desc = "CLC_HAF Violation",
	},
	{
		.bitmask = BIT(26),
		.err_name = "PP VIOLATION",
		.desc = "CCIF protocol violation",
	},
	{
		.bitmask  = BIT(27),
		.err_name = "DIAG VIOLATION",
		.desc = "Sensor: The HBI at TFE input is less than the spec (64 cycles)",
		.debug = "Check sensor config",
	},
};

static struct cam_vfe_top_ver4_pdaf_violation_desc tfe1080_haf_violation_desc[] = {
	{
		.bitmask = BIT(0),
		.desc = "Sim monitor 1 violation - SAD output",
	},
	{
		.bitmask = BIT(1),
		.desc = "Sim monitor 2 violation - pre-proc output",
	},
	{
		.bitmask = BIT(2),
		.desc = "Sim monitor 3 violation - parsed output",
	},
	{
		.bitmask = BIT(3),
		.desc = "Sim monitor 4 violation - CAF output",
	},
	{
		.bitmask  = BIT(4),
		.desc = "PDAF constraint violation",
	},
	{
		.bitmask = BIT(5),
		.desc = "CAF constraint violation",
	},
};

static struct cam_vfe_top_ver4_pdaf_lcr_res_info tfe1080_pdaf_haf_res_mask[] = {
	{
		.res_id = CAM_ISP_HW_VFE_IN_RDI0,
		.val = 0,
	},
	{
		.res_id = CAM_ISP_HW_VFE_IN_RDI1,
		.val = 1,
	},
	{
		.res_id = CAM_ISP_HW_VFE_IN_RDI2,
		.val = 2,
	},
};

static struct cam_irq_register_set tfe1080_top_irq_reg_set = {
	.mask_reg_offset   = 0x000001D4,
	.clear_reg_offset  = 0x000001D8,
	.status_reg_offset = 0x000001DC,
	.set_reg_offset    = 0x000001E0,
	.test_set_val      = BIT(0),
	.test_sub_val      = BIT(0),
};

static struct cam_irq_controller_reg_info tfe1080_top_irq_reg_info = {
	.num_registers = 1,
	.irq_reg_set = &tfe1080_top_irq_reg_set,
	.global_irq_cmd_offset = 0x000001D0,
	.global_clear_bitmask  = 0x00000001,
	.global_set_bitmask    = 0x00000010,
	.clear_all_bitmask     = 0xFFFFFFFF,
};

static uint32_t tfe1080_top_debug_reg[] = {
	0x000004EC,
	0x000004F0,
	0x000004F4,
	0x000004F8,
	0x000004FC,
	0x00000500,
	0x00000504,
	0x00000508,
	0x0000050C,
	0x00000510,
	0x00000514,
	0x00000518,
	0x0000051C,
	0x00000520,
	0x00000524,
	0x00000528,
	0x0000052C,
};

static uint32_t tfe1080_bayer_debug_reg[] = {
	0x0000E4E8,
	0x0000E4EC,
	0x0000E4F0,
	0x0000E4F4,
	0x0000E4F8,
	0x0000E4FC,
	0x0000E500,
	0x0000E504,
	0x0000E508,
	0x0000E50C,
};

static struct cam_vfe_top_ver4_reg_offset_common tfe1080_top_common_reg = {
	.hw_version               = 0x00000000,
	.core_cgc_ovd_0           = 0x00000100,
	.ahb_cgc_ovd              = 0x00000108,
	.core_mux_cfg             = 0x00000110,
	.pdaf_input_cfg_0         = 0x00000114,
	.pdaf_input_cfg_1         = 0x00000118,
	.stats_throttle_cfg_0     = 0x00000150,
	.stats_throttle_cfg_1     = 0x00000154,
	.stats_throttle_cfg_2     = 0x00000158,
	.core_cfg_4               = 0x0000015C,
	.pdaf_parsed_throttle_cfg = 0x00000160,
	.fd_y_throttle_cfg        = 0x00000168,
	.fd_c_throttle_cfg        = 0x0000016C,
	.ds16_g_throttle_cfg      = 0x00000170,
	.ds16_br_throttle_cfg     = 0x00000174,
	.ds4_g_throttle_cfg       = 0x00000178,
	.ds4_br_throttle_cfg      = 0x0000017C,
	.ds2_g_throttle_cfg       = 0x00000180,
	.ds2_br_throttle_cfg      = 0x00000184,
	.full_out_throttle_cfg    = 0x00000188,
	.diag_config              = 0x0000039C,
	.global_reset_cmd         = 0x000001D0,
	.diag_sensor_status       = {0x000003A0, 0x000003A4, 0x000003A8, 0x000003AC},
	.diag_frm_cnt_status      = {0x000003B0, 0x000003B4, 0x000003B8},
	.ipp_violation_status     = 0x00000248,
	.bayer_violation_status   = 0x0000E248,
	.pdaf_violation_status    = 0x00009304,
	.dsp_status               = 0x0,
	.bus_violation_status     = 0x00001064,
	.bus_overflow_status      = 0x00001068,
	.num_perf_counters        = 8,
	.perf_count_reg = {
		{
			.perf_count_cfg    = 0x000003DC,
			.perf_count_cfg_mc = 0x000003E0,
			.perf_pix_count    = 0x000003E4,
			.perf_line_count   = 0x000003E8,
			.perf_stall_count  = 0x000003EC,
			.perf_always_count = 0x000003F0,
			.perf_count_status = 0x000003F4,
		},
		{
			.perf_count_cfg    = 0x000003F8,
			.perf_count_cfg_mc = 0x000003FC,
			.perf_pix_count    = 0x00000400,
			.perf_line_count   = 0x00000404,
			.perf_stall_count  = 0x00000408,
			.perf_always_count = 0x0000040C,
			.perf_count_status = 0x00000410,
		},
		{
			.perf_count_cfg    = 0x00000414,
			.perf_count_cfg_mc = 0x00000418,
			.perf_pix_count    = 0x0000041C,
			.perf_line_count   = 0x00000420,
			.perf_stall_count  = 0x00000424,
			.perf_always_count = 0x00000428,
			.perf_count_status = 0x0000042C,
		},
		{
			.perf_count_cfg    = 0x00000430,
			.perf_count_cfg_mc = 0x00000434,
			.perf_pix_count    = 0x00000438,
			.perf_line_count   = 0x0000043C,
			.perf_stall_count  = 0x00000440,
			.perf_always_count = 0x00000444,
			.perf_count_status = 0x00000448,
		},
		/*  Bayer perf count regs from here onwards */
		{
			.perf_count_cfg    = 0x0000E3DC,
			.perf_count_cfg_mc = 0x0000E3E0,
			.perf_pix_count    = 0x0000E3E4,
			.perf_line_count   = 0x0000E3E8,
			.perf_stall_count  = 0x0000E3EC,
			.perf_always_count = 0x0000E3F0,
			.perf_count_status = 0x0000E3F4,
		},
		{
			.perf_count_cfg    = 0x0000E3F8,
			.perf_count_cfg_mc = 0x0000E3FC,
			.perf_pix_count    = 0x0000E400,
			.perf_line_count   = 0x0000E404,
			.perf_stall_count  = 0x0000E408,
			.perf_always_count = 0x0000E40C,
			.perf_count_status = 0x0000E410,
		},
		{
			.perf_count_cfg    = 0x0000E414,
			.perf_count_cfg_mc = 0x0000E418,
			.perf_pix_count    = 0x0000E41C,
			.perf_line_count   = 0x0000E420,
			.perf_stall_count  = 0x0000E424,
			.perf_always_count = 0x0000E428,
			.perf_count_status = 0x0000E42C,
		},
		{
			.perf_count_cfg    = 0x0000E430,
			.perf_count_cfg_mc = 0x0000E434,
			.perf_pix_count    = 0x0000E438,
			.perf_line_count   = 0x0000E43C,
			.perf_stall_count  = 0x0000E440,
			.perf_always_count = 0x0000E444,
			.perf_count_status = 0x0000E448,
		},
	},
	.top_debug_err_vec_irq    = {0x000004E4, 0x000004E8},
	.top_debug_err_vec_ts_lb  = 0x000004DC,
	.top_debug_err_vec_ts_mb  = 0x000004E0,
	.bayer_debug_err_vec_irq  = {0x0000E4E4, 0x0},
	.bayer_debug_err_vec_ts_lb = 0x0000E4DC,
	.bayer_debug_err_vec_ts_mb = 0x0000E4E0,
	.top_debug_cfg            = 0x00000548,
	.bayer_debug_cfg          = 0x0000E518,
	.num_top_debug_reg        = CAM_TFE_1080_NUM_TOP_DBG_REG,
	.top_debug = tfe1080_top_debug_reg,
	.num_bayer_debug_reg = CAM_TFE_1080_NUM_BAYER_DBG_REG,
	.bayer_debug = tfe1080_bayer_debug_reg,
	.frame_timing_irq_reg_idx = CAM_IFE_IRQ_CAMIF_REG_STATUS0,
	.capabilities = CAM_VFE_COMMON_CAP_SKIP_CORE_CFG |
			CAM_VFE_COMMON_CAP_CORE_MUX_CFG |
			CAM_VFE_COMMON_CAP_DEBUG_ERR_VEC,
};

static struct cam_vfe_ver4_path_reg_data tfe1080_ipp_common_reg_data = {
	.sof_irq_mask                    = 0x150,
	.eof_irq_mask                    = 0x2A0,
	.error_irq_mask                  = 0xF000005,
	.ipp_violation_mask              = 0x4000000,
	.bayer_violation_mask            = 0x4,
	.pdaf_violation_mask             = 0x2000000,
	.diag_violation_mask             = 0x8000000,
	.diag_sensor_sel_mask            = 0x6,
	.diag_frm_count_mask_0           = 0xF000,
	.enable_diagnostic_hw            = 0x1,
	.top_debug_cfg_en                = 3,
	.is_mc_path                      = true,
	/* SOF and EOF mask combined for each context */
	.frm_irq_hw_ctxt_mask = {
		0x30,
		0xC0,
		0x300,
	},
};

static struct cam_vfe_ver4_path_reg_data tfe1080_pdlib_reg_data = {
	.sof_irq_mask                    = 0x400,
	.eof_irq_mask                    = 0x800,
	.diag_sensor_sel_mask            = 0x8,
	.diag_frm_count_mask_0           = 0x40,
	.enable_diagnostic_hw            = 0x1,
	.top_debug_cfg_en                = 3,
};

static struct cam_vfe_ver4_path_reg_data tfe1080_vfe_full_rdi_reg_data[5] = {
	{
		.sof_irq_mask                    = 0x1000,
		.eof_irq_mask                    = 0x2000,
		.error_irq_mask                  = 0x0,
		.diag_sensor_sel_mask            = 0xA,
		.diag_frm_count_mask_0           = 0x80,
		.enable_diagnostic_hw            = 0x1,
		.top_debug_cfg_en                = 3,
	},
	{
		.sof_irq_mask                    = 0x4000,
		.eof_irq_mask                    = 0x8000,
		.error_irq_mask                  = 0x0,
		.diag_sensor_sel_mask            = 0xC,
		.diag_frm_count_mask_0           = 0x100,
		.enable_diagnostic_hw            = 0x1,
		.top_debug_cfg_en                = 3,
	},
	{
		.sof_irq_mask                    = 0x10000,
		.eof_irq_mask                    = 0x20000,
		.error_irq_mask                  = 0x0,
		.enable_diagnostic_hw            = 0x1,
		.diag_sensor_sel_mask            = 0xE,
		.diag_frm_count_mask_0           = 0x200,
		.top_debug_cfg_en                = 3,
	},
	{
		.sof_irq_mask                    = 0x40000,
		.eof_irq_mask                    = 0x80000,
		.error_irq_mask                  = 0x0,
		.diag_sensor_sel_mask            = 0x10,
		.diag_frm_count_mask_0           = 0x400,
		.enable_diagnostic_hw            = 0x1,
		.top_debug_cfg_en                = 3,
	},
	{
		.sof_irq_mask                    = 0x100000,
		.eof_irq_mask                    = 0x200000,
		.error_irq_mask                  = 0x0,
		.diag_sensor_sel_mask            = 0x12,
		.diag_frm_count_mask_0           = 0x800,
		.enable_diagnostic_hw            = 0x1,
		.top_debug_cfg_en                = 3,
	},
};

struct cam_vfe_ver4_path_hw_info
	tfe1080_rdi_hw_info_arr[] = {
	{
		.common_reg     = &tfe1080_top_common_reg,
		.reg_data       = &tfe1080_vfe_full_rdi_reg_data[0],
	},
	{
		.common_reg     = &tfe1080_top_common_reg,
		.reg_data       = &tfe1080_vfe_full_rdi_reg_data[1],
	},
	{
		.common_reg     = &tfe1080_top_common_reg,
		.reg_data       = &tfe1080_vfe_full_rdi_reg_data[2],
	},
	{
		.common_reg     = &tfe1080_top_common_reg,
		.reg_data       = &tfe1080_vfe_full_rdi_reg_data[3],
	},
	{
		.common_reg     = &tfe1080_top_common_reg,
		.reg_data       = &tfe1080_vfe_full_rdi_reg_data[4],
	},
};

static struct cam_vfe_top_ver4_debug_reg_info tfe1080_top_dbg_reg_info[
	CAM_TFE_1080_NUM_TOP_DBG_REG][8] = {
	VFE_DBG_INFO_ARRAY_4bit("test_bus_reserved",
		"test_bus_reserved",
		"test_bus_reserved",
		"test_bus_reserved",
		"test_bus_reserved",
		"test_bus_reserved",
		"test_bus_reserved",
		"test_bus_reserved"
	),
	{
		VFE_DBG_INFO_WITH_IDLE(0, "STATS_AWB_BG_TINTLESS",
			0x00000530, (BIT(0) | BIT(1) | BIT(2))),
		VFE_DBG_INFO_WITH_IDLE(4, "STATS_AWB_BG_AE",
			0x00000530, (BIT(3) | BIT(4) | BIT(5))),
		VFE_DBG_INFO_WITH_IDLE(8, "STATS_BHIST_AEC",
			0x00000530, (BIT(6) | BIT(7) | BIT(8))),
		VFE_DBG_INFO_WITH_IDLE(12, "STATS_RS",
			0x00000530, (BIT(9) | BIT(10) | BIT(11))),
		VFE_DBG_INFO_WITH_IDLE(16, "STATS_BFW_AWB",
			0x00000530, (BIT(12) | BIT(13) | BIT(14))),
		VFE_DBG_INFO_WITH_IDLE(20, "STATS_AWB_BG_AWB",
			0x00000530, (BIT(15) | BIT(16) | BIT(17))),
		VFE_DBG_INFO_WITH_IDLE(24, "STATS_BHIST_AF",
			0x00000530, (BIT(18) | BIT(19) | BIT(20))),
		VFE_DBG_INFO_WITH_IDLE(28, "STATS_AWB_BG_ALSC",
			0x00000530, (BIT(21) | BIT(22) | BIT(23))),
	},
	{
		VFE_DBG_INFO_WITH_IDLE(0, "STATS_BHIST_TMC",
			0x00000530, (BIT(24) | BIT(25) | BIT(26))),
		VFE_DBG_INFO_WITH_IDLE(4, "compdecomp_fd",
			0x00000530, BIT(27)),
		VFE_DBG_INFO_WITH_IDLE(8, "color_correct",
			0x00000530, BIT(28)),
		VFE_DBG_INFO_WITH_IDLE(12, "gtm",
			0x00000530, BIT(29)),
		VFE_DBG_INFO_WITH_IDLE(16, "glut",
			0x00000530, BIT(30)),
		VFE_DBG_INFO_WITH_IDLE(20, "color_xform",
			0x00000530, BIT(31)),
		VFE_DBG_INFO_WITH_IDLE(24, "downscale_mn_y",
			0x00000534, BIT(0)),
		VFE_DBG_INFO_WITH_IDLE(28, "downscale_mn_c",
			0x00000534, BIT(1)),
	},
	{
		VFE_DBG_INFO_WITH_IDLE(0, "crop_rnd_clamp_fd_y",
			0x00000534, BIT(2)),
		VFE_DBG_INFO_WITH_IDLE(4, "crop_rnd_clamp_fd_c",
			0x00000534, BIT(3)),
		VFE_DBG_INFO_WITH_IDLE(8, "bds2_demo",
			0x00000534, (BIT(4) | BIT(5) | BIT(6))),
		VFE_DBG_INFO_WITH_IDLE(12, "punch_bds2",
			0x00000534, (BIT(7) | BIT(8) | BIT(9))),
		VFE_DBG_INFO_WITH_IDLE(16, "punch_ds4_mux",
			0x00000534, (BIT(10) | BIT(11) | BIT(12))),
		VFE_DBG_INFO_WITH_IDLE(20, "bayer_ds_4_ds4",
			0x00000534, (BIT(13) | BIT(14) | BIT(15))),
		VFE_DBG_INFO_WITH_IDLE(24, "crop_rnd_clamp_ds4",
			0x00000534, (BIT(16) | BIT(17) | BIT(18))),
		VFE_DBG_INFO_WITH_IDLE(28, "punch_ds16",
			0x00000534, (BIT(19) | BIT(20) | BIT(21))),
	},
	{
		VFE_DBG_INFO_WITH_IDLE(0, "bayer_ds_4_ds16",
			0x00000534, (BIT(22) | BIT(23) | BIT(24))),
		VFE_DBG_INFO_WITH_IDLE(4, "crop_rnd_clamp_ds16",
			0x00000534, (BIT(25) | BIT(26) | BIT(27))),
		VFE_DBG_INFO_WITH_IDLE(8, "crop_rnd_clamp_ds2",
			0x00000534, (BIT(28) | BIT(29) | BIT(30))),
		VFE_DBG_INFO_WITH_IDLE(12, "clc_haf",
			0x00000534, BIT(31)),
		VFE_DBG_INFO_WITH_IDLE(16, "clc_rcs_ds2",
			0x00000538, (BIT(0) | BIT(1) | BIT(2))),
		VFE_DBG_INFO_WITH_IDLE(20, "clc_crop_rnd_clamp_full_out",
			0x00000538, (BIT(3) | BIT(4) | BIT(5))),
		VFE_DBG_INFO_WITH_IDLE(24, "clc_compdecomp_bypass",
			0x00000538, (BIT(6) | BIT(7) | BIT(8))),
		VFE_DBG_INFO_WITH_IDLE(28, "clc_crop_rnd_clamp_bypass",
			0x00000538, (BIT(9) | BIT(10) | BIT(11))),
	},
	{
		VFE_DBG_INFO_WITH_IDLE(0, "clc_rcs_full_out",
			0x00000538, (BIT(12) | BIT(13) | BIT(14))),
		VFE_DBG_INFO_WITH_IDLE(4, "clc_haf",
			0x00000538, BIT(15)),
		VFE_DBG_INFO_WITH_IDLE(8, "csid_tfe_ipp",
			0x00000538, (BIT(16) | BIT(17) | BIT(18))),
		VFE_DBG_INFO_WITH_IDLE(12, "ppp_repeater",
			0x00000538, BIT(19)),
		VFE_DBG_INFO_WITH_IDLE(16, "stats_awb_bg_tintless_throttle",
			0x00000538, (BIT(20) | BIT(21) | BIT(22))),
		VFE_DBG_INFO_WITH_IDLE(20, "stats_awb_bg_ae_throttle",
			0x00000538, (BIT(23) | BIT(24) | BIT(25))),
		VFE_DBG_INFO_WITH_IDLE(24, "stats_ae_bhist_throttle",
			0x00000538, (BIT(26) | BIT(27) | BIT(28))),
		VFE_DBG_INFO_WITH_IDLE(28, "stats_bayer_rs_throttle",
			0x00000538, (BIT(29) | BIT(30) | BIT(31))),
	},
	{
		VFE_DBG_INFO_WITH_IDLE(0, "stats_bayer_bfw_throttle",
			0x0000053C, (BIT(0) | BIT(1) | BIT(2))),
		VFE_DBG_INFO_WITH_IDLE(4, "stats_awb_bg_awb_throttle",
			0x0000053C, (BIT(3) | BIT(4) | BIT(5))),
		VFE_DBG_INFO_WITH_IDLE(8, "stats_bhist_af_throttle",
			0x0000053C, (BIT(6) | BIT(7) | BIT(8))),
		VFE_DBG_INFO_WITH_IDLE(12, "full_out_throttle",
			0x0000053C, (BIT(9) | BIT(10) | BIT(11))),
		VFE_DBG_INFO_WITH_IDLE(16, "ds4_out_y_throttle",
			0x0000053C, (BIT(12) | BIT(13) | BIT(14))),
		VFE_DBG_INFO_WITH_IDLE(20, "ds4_out_c_throttle",
			0x0000053C, (BIT(15) | BIT(16) | BIT(17))),
		VFE_DBG_INFO_WITH_IDLE(24, "ds16_out_y_throttle",
			0x0000053C, (BIT(18) | BIT(19) | BIT(20))),
		VFE_DBG_INFO_WITH_IDLE(28, "ds16_out_c_throttle",
			0x0000053C, (BIT(21) | BIT(22) | BIT(23))),
	},
	{
		VFE_DBG_INFO_WITH_IDLE(0, "ds2_out_y_throttle",
			0x0000053C, (BIT(24) | BIT(25) | BIT(26))),
		VFE_DBG_INFO_WITH_IDLE(4, "ds2_out_c_throttle",
			0x0000053C, (BIT(27) | BIT(28) | BIT(29))),
		VFE_DBG_INFO_WITH_IDLE(8, "raw_out_throttle",
			0x00000540, (BIT(0) | BIT(1) | BIT(2))),
		VFE_DBG_INFO_WITH_IDLE(12, "fd_out_y_throttle",
			0x00000540, (BIT(3) | BIT(4) | BIT(5))),
		VFE_DBG_INFO_WITH_IDLE(16, "fd_out_c_throttle",
			0x00000540, (BIT(6) | BIT(7) | BIT(8))),
		VFE_DBG_INFO_WITH_IDLE(20, "haf_sad_stats_throttle",
			0x0000053C, BIT(30)),
		VFE_DBG_INFO_WITH_IDLE(24, "haf_caf_stats_throttle",
			0x0000053C, BIT(31)),
		VFE_DBG_INFO_WITH_IDLE(28, "haf_parsed_throttle",
			0x00000540, BIT(9)),
	},
	{
		VFE_DBG_INFO_WITH_IDLE(0, "haf_pre_processed",
			0x00000540, BIT(10)),
		VFE_DBG_INFO(4, "full_out"),
		VFE_DBG_INFO(8, "ubwc_stats"),
		VFE_DBG_INFO(12, "ds4_out_y"),
		VFE_DBG_INFO(16, "ds4_out_c"),
		VFE_DBG_INFO(20, "ds16_out_y"),
		VFE_DBG_INFO(24, "ds16_out_c"),
		VFE_DBG_INFO(28, "ds2_out_y"),
	},
	VFE_DBG_INFO_ARRAY_4bit(
		"ubwc_stats",
		"ds2_out_c",
		"fd_out_y",
		"fd_out_c",
		"raw_out",
		"stats_awb_bg_ae",
		"stats_ae_bhist",
		"stats_awb_bg_tintless"
	),
	{
		VFE_DBG_INFO_WITH_IDLE(0, "stats_awb_bg_alsc",
			0x00000540, (BIT(20) | BIT(21) | BIT(22))),
		VFE_DBG_INFO(4, "stats_throttle_to_bus_awb_bg_awb"),
		VFE_DBG_INFO(8, "stats_throttle_to_bus_bayer_bfw"),
		VFE_DBG_INFO(12, "stats_throttle_to_bus_bhist_af"),
		VFE_DBG_INFO(16, "stats_throttle_to_bus_awb_bg_alsc"),
		VFE_DBG_INFO(20, "stats_throttle_to_bus_bayer_rs"),
		VFE_DBG_INFO(24, "stats_throttle_to_bus_bhist_tmc"),
		VFE_DBG_INFO(28, "stats_throttle_to_bus_sad"),

	},
	VFE_DBG_INFO_ARRAY_4bit(
		"tfe_haf_processed_to_bus",
		"tfe_haf_parsed_to_bus",
		"tfe_stats_throttle_to_bus",
		"rdi0_splitter_to_bus_wr",
		"rdi1_splitter_to_bus_wr",
		"rdi2_splitter_to_bus_wr",
		"rdi3_splitter_to_bus_wr",
		"rdi4_splitter_to_bus_wr"
	),
	{
		VFE_DBG_INFO_WITH_IDLE(0, "stats_bhist_tmc_throttle",
			0x00000540, (BIT(23) | BIT(24) | BIT(25))),
		VFE_DBG_INFO_WITH_IDLE(4, "clc_bls",
			0x00000544, BIT(1)),
		VFE_DBG_INFO(8, "reserved"),
		VFE_DBG_INFO(12, "reserved"),
		VFE_DBG_INFO(16, "reserved"),
		VFE_DBG_INFO(20, "reserved"),
		VFE_DBG_INFO(24, "reserved"),
		VFE_DBG_INFO(28, "reserved"),
	},
	{
		/* needs to be parsed separately, doesn't conform to I, V, R */
		VFE_DBG_INFO(32, "non_ccif_0"),
		VFE_DBG_INFO(32, "non_ccif_0"),
		VFE_DBG_INFO(32, "non_ccif_0"),
		VFE_DBG_INFO(32, "non_ccif_0"),
		VFE_DBG_INFO(32, "non_ccif_0"),
		VFE_DBG_INFO(32, "non_ccif_0"),
		VFE_DBG_INFO(32, "non_ccif_0"),
		VFE_DBG_INFO(32, "non_ccif_0"),
	},
	{
		/* needs to be parsed separately, doesn't conform to I, V, R */
		VFE_DBG_INFO(32, "non_ccif_1"),
		VFE_DBG_INFO(32, "non_ccif_1"),
		VFE_DBG_INFO(32, "non_ccif_1"),
		VFE_DBG_INFO(32, "non_ccif_1"),
		VFE_DBG_INFO(32, "non_ccif_1"),
		VFE_DBG_INFO(32, "non_ccif_1"),
		VFE_DBG_INFO(32, "non_ccif_1"),
		VFE_DBG_INFO(32, "non_ccif_1"),
	},
	{
		/* needs to be parsed separately, doesn't conform to I, V, R */
		VFE_DBG_INFO(32, "non_ccif_2"),
		VFE_DBG_INFO(32, "non_ccif_2"),
		VFE_DBG_INFO(32, "non_ccif_2"),
		VFE_DBG_INFO(32, "non_ccif_2"),
		VFE_DBG_INFO(32, "non_ccif_2"),
		VFE_DBG_INFO(32, "non_ccif_2"),
		VFE_DBG_INFO(32, "non_ccif_2"),
		VFE_DBG_INFO(32, "non_ccif_2"),
	},
	{
		/* needs to be parsed separately, doesn't conform to I, V, R */
		VFE_DBG_INFO(32, "non_ccif_3"),
		VFE_DBG_INFO(32, "non_ccif_3"),
		VFE_DBG_INFO(32, "non_ccif_3"),
		VFE_DBG_INFO(32, "non_ccif_3"),
		VFE_DBG_INFO(32, "non_ccif_3"),
		VFE_DBG_INFO(32, "non_ccif_3"),
		VFE_DBG_INFO(32, "non_ccif_3"),
		VFE_DBG_INFO(32, "non_ccif_3"),
	},
};

static struct cam_vfe_top_ver4_debug_reg_info tfe1080_bayer_dbg_reg_info[
	CAM_TFE_1080_NUM_BAYER_DBG_REG][8] = {
	VFE_DBG_INFO_ARRAY_4bit("test_bus_reserved",
		"test_bus_reserved",
		"test_bus_reserved",
		"test_bus_reserved",
		"test_bus_reserved",
		"test_bus_reserved",
		"test_bus_reserved",
		"test_bus_reserved"
	),
	{
		VFE_DBG_INFO_WITH_IDLE(0, "clc_demux_w0",
			0x0000E510, (BIT(0) | BIT(1) | BIT(2))),
		VFE_DBG_INFO_WITH_IDLE(4, "clc_bpc_pdpc_gic_w0",
			0x0000E510, (BIT(3) | BIT(4) | BIT(5))),
		VFE_DBG_INFO_WITH_IDLE(8, "clc_pdpc_bpc_1d_w0",
			0x0000E510, (BIT(6) | BIT(7) | BIT(8))),
		VFE_DBG_INFO_WITH_IDLE(12, "clc_abf_binc_w0",
			0x0000E510, (BIT(9) | BIT(10) | BIT(11))),
		VFE_DBG_INFO_WITH_IDLE(16, "clc_channel_gains_w0",
			0x0000E510, (BIT(12) | BIT(13) | BIT(14))),
		VFE_DBG_INFO_WITH_IDLE(20, "clc_lsc_w3",
			0x0000E510, (BIT(15) | BIT(16) | BIT(17))),
		VFE_DBG_INFO_WITH_IDLE(24, "clc_fcg_w2",
			0x0000E510, (BIT(18) | BIT(19) | BIT(20))),
		VFE_DBG_INFO_WITH_IDLE(28, "clc_wb_gain_w6",
			0x0000E510, (BIT(21) | BIT(22) | BIT(23))),
	},
	{
		VFE_DBG_INFO_WITH_IDLE(0, "clc_compdecomp_bayer_w0",
			0x0000E510, (BIT(24) | BIT(25) | BIT(26))),
		VFE_DBG_INFO_WITH_IDLE(4, "reserved",
			0x0000E510, BIT(27)),
		VFE_DBG_INFO_WITH_IDLE(8, "clc_univ_channel_gains",
			0x0000E510, BIT(28)),
		VFE_DBG_INFO_WITH_IDLE(12, "clc_qpdr",
			0x0000E510, BIT(29)),
		VFE_DBG_INFO(16, "reserved"),
		VFE_DBG_INFO(20, "reserved"),
		VFE_DBG_INFO(24, "reserved"),
		VFE_DBG_INFO(28, "reserved"),
	},
	VFE_DBG_INFO_ARRAY_4bit(
		"reserved",
		"reserved",
		"reserved",
		"reserved",
		"reserved",
		"reserved",
		"reserved",
		"reserved"
	),
	VFE_DBG_INFO_ARRAY_4bit(
		"reserved",
		"reserved",
		"reserved",
		"reserved",
		"reserved",
		"reserved",
		"reserved",
		"reserved"
	),
	VFE_DBG_INFO_ARRAY_4bit(
		"reserved",
		"reserved",
		"reserved",
		"reserved",
		"reserved",
		"reserved",
		"reserved",
		"reserved"
	),
	{
		/* needs to be parsed separately, doesn't conform to I, V, R */
		VFE_DBG_INFO(32, "non_ccif_0"),
		VFE_DBG_INFO(32, "non_ccif_0"),
		VFE_DBG_INFO(32, "non_ccif_0"),
		VFE_DBG_INFO(32, "non_ccif_0"),
		VFE_DBG_INFO(32, "non_ccif_0"),
		VFE_DBG_INFO(32, "non_ccif_0"),
		VFE_DBG_INFO(32, "non_ccif_0"),
		VFE_DBG_INFO(32, "non_ccif_0"),
	},
	{
		/* needs to be parsed separately, doesn't conform to I, V, R */
		VFE_DBG_INFO(32, "non_ccif_1"),
		VFE_DBG_INFO(32, "non_ccif_1"),
		VFE_DBG_INFO(32, "non_ccif_1"),
		VFE_DBG_INFO(32, "non_ccif_1"),
		VFE_DBG_INFO(32, "non_ccif_1"),
		VFE_DBG_INFO(32, "non_ccif_1"),
		VFE_DBG_INFO(32, "non_ccif_1"),
		VFE_DBG_INFO(32, "non_ccif_1"),
	},
	{
		/* needs to be parsed separately, doesn't conform to I, V, R */
		VFE_DBG_INFO(32, "non_ccif_2"),
		VFE_DBG_INFO(32, "non_ccif_2"),
		VFE_DBG_INFO(32, "non_ccif_2"),
		VFE_DBG_INFO(32, "non_ccif_2"),
		VFE_DBG_INFO(32, "non_ccif_2"),
		VFE_DBG_INFO(32, "non_ccif_2"),
		VFE_DBG_INFO(32, "non_ccif_2"),
		VFE_DBG_INFO(32, "non_ccif_2"),
	},
	{
		/* needs to be parsed separately, doesn't conform to I, V, R */
		VFE_DBG_INFO(32, "non_ccif_3"),
		VFE_DBG_INFO(32, "non_ccif_3"),
		VFE_DBG_INFO(32, "non_ccif_3"),
		VFE_DBG_INFO(32, "non_ccif_3"),
		VFE_DBG_INFO(32, "non_ccif_3"),
		VFE_DBG_INFO(32, "non_ccif_3"),
		VFE_DBG_INFO(32, "non_ccif_3"),
		VFE_DBG_INFO(32, "non_ccif_3"),
	},
};

static struct cam_vfe_top_ver4_diag_reg_info tfe1080_diag_reg_info[] = {
	{
		.bitmask = 0x3FFF,
		.name    = "SENSOR_HBI",
	},
	{
		.bitmask = 0x4000,
		.name    = "SENSOR_NEQ_HBI",
	},
	{
		.bitmask = 0x8000,
		.name    = "SENSOR_HBI_MIN_ERROR",
	},
	{
		.bitmask = 0xFFFFFF,
		.name    = "SENSOR_VBI",
	},
	{
		.bitmask = 0xFFFF,
		.name    = "SENSOR_VBI_IPP_CONTEXT_0",
	},
	{
		.bitmask = 0x10000000,
		.name    = "SENSOR_VBI_IPP_MIN_ERROR",
	},
	{
		.bitmask = 0xFFFF,
		.name    = "SENSOR_VBI_IPP_CONTEXT_1",
	},
	{
		.bitmask = 0xFFFF0000,
		.name    = "SENSOR_VBI_IPP_CONTEXT_2",
	},
	{
		.bitmask = 0xFF,
		.name    = "FRAME_CNT_PPP_PIPE",
	},
	{
		.bitmask = 0xFF00,
		.name    = "FRAME_CNT_RDI_0_PIPE",
	},
	{
		.bitmask = 0xFF0000,
		.name    = "FRAME_CNT_RDI_1_PIPE",
	},
	{
		.bitmask = 0xFF000000,
		.name    = "FRAME_CNT_RDI_2_PIPE",
	},
	{
		.bitmask = 0xFF,
		.name    = "FRAME_CNT_RDI_3_PIPE",
	},
	{
		.bitmask = 0xFF00,
		.name    = "FRAME_CNT_RDI_4_PIPE",
	},
	{
		.bitmask = 0xFF,
		.name    = "FRAME_CNT_IPP_CONTEXT0_PIPE",
	},
	{
		.bitmask = 0xFF00,
		.name    = "FRAME_CNT_IPP_CONTEXT1_PIPE",
	},
	{
		.bitmask = 0xFF0000,
		.name    = "FRAME_CNT_IPP_CONTEXT2_PIPE",
	},
	{
		.bitmask = 0xFF000000,
		.name    = "FRAME_CNT_IPP_ALL_CONTEXT_PIPE",
	},
};

static struct cam_vfe_top_ver4_diag_reg_fields tfe1080_diag_sensor_field[] = {
	{
		.num_fields = 3,
		.field      = &tfe1080_diag_reg_info[0],
	},
	{
		.num_fields = 1,
		.field      = &tfe1080_diag_reg_info[3],
	},
	{
		.num_fields = 2,
		.field      = &tfe1080_diag_reg_info[4],
	},
	{
		.num_fields = 2,
		.field      = &tfe1080_diag_reg_info[6],
	},
};

static struct cam_vfe_top_ver4_diag_reg_fields tfe1080_diag_frame_field[] = {
	{
		.num_fields = 4,
		.field      = &tfe1080_diag_reg_info[8],
	},
	{
		.num_fields = 2,
		.field      = &tfe1080_diag_reg_info[12],
	},
	{
		.num_fields = 4,
		.field      = &tfe1080_diag_reg_info[14],
	},
};

static struct cam_vfe_ver4_fcg_module_info tfe1080_fcg_module_info = {
	.max_fcg_ch_ctx                      = 3,
	.max_fcg_predictions                 = 3,
	.fcg_index_shift                     = 16,
	.max_reg_val_pair_size               = 6,
	.fcg_type_size                       = 2,
	.fcg_phase_index_cfg_0               = 0x00010470,
	.fcg_phase_index_cfg_1               = 0x00010474,
	.fcg_reg_ctxt_shift                  = 0x0,
	.fcg_reg_ctxt_sel                    = 0x000105F4,
	.fcg_reg_ctxt_mask                   = 0x7,
};

static struct cam_vfe_top_ver4_hw_info tfe1080_top_hw_info = {
	.common_reg = &tfe1080_top_common_reg,
	.vfe_full_hw_info = {
		.common_reg     = &tfe1080_top_common_reg,
		.reg_data       = &tfe1080_ipp_common_reg_data,
	},
	.pdlib_hw_info = {
		.common_reg     = &tfe1080_top_common_reg,
		.reg_data       = &tfe1080_pdlib_reg_data,
	},
	.rdi_hw_info            = tfe1080_rdi_hw_info_arr,
	.wr_client_desc         = tfe1080_wr_client_desc,
	.ipp_module_desc        = tfe1080_ipp_mod_desc,
	.bayer_module_desc      = tfe1080_bayer_mod_desc,
	.num_mux = 7,
	.mux_type = {
		CAM_VFE_CAMIF_VER_4_0,
		CAM_VFE_RDI_VER_1_0,
		CAM_VFE_RDI_VER_1_0,
		CAM_VFE_RDI_VER_1_0,
		CAM_VFE_RDI_VER_1_0,
		CAM_VFE_RDI_VER_1_0,
		CAM_VFE_PDLIB_VER_1_0,
	},
	.num_path_port_map = 3,
	.path_port_map = {
		{CAM_ISP_HW_VFE_IN_PDLIB, CAM_ISP_IFE_OUT_RES_2PD},
		{CAM_ISP_HW_VFE_IN_PDLIB, CAM_ISP_IFE_OUT_RES_PREPROCESS_2PD},
		{CAM_ISP_HW_VFE_IN_PDLIB, CAM_ISP_IFE_OUT_RES_PDAF_PARSED_DATA},
	},
	.num_rdi                         = ARRAY_SIZE(tfe1080_rdi_hw_info_arr),
	.num_top_errors                  = ARRAY_SIZE(tfe1080_top_irq_err_desc),
	.top_err_desc                    = tfe1080_top_irq_err_desc,
	.num_pdaf_violation_errors       = ARRAY_SIZE(tfe1080_haf_violation_desc),
	.pdaf_violation_desc             = tfe1080_haf_violation_desc,
	.top_debug_reg_info              = &tfe1080_top_dbg_reg_info,
	.bayer_debug_reg_info            = &tfe1080_bayer_dbg_reg_info,
	.pdaf_lcr_res_mask               = tfe1080_pdaf_haf_res_mask,
	.num_pdaf_lcr_res                = ARRAY_SIZE(tfe1080_pdaf_haf_res_mask),
	.fcg_module_info                 = &tfe1080_fcg_module_info,
	.fcg_mc_supported                = true,
	.diag_sensor_info                = tfe1080_diag_sensor_field,
	.diag_frame_info                 = tfe1080_diag_frame_field,
};

static struct cam_irq_register_set tfe1080_bus_irq_reg[2] = {
	{
		.mask_reg_offset   = 0x00001018,
		.clear_reg_offset  = 0x00001020,
		.status_reg_offset = 0x00001028,
		.set_reg_offset    = 0x00001050,
	},
	{
		.mask_reg_offset   = 0x0000101C,
		.clear_reg_offset  = 0x00001024,
		.status_reg_offset = 0x0000102C,
		.set_reg_offset    = 0x00001054,
	},
};

static struct cam_vfe_bus_ver3_reg_offset_ubwc_client
	tfe1080_ubwc_regs = {
	.meta_addr        = 0x00000040,
	.meta_cfg         = 0x00000044,
	.mode_cfg         = 0x00000048,
	.stats_ctrl       = 0x0000004C,
	.ctrl_2           = 0x00000050,
	.lossy_thresh0    = 0x00000054,
	.lossy_thresh1    = 0x00000058,
	.off_lossy_var    = 0x0000005C,
	.bw_limit         = 0x0000001C,
	.ubwc_comp_en_bit = BIT(1),
};

static uint32_t tfe1080_out_port_mid[][12] = {
	{56},
	{57},
	{58},
	{59},
	{60},
	{32, 34, 36, 33, 35, 37},
	{44, 46, 48, 45, 47, 49, 50, 52, 54, 51, 53, 55},
	{38, 40, 42, 39, 41, 43, 44, 46, 48, 45, 47, 49},
	{32, 34, 36, 33, 35, 37, 38, 40, 42, 39, 41, 43},
	{56, 57, 58},
	{50, 52, 54, 51, 53, 55},
	{32, 33, 34},
	{35, 36, 37},
	{38, 39, 40},
	{41, 42, 43},
	{44, 45, 46},
	{47, 48, 49},
	{50, 51, 52},
	{53, 54, 55},
	{56, 57, 58},
	{59},
	{61, 62},
	{60},
	{59},
};

static struct cam_vfe_bus_ver3_err_irq_desc tfe1080_bus_irq_err_desc[][32] = {
	{
		{
			.bitmask = BIT(26),
			.err_name = "IPCC_FENCE_DATA_ERR",
			.desc = "IPCC or FENCE Data was not available in the Input Fifo",
		},
		{
			.bitmask = BIT(27),
			.err_name = "IPCC_FENCE_ADDR_ERR",
			.desc = "IPCC or FENCE address fifo was empty and read was attempted",
		},
		{
			.bitmask = BIT(28),
			.err_name = "CONS_VIOLATION",
			.desc = "Programming of software registers violated the constraints",
		},
		{
			.bitmask = BIT(30),
			.err_name = "VIOLATION",
			.desc = "Client has a violation in ccif protocol at input",
		},
		{
			.bitmask = BIT(31),
			.err_name = "IMAGE_SIZE_VIOLATION",
			.desc = "Programmed image size is not same as image size from the CCIF",
		},
	},
	{
		{
			.bitmask = BIT(28),
			.err_name = "EARLY_DONE",
			.desc = "Early Buf done irq for client 20 (STATS_BAF)",
		},
		{
			.bitmask = BIT(29),
			.err_name = "EARLY_DONE",
			.desc = "Early Buf done irq for client 21 (DUAL_PD)",
		},
	},
};

static uint32_t tfe1080_num_bus_irq_err_desc[] = {
	ARRAY_SIZE(tfe1080_bus_irq_err_desc[0]),
	ARRAY_SIZE(tfe1080_bus_irq_err_desc[1]),
};

static struct cam_vfe_bus_ver3_hw_info tfe1080_bus_hw_info = {
	.common_reg = {
		.hw_version                       = 0x00001000,
		.cgc_ovd                          = 0x00001008,
		.ctxt_sel                         = 0x00001124,
		.ubwc_static_ctrl                 = 0x00001058,
		.pwr_iso_cfg                      = 0x0000105C,
		.overflow_status_clear            = 0x00001060,
		.ccif_violation_status            = 0x00001064,
		.overflow_status                  = 0x00001068,
		.image_size_violation_status      = 0x00001070,
		.debug_status_top_cfg             = 0x000010F0,
		.debug_status_top                 = 0x000010F4,
		.test_bus_ctrl                    = 0x00001128,
		.mc_read_sel_shift                = 0x5,
		.mc_write_sel_shift               = 0x0,
		.mc_ctxt_mask                     = 0x7,
		.wm_mode_shift                    = 16,
		.wm_mode_val                      = { 0x0, 0x1, 0x2 },
		.wm_en_shift                      = 0,
		.frmheader_en_shift               = 2,
		.virtual_frm_en_shift             = 1,
		.irq_reg_info = {
			.num_registers            = 2,
			.irq_reg_set              = tfe1080_bus_irq_reg,
			.global_irq_cmd_offset    = 0x00001030,
			.global_clear_bitmask     = 0x00000001,
		},
		.num_perf_counters                = 8,
		.perf_cnt_status                  = 0x000010B4,
		.perf_cnt_reg = {
			{
				.perf_cnt_cfg = 0x00001074,
				.perf_cnt_val = 0x00001094,
			},
			{
				.perf_cnt_cfg = 0x00001078,
				.perf_cnt_val = 0x00001098,
			},
			{
				.perf_cnt_cfg = 0x0000107C,
				.perf_cnt_val = 0x0000109C,
			},
			{
				.perf_cnt_cfg = 0x00001080,
				.perf_cnt_val = 0x000010A0,
			},
			{
				.perf_cnt_cfg = 0x00001084,
				.perf_cnt_val = 0x000010A4,
			},
			{
				.perf_cnt_cfg = 0x00001088,
				.perf_cnt_val = 0x000010A8,
			},
			{
				.perf_cnt_cfg = 0x0000108C,
				.perf_cnt_val = 0x000010AC,
			},
			{
				.perf_cnt_cfg = 0x00001090,
				.perf_cnt_val = 0x000010B0,
			},
		},
	},
	.num_client = CAM_TFE_BUS_VER3_1080_MAX_CLIENTS,
	.support_dyn_offset                       = true,
	.client_base                              = 0x1500,
	.client_reg_size                          = 0x100,
	.ubwc_clients_mask                        = 0x10007F,
	.client_offsets = {
			.cfg                      = 0x00000000,
			.image_addr               = 0x00000004,
			.frame_incr               = 0x00000008,
			.image_cfg_0              = 0x0000000C,
			.image_cfg_1              = 0x00000010,
			.image_cfg_2              = 0x00000014,
			.packer_cfg               = 0x00000018,
			.frame_header_addr        = 0x00000020,
			.frame_header_incr        = 0x00000024,
			.frame_header_cfg         = 0x00000028,
			.irq_subsample_period     = 0x00000030,
			.irq_subsample_pattern    = 0x00000034,
			.framedrop_period         = 0x00000038,
			.framedrop_pattern        = 0x0000003C,
			.mmu_prefetch_cfg         = 0x00000060,
			.mmu_prefetch_max_offset  = 0x00000064,
			.system_cache_cfg         = 0x00000068,
			.addr_cfg                 = 0x00000070,
			.ctxt_cfg                 = 0x00000078,
			.addr_status_0            = 0x00000090,
			.addr_status_1            = 0x00000094,
			.addr_status_2            = 0x00000098,
			.addr_status_3            = 0x0000009C,
			.debug_status_cfg         = 0x0000007C,
			.debug_status_0           = 0x00000080,
			.debug_status_1           = 0x00000084,
			.bw_limiter_addr          = 0x0000001C,
			.ubwc_regs                = &tfe1080_ubwc_regs,

	},
	.bus_client_reg = {
		/* BUS Client 0 FULL */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_0,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_TP_10) |
				BIT_ULL(PACKER_FMT_VER3_MIPI10) |
				BIT_ULL(PACKER_FMT_VER3_MIPI12) |
				BIT_ULL(PACKER_FMT_VER3_MIPI14) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_8) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_128) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_10BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_12BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_14BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_16BPP),
			.rcs_en_mask             =  0x200,
		},
		/* BUS Client 1 DS4_Y */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_0,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_TP_10),
		},
		/* BUS Client 2 DS4_C */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_0,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_TP_10),
		},
		/* BUS Client 3 DS16_Y */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_0,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_TP_10),
		},
		/* BUS Client 4 DS16_C */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_0,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_TP_10),
		},
		/* BUS Client 5 DS2_Y */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_0,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_8) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_128) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_10BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_12BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_14BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_16BPP) |
				BIT_ULL(PACKER_FMT_VER3_MIPI10) |
				BIT_ULL(PACKER_FMT_VER3_TP_10),
			.rcs_en_mask             =  0x200,
		},
		/* BUS Client 6 DS2_C */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_0,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_8) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_128) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_10BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_12BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_14BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_16BPP) |
				BIT_ULL(PACKER_FMT_VER3_MIPI10) |
				BIT_ULL(PACKER_FMT_VER3_TP_10),

			.rcs_en_mask             =  0x200,
		},
		/* BUS Client 7 FD_Y */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_1,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_8) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_8_LSB_MSB_10_ODD_EVEN) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_8_LSB_MSB_10),
		},
		/* BUS Client 8 FD_C */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_1,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_8) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_8_LSB_MSB_10_ODD_EVEN) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_8_LSB_MSB_10),
		},
		/* BUS Client 9 PIXEL RAW */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_0,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_128) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_10BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_12BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_14BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_16BPP) |
				BIT_ULL(PACKER_FMT_VER3_MIPI10) |
				BIT_ULL(PACKER_FMT_VER3_MIPI12) |
				BIT_ULL(PACKER_FMT_VER3_MIPI14),
		},
		/* BUS Client 10 STATS_AEC_BE */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_2,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_128),
		},
		/* BUS Client 11 STATS_AEC_BHIST */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_2,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_64),
		},
		/* BUS Client 12 STATS_TINTLESS_BG */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_2,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_128),
		},
		/* BUS Client 13 STATS_AWB_BG */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_2,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_128),
		},
		/* BUS Client 14 STATS_AWB_BFW */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_2,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_128),
		},
		/* BUS Client 15 STATS_AF_BHIST */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_2,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_64),
		},
		/* BUS Client 16 STATS_ALSC_BG */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_2,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_128),
		},
		/* BUS Client 17 STATS_FLICKER_BAYERS */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_2,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_32),
		},
		/* BUS Client 18 STATS_TMC_BHIST */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_2,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_64),
		},
		/* BUS Client 19 PDAF_0 */ /* Note: PDAF_SAD == 2PD*/
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_3,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_64),
		},
		/* BUS Client 20 PDAF_1 */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_3,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_128) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_10BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_12BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_14BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_16BPP),
		},
		/* BUS Client 21 PDAF_2 */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_3,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_8) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_128) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_10BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_12BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_14BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_16BPP),
		},
		/* BUS Client 22 PDAF_3 */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_4,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_64),
		},
		/* BUS Client 23 RDI_0 */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_5,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_MIPI10) |
				BIT_ULL(PACKER_FMT_VER3_MIPI12) | BIT_ULL(PACKER_FMT_VER3_MIPI14) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_128) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_8) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_10BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_12BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_14BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_16BPP),
		},
		/* BUS Client 24 RDI_1 */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_6,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_MIPI10) |
				BIT_ULL(PACKER_FMT_VER3_MIPI12) | BIT_ULL(PACKER_FMT_VER3_MIPI14) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_128) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_8) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_10BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_12BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_14BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_16BPP),
		},
		/* BUS Client 25 RDI_2 */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_7,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_MIPI10) |
				BIT_ULL(PACKER_FMT_VER3_MIPI12) | BIT_ULL(PACKER_FMT_VER3_MIPI14) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_128) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_8) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_10BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_12BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_14BPP) |
				BIT_ULL(PACKER_FMT_VER3_PLAIN_16_16BPP),
		},
		/* BUS Client 26 RDI_3 */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_8,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_128),
		},
		/* BUS Client 27 RDI_4 */
		{
			.comp_group               = CAM_VFE_BUS_VER3_COMP_GRP_9,
			.supported_pack_formats   = BIT_ULL(PACKER_FMT_VER3_PLAIN_128),
		},
	},
	.valid_wm_mask   = 0xFFFFFFF,
	.vfe_out_hw_info = {
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_RDI0,
			.max_width     = 16384,
			.max_height    = 16384,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_2,
			.mid           = tfe1080_out_port_mid[0],
			.num_mid       = 1,
			.num_wm        = 1,
			.line_based    = 1,
			.wm_idx        = {
				23,
			},
			.name          = {
				"RDI_0",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_RDI1,
			.max_width     = 16384,
			.max_height    = 16384,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_3,
			.mid           = tfe1080_out_port_mid[1],
			.num_mid       = 1,
			.num_wm        = 1,
			.line_based    = 1,
			.wm_idx        = {
				24,
			},
			.name          = {
				"RDI_1",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_RDI2,
			.max_width     = 16384,
			.max_height    = 16384,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_4,
			.mid           = tfe1080_out_port_mid[2],
			.num_mid       = 1,
			.num_wm        = 1,
			.line_based    = 1,
			.wm_idx        = {
				25,
			},
			.name          = {
				"RDI_2",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_RDI3,
			.max_width     = 16384,
			.max_height    = 16384,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_5,
			.mid           = tfe1080_out_port_mid[3],
			.num_mid       = 1,
			.num_wm        = 1,
			.line_based    = 1,
			.wm_idx        = {
				26,
			},
			.name          = {
				"RDI_3",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_RDI4,
			.max_width     = 16384,
			.max_height    = 16384,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_6,
			.mid           = tfe1080_out_port_mid[4],
			.num_mid       = 1,
			.num_wm        = 1,
			.line_based    = 1,
			.wm_idx        = {
				27,
			},
			.name          = {
				"RDI_4",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_FULL,
			.max_width     = 4672,
			.max_height    = 16384,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_0,
			.mid           = tfe1080_out_port_mid[5],
			.num_mid       = 6,
			.num_wm        = 1,
			.line_based    = 1,
			.mc_based      = true,
			.mc_grp_shift  = 0,
			.wm_idx        = {
				0,
			},
			.name          = {
				"FULL",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_DS4,
			.max_width     = 1168,
			.max_height    = 4096,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_0,
			.mid           = tfe1080_out_port_mid[6],
			.num_mid       = 12,
			.num_wm        = 2,
			.line_based    = 1,
			.mc_based      = true,
			.mc_grp_shift  = 0,
			.wm_idx        = {
				1,
				2,
			},
			.name          = {
				"DS4_Y",
				"DS4_C"
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_DS16,
			.max_width     = 292,
			.max_height    = 1024,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_0,
			.mid           = tfe1080_out_port_mid[7],
			.num_mid       = 12,
			.num_wm        = 2,
			.line_based    = 1,
			.mc_based      = true,
			.mc_grp_shift  = 0,
			.wm_idx        = {
				3,
				4,
			},
			.name          = {
				"DS16_Y",
				"DS16_C",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_DS2,
			.max_width     = 4672,
			.max_height    = 8192,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_0,
			.mid           = tfe1080_out_port_mid[8],
			.num_mid       = 12,
			.num_wm        = 2,
			.line_based    = 1,
			.mc_based      = true,
			.wm_idx        = {
				5,
				6,
			},
			.name          = {
				"DS2_Y",
				"DS2_C",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_FD,
			.max_width     = 9312,
			.max_height    = 16384,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_0,
			.mid           = tfe1080_out_port_mid[9],
			.num_mid       = 3,
			.num_wm        = 2,
			.line_based    = 1,
			.cntxt_cfg_except = true,
			.wm_idx        = {
				7,
				8,
			},
			.name          = {
				"FD_Y",
				"FD_C",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_RAW_DUMP,
			.max_width     = 4672,
			.max_height    = 16384,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_0,
			.mid           = tfe1080_out_port_mid[10],
			.num_mid       = 2,
			.num_wm        = 1,
			.line_based    = 1,
			.mc_based      = true,
			.mc_grp_shift  = 0,
			.wm_idx        = {
				9,
			},
			.name          = {
				"PIXEL_RAW",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_STATS_AEC_BE,
			.max_width     = -1,
			.max_height    = -1,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_0,
			.mid           = tfe1080_out_port_mid[11],
			.num_mid       = 3,
			.num_wm        = 1,
			.mc_based      = true,
			.mc_grp_shift  = 4,
			.wm_idx        = {
				10,
			},
			.name          = {
				"STATS_AEC_BE",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_STATS_AEC_BHIST,
			.max_width     = -1,
			.max_height    = -1,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_0,
			.mid           = tfe1080_out_port_mid[12],
			.num_mid       = 3,
			.num_wm        = 1,
			.mc_based      = true,
			.mc_grp_shift  = 4,
			.wm_idx        = {
				11,
			},
			.name          = {
				"STATS_BHIST",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_STATS_TL_BG,
			.max_width     = -1,
			.max_height    = -1,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_0,
			.mid           = tfe1080_out_port_mid[13],
			.num_mid       = 3,
			.num_wm        = 1,
			.mc_based      = true,
			.mc_grp_shift  = 4,
			.wm_idx        = {
				12,
			},
			.name          = {
				"STATS_TL_BG",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_STATS_AWB_BG,
			.max_width     = -1,
			.max_height    = -1,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_0,
			.mid           = tfe1080_out_port_mid[14],
			.num_mid       = 3,
			.num_wm        = 1,
			.mc_based      = true,
			.mc_grp_shift  = 4,
			.wm_idx        = {
				13,
			},
			.name          = {
				"STATS_AWB_BG",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_AWB_BFW,
			.max_width     = -1,
			.max_height    = -1,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_0,
			.mid           = tfe1080_out_port_mid[15],
			.num_mid       = 3,
			.num_wm        = 1,
			.mc_based      = true,
			.mc_grp_shift  = 4,
			.wm_idx        = {
				14,
			},
			.name          = {
				"AWB_BFW",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_STATS_AF_BHIST,
			.max_width     = -1,
			.max_height    = -1,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_0,
			.mid           = tfe1080_out_port_mid[16],
			.num_mid       = 3,
			.num_wm        = 1,
			.mc_based      = true,
			.mc_grp_shift  = 4,
			.wm_idx        = {
				15,
			},
			.name          = {
				"AF_BHIST",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_STATS_ALSC,
			.max_width     = -1,
			.max_height    = -1,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_0,
			.mid           = tfe1080_out_port_mid[17],
			.num_mid       = 3,
			.num_wm        = 1,
			.mc_based      = true,
			.mc_grp_shift  = 4,
			.wm_idx        = {
				16,
			},
			.name          = {
				"ALSC_BG",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_STATS_BAYER_RS,
			.max_width     = -1,
			.max_height    = -1,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_0,
			.mid           = tfe1080_out_port_mid[18],
			.num_mid       = 3,
			.num_wm        = 1,
			.mc_based      = true,
			.mc_grp_shift  = 4,
			.wm_idx        = {
				17,
			},
			.name          = {
				"STATS_RS",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_STATS_TMC_BHIST,
			.max_width     = -1,
			.max_height    = -1,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_0,
			.mid           = tfe1080_out_port_mid[19],
			.num_mid       = 3,
			.num_wm        = 1,
			.mc_based      = true,
			.mc_grp_shift  = 4,
			.wm_idx        = {
				18,
			},
			.name          = {
				"STATS_TMC_BHIST",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_2PD,
			.max_width     = 14592,
			.max_height    = 4096,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_1,
			.mid           = tfe1080_out_port_mid[20],
			.num_mid       = 1,
			.num_wm        = 1,
			.wm_idx        = {
				19,
			},
			.name          = {
				"PDAF_0_2PD",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_PREPROCESS_2PD,
			.max_width     = 1920,
			.max_height    = 1080,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_1,
			.mid           = tfe1080_out_port_mid[21],
			.num_mid       = 2,
			.num_wm        = 1,
			.line_based    = 1,
			.wm_idx        = {
				20,
			},
			.name          = {
				"PDAF_1_PREPROCESS_2PD",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_PDAF_PARSED,
			.max_width     = -1,
			.max_height    = -1,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_1,
			.mid           = tfe1080_out_port_mid[22],
			.num_mid       = 1,
			.num_wm        = 1,
			.line_based    = 1,
			.wm_idx        = {
				21,
			},
			.name          = {
				"PDAF_2_PARSED_DATA",
			},
		},
		{
			.vfe_out_type  = CAM_VFE_BUS_VER3_VFE_OUT_STATS_CAF,
			.max_width     = -1,
			.max_height    = -1,
			.source_group  = CAM_VFE_BUS_VER3_SRC_GRP_1,
			.mid           = tfe1080_out_port_mid[23],
			.num_mid       = 1,
			.num_wm        = 1,
			.mc_based      = false,
			.mc_grp_shift  = 4,
			.wm_idx        = {
				22,
			},
			.name          = {
				"STATS_CAF",
			},
		},
	},
	.num_cons_err = 32,
	.constraint_error_list = {
		{
			.bitmask = BIT(0),
			.error_description = "PPC 1x1 input Not Supported"
		},
		{
			.bitmask = BIT(1),
			.error_description = "PPC 1x2 input Not Supported"
		},
		{
			.bitmask = BIT(2),
			.error_description = "PPC 2x1 input Not Supported"
		},
		{
			.bitmask = BIT(3),
			.error_description = "PPC 2x2 input Not Supported"
		},
		{
			.bitmask = BIT(4),
			.error_description = "Pack 8 BPP format Not Supported"
		},
		{
			.bitmask = BIT(5),
			.error_description = "Pack 16 BPP format Not Supported"
		},
		{
			.bitmask = BIT(6),
			.error_description = "Pack 24 BPP format Not Supported"
		},
		{
			.bitmask = BIT(7),
			.error_description = "Pack 32 BPP format Not Supported"
		},
		{
			.bitmask = BIT(8),
			.error_description = "Pack 64 BPP format Not Supported"
		},
		{
			.bitmask = BIT(9),
			.error_description = "Pack MIPI 20 format Not Supported"
		},
		{
			.bitmask = BIT(10),
			.error_description = "Pack MIPI 14 format Not Supported"
		},
		{
			.bitmask = BIT(11),
			.error_description = "Pack MIPI 12 format Not Supported"
		},
		{
			.bitmask = BIT(12),
			.error_description = "Pack MIPI 10 format Not Supported"
		},
		{
			.bitmask = BIT(13),
			.error_description = "Pack 128 BPP format Not Supported"
		},
		{
			.bitmask = BIT(14),
			.error_description = "UBWC P016 format Not Supported"
		},
		{
			.bitmask = BIT(15),
			.error_description = "UBWC P010 format Not Supported"
		},
		{
			.bitmask = BIT(16),
			.error_description = "UBWC NV12 format Not Supported"
		},
		{
			.bitmask = BIT(17),
			.error_description = "UBWC NV12 4R format Not Supported"
		},
		{
			.bitmask = BIT(18),
			.error_description = "UBWC TP10 format Not Supported"
		},
		{
			.bitmask = BIT(19),
			.error_description = "Frame based Mode Not Supported"
		},
		{
			.bitmask = BIT(20),
			.error_description = "Index based Mode Not Supported"
		},
		{
			.bitmask = BIT(21),
			.error_description = "FIFO image addr unalign"
		},
		{
			.bitmask = BIT(22),
			.error_description = "FIFO ubwc addr unalign"
		},
		{
			.bitmask = BIT(23),
			.error_description = "FIFO framehdr addr unalign"
		},
		{
			.bitmask = BIT(24),
			.error_description = "Image address unalign"
		},
		{
			.bitmask = BIT(25),
			.error_description = "UBWC address unalign"
		},
		{
			.bitmask = BIT(26),
			.error_description = "Frame Header address unalign"
		},
		{
			.bitmask = BIT(27),
			.error_description = "Stride unalign"
		},
		{
			.bitmask = BIT(28),
			.error_description = "X Initialization unalign"
		},
		{
			.bitmask = BIT(29),
			.error_description = "Image Width unalign",
		},
		{
			.bitmask = BIT(30),
			.error_description = "Image Height unalign",
		},
		{
			.bitmask = BIT(31),
			.error_description = "Meta Stride unalign",
		},
	},
	.num_bus_errors        = tfe1080_num_bus_irq_err_desc,
	.bus_err_desc          = &tfe1080_bus_irq_err_desc,
	.num_comp_grp          = 10,
	.support_consumed_addr = true,
	.mc_comp_done_mask = {
		BIT(24), 0x0, BIT(25), 0x0, 0x0, 0x0,
		0x0, 0x0, 0x0, 0x0,
	},
	.comp_done_mask = {
		(BIT(0) | BIT(1) | BIT(2)), BIT(3), (BIT(4) | BIT(5) | BIT(6)), BIT(7),
		BIT(8), BIT(16), BIT(17), BIT(18), BIT(19), BIT(20),
	},
	.top_irq_shift         = 0,
	.max_out_res           = CAM_ISP_IFE_OUT_RES_BASE + 43,
	.pack_align_shift      = 5,
	.max_bw_counter_limit  = 0xFF,
	.skip_regdump          = true,
	.skip_regdump_start_offset = 0x1000,
	.skip_regdump_stop_offset = 0x309C,
};

static struct cam_vfe_irq_hw_info tfe1080_irq_hw_info = {
	.reset_mask    = 0,
	.supported_irq = CAM_VFE_HW_IRQ_CAP_EXT_CSID,
	.top_irq_reg   = &tfe1080_top_irq_reg_info,
};

static struct cam_vfe_hw_info cam_tfe1080_hw_info = {
	.irq_hw_info                  = &tfe1080_irq_hw_info,

	.bus_version                   = CAM_VFE_BUS_VER_3_0,
	.bus_hw_info                   = &tfe1080_bus_hw_info,

	.top_version                   = CAM_VFE_TOP_VER_4_0,
	.top_hw_info                   = &tfe1080_top_hw_info,
};
#endif /* _CAM_TFE1080_H_ */
