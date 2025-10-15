/*
 * Copyright (C) 2023 Motorola Mobility LLC.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/firmware.h>
#include "cam_ois_core.h"
#include "cam_ois_soc.h"

#define REG_APP_VER (0x1008)
#define REG_OIS_STS (0x0001)
#define REG_OIS_CTRL (0x0000)
#define REG_FWUP_CTRL (0x1000)
#define REG_DATA_BUF (0x1100)
#define REG_FWUP_CRC (0x1010)
#define REG_FWUP_ERR (0x1001)
#define REG_REF_CRC (0x1014)
#define REG_BOOT_VER (0x1004)

#define STATE_READY (0x01)
#define OIS_OFF (0x00)
#define NO_ERROR (0x00)
#define RESET_REQ (0x80)
#define FWUP_CTRL_256_SET (0x07)
#define SECURE_ROOT (0x40)

#define SEM1218S_CHUNCK_SIZE (256)
#define POLYNOMIAL (0x04C11DB7)

#if defined(CONFIG_MOT_DRV_OIS_MODIFY_VDDIO)
#define REG_BOOT_LOCK (0x102C)
#define BOOT_KEY (0xF01DC0DE)

#define REG_BOOT_CONFIG (0x1002)
#define BOOT_VDDIO_1_8V (0x41)
#define BOOT_VDDIO_1_2V (0x61)
#define REG_VDDIO_CHECK (0x1031)
#define VDDIO_1_8V (0x00)
#define VDDIO_1_2V (0x01)
#endif

#ifdef CONFIG_MOT_DRV_OIS_DEINIT
#define REG_SPI_MODE (0x0603)
#define REG_GPWR_CTRL (0x0602)
#endif

//#define SEM1218S_OIS_DEBUG

static int32_t sem1218s_cci_write_u32_little_endian(struct camera_io_master * io_master_info, uint16_t reg, uint32_t val)
{
	int32_t rc = 0;
	struct cam_sensor_i2c_reg_array reg_setting;
	struct cam_sensor_i2c_reg_setting wr_setting;

	uint32_t send = 0;
	send = ((val & 0xFF000000) >> 24) |
		((val & 0x00FF0000) >> 8) |
		((val & 0x0000FF00) << 8) |
		((val & 0x000000FF) << 24);

	CAM_INFO(CAM_OIS, "val 0x%x, send 0x%x", val, send);

	reg_setting.reg_addr = reg;
	reg_setting.reg_data = send;
	reg_setting.delay = 0;
	reg_setting.data_mask = 0;

	wr_setting.reg_setting = &reg_setting;
	wr_setting.size = 1;
	wr_setting.addr_type = CAMERA_SENSOR_I2C_TYPE_WORD;
	wr_setting.data_type = CAMERA_SENSOR_I2C_TYPE_DWORD;
	wr_setting.delay = 0;

	rc = camera_io_dev_write(io_master_info, &wr_setting);
	return rc;
}

static int32_t sem1218s_cci_write_byte(struct camera_io_master * io_master_info, uint16_t reg, uint8_t val)
{
	int32_t rc = 0;
	struct cam_sensor_i2c_reg_array reg_setting;
	struct cam_sensor_i2c_reg_setting wr_setting;

	reg_setting.reg_addr = reg;
	reg_setting.reg_data = val;
	reg_setting.delay = 0;
	reg_setting.data_mask = 0;

	wr_setting.reg_setting = &reg_setting;
	wr_setting.size = 1;
	wr_setting.addr_type = CAMERA_SENSOR_I2C_TYPE_WORD;
	wr_setting.data_type = CAMERA_SENSOR_I2C_TYPE_BYTE;
	wr_setting.delay = 0;

	rc = camera_io_dev_write(io_master_info, &wr_setting);
	return rc;
}

static int32_t sem1218s_cci_read_byte(struct camera_io_master * io_master_info, uint16_t reg, uint8_t *val)
{
	int32_t rc = 0;
	uint32_t regVal = 0;
	rc = camera_io_dev_read(io_master_info, reg, &regVal, CAMERA_SENSOR_I2C_TYPE_WORD, CAMERA_SENSOR_I2C_TYPE_BYTE, false);
	if (!rc) {
		*val = (uint8_t)regVal;
	}
	return rc;
}

static int32_t sem1218s_cci_read_u32_little_endian(struct camera_io_master * io_master_info, uint16_t reg, uint32_t *receive)
{
	int32_t rc = 0;
	uint32_t val = 0;
	rc = camera_io_dev_read(io_master_info, reg, &val, CAMERA_SENSOR_I2C_TYPE_WORD, CAMERA_SENSOR_I2C_TYPE_DWORD, false);
	if (!rc) {
		*receive = 	((val & 0xFF000000) >> 24)|
				((val & 0x00FF0000) >> 8) |
				((val & 0x0000FF00) << 8) |
				((val & 0x000000FF) << 24);

		CAM_INFO(CAM_OIS, "val 0x%x, receive 0x%x", val, *receive);
	}
	return rc;
}

static void sem1218s_delay_ms(uint32_t ms)
{
	usleep_range(ms*1000, ms*1000+10);
	return;
}

#ifdef CONFIG_MOT_DRV_OIS_DEINIT
void sem1218s_deinit_gyro(struct camera_io_master * io_master_info)
{
	uint8_t reg_spi_mode = 0;
	uint8_t reg_gpwr_ctrl = 0;
	int32_t rc = 0;

	rc = sem1218s_cci_read_byte(io_master_info, REG_SPI_MODE, &reg_spi_mode);
	if (rc < 0) {
		CAM_ERR(CAM_OIS, "read REG_SPI_MODE failed, rc %d", rc);
	}
	rc = sem1218s_cci_read_byte(io_master_info, REG_GPWR_CTRL, &reg_gpwr_ctrl);
	if (rc < 0) {
		CAM_ERR(CAM_OIS, "read REG_GPWR_CTRL failed, rc %d", rc);
	}

	CAM_INFO(CAM_OIS, "[sem1218s_deinit_gyro] reg_spi_mode=0x%X, reg_gpwr_ctrl=0x%X", reg_spi_mode, reg_gpwr_ctrl);

	//SPI Master mode
	if(reg_spi_mode == 0x00)
	{
		rc = sem1218s_cci_write_byte(io_master_info, REG_GPWR_CTRL, 0x00);
		if (rc < 0) {
			CAM_ERR(CAM_OIS, "write REG_GPWR_CTRL failed, rc %d", rc);
		}
	}
}
#endif

static uint32_t sem1218s_calculateCRC32(uint8_t *data, uint32_t size)
{
	uint32_t crc_table[SEM1218S_CHUNCK_SIZE];
	uint32_t i,j,crc_accum;

	for(i = 0; i < SEM1218S_CHUNCK_SIZE; i++) {
		crc_accum = i << 24;
		for(j = 0; j < 8; j++) {
			if (crc_accum & 0x80000000ul)
				crc_accum = (crc_accum << 1) ^ POLYNOMIAL;
			else
				crc_accum = crc_accum << 1;
		}
		crc_table[i] = crc_accum;
	}

	crc_accum = 0;
	for(j = 0; j < size; j++) {
		i = ((uint32_t)(crc_accum >> 24) ^ *data ++) & 0xff;
		crc_accum = (crc_accum << 8) ^ crc_table[i];
	}

	return crc_accum;
}

#if defined(CONFIG_MOT_DRV_OIS_MODIFY_VDDIO)
static int cam_ois_power_up_vddio(struct cam_ois_ctrl_t *o_ctrl)
{
	int                                     rc = 0;
	struct cam_hw_soc_info                 *soc_info = &o_ctrl->soc_info;
	struct cam_ois_soc_private             *soc_private;
	struct cam_sensor_power_ctrl_t         *power_info;
	struct completion                      *i3c_probe_completion = NULL;

	soc_private = (struct cam_ois_soc_private *)o_ctrl->soc_info.soc_private;
	power_info = &soc_private->power_info;

	if ((power_info->power_setting == NULL) &&
		(power_info->power_down_setting == NULL)) {
		CAM_INFO(CAM_OIS,
			"Using default power settings");
		rc = cam_ois_construct_default_power_setting(power_info);
		if (rc < 0) {
			CAM_ERR(CAM_OIS,
				"Construct default ois power setting failed.");
			return rc;
		}
	}

	/* Parse and fill vreg params for power up settings */
	rc = msm_camera_fill_vreg_params(
		soc_info,
		power_info->power_setting,
		power_info->power_setting_size);
	if (rc) {
		CAM_ERR(CAM_OIS,
			"failed to fill vreg params for power up rc:%d", rc);
		return rc;
	}

	/* Parse and fill vreg params for power down settings*/
	rc = msm_camera_fill_vreg_params(
		soc_info,
		power_info->power_down_setting,
		power_info->power_down_setting_size);
	if (rc) {
		CAM_ERR(CAM_OIS,
			"failed to fill vreg params for power down rc:%d", rc);
		return rc;
	}

	power_info->dev = soc_info->dev;

	if (o_ctrl->io_master_info.master_type == I3C_MASTER)
		i3c_probe_completion = cam_ois_get_i3c_completion(o_ctrl->soc_info.index);

	rc = cam_sensor_core_power_up(power_info, soc_info, i3c_probe_completion);
	if (rc) {
		CAM_ERR(CAM_OIS, "failed in ois power up rc %d", rc);
		return rc;
	}

	CAM_INFO(CAM_OIS, "OIS Power up successfully");

	rc = camera_io_init(&o_ctrl->io_master_info);
	if (rc) {
		CAM_ERR(CAM_OIS, "cci_init failed: rc: %d", rc);
		goto cci_failure;
	}

	o_ctrl->cam_ois_state = CAM_OIS_CONFIG;

	return rc;
cci_failure:
	if (cam_sensor_util_power_down(power_info, soc_info))
		CAM_ERR(CAM_OIS, "Power Down failed");

	return rc;
}

/**
 * cam_ois_power_down - power down OIS device
 * @o_ctrl:     ctrl structure
 *
 * Returns success or failure
 */
static int cam_ois_power_down_vddio(struct cam_ois_ctrl_t *o_ctrl)
{
	int32_t                         rc = 0;
	struct cam_sensor_power_ctrl_t  *power_info;
	struct cam_hw_soc_info          *soc_info = &o_ctrl->soc_info;
	struct cam_ois_soc_private *soc_private;

	if (!o_ctrl) {
		CAM_ERR(CAM_OIS, "failed: o_ctrl %pK", o_ctrl);
		return -EINVAL;
	}

	soc_private =
		(struct cam_ois_soc_private *)o_ctrl->soc_info.soc_private;
	power_info = &soc_private->power_info;
	soc_info = &o_ctrl->soc_info;

	if (!power_info) {
		CAM_ERR(CAM_OIS, "failed: power_info %pK", power_info);
		return -EINVAL;
	}

	rc = cam_sensor_util_power_down(power_info, soc_info);
	if (rc) {
		CAM_ERR(CAM_OIS, "power down the core is failed:%d", rc);
		return rc;
	}

	CAM_INFO(CAM_OIS, "OIS power down successed");

	camera_io_release(&o_ctrl->io_master_info);
	o_ctrl->cam_ois_state = CAM_OIS_ACQUIRE;

	return rc;
}
#endif

static struct cam_sensor_i2c_reg_array   i2c_register_array[SEM1218S_CHUNCK_SIZE] = {0};
static uint8_t buff[SEM1218S_CHUNCK_SIZE] = {0};
int32_t sem1218s_fw_update(struct cam_ois_ctrl_t *o_ctrl, const struct firmware *fw)
{
	struct cam_sensor_i2c_reg_setting i2c_register_setting = {0};
	struct cam_sensor_i2c_reg_array   *pI2CRegisterArray = NULL;
	uint32_t wr_bytes = 0;
	uint32_t remain_bytes = 0;
	uint8_t *pFwData = NULL;
	uint32_t current_fw_ver = 0;
	uint32_t new_fw_ver = 0;
	uint32_t updated_ver = 0;
	int32_t rc = 0;
	uint8_t reg_val = 0;
	uint32_t crc = 0;
	int32_t i = 0;
#if defined(CONFIG_MOT_DRV_OIS_MODIFY_VDDIO)
	uint8_t reg_vddio = 0xff;
#endif

	if (o_ctrl == NULL) {
		CAM_ERR(CAM_OIS, "Invalid o_ctrl args");
		return -EINVAL;
	}

	if (fw == NULL) {
		CAM_ERR(CAM_OIS, "Invalid fw args");
		return -EINVAL;
	}

	if (fw->size <= 0 || fw->data == NULL) {
		CAM_ERR(CAM_OIS, "FW is not valid( buf:%p, size:%d)", fw->data, fw->size);
		return -EINVAL;
	}

	pFwData = (uint8_t *)fw->data;

	rc = sem1218s_cci_read_u32_little_endian(&(o_ctrl->io_master_info), REG_APP_VER, &current_fw_ver);
	if (rc < 0) {
		CAM_ERR(CAM_OIS, "Read current fw version failed, rc %d", rc);
		return -EINVAL;
	}

	CAM_INFO(CAM_OIS, "OIS current_fw_ver 0x%x, fw->size %d", current_fw_ver, fw->size);

#if defined(CONFIG_MOT_DRV_OIS_MODIFY_VDDIO)
#if defined(CONFIG_VANTAGE_DTB)
	if (current_fw_ver > 0xb) {
		rc = sem1218s_cci_read_byte(&(o_ctrl->io_master_info), REG_VDDIO_CHECK, &reg_vddio);
		if (rc < 0) {
			CAM_ERR(CAM_OIS, "read REG_VDDIO_CHECK failed, rc %d", rc);
			return -EINVAL;
		}
		CAM_INFO(CAM_OIS, "OIS 0x1031 reg_vddio 0x%x", reg_vddio);
		if (reg_vddio == VDDIO_1_8V) {
			goto fw_update;
		} else {
			goto vddio_1p8;
		}
	} else
#elif defined(CONFIG_BLANC_DTB)
	if (current_fw_ver > 0x186a2) {
		rc = sem1218s_cci_read_byte(&(o_ctrl->io_master_info), REG_VDDIO_CHECK, &reg_vddio);
		if (rc < 0) {
			CAM_ERR(CAM_OIS, "read REG_VDDIO_CHECK failed, rc %d", rc);
			return -EINVAL;
		}
		CAM_INFO(CAM_OIS, "OIS 0x1031 reg_vddio 0x%x", reg_vddio);
		if (reg_vddio == VDDIO_1_8V) {
			goto fw_update;
		} else {
			goto vddio_1p8;
		}
	} else
#endif
vddio_1p8:
	{
		new_fw_ver = *(uint32_t *)(pFwData + (fw->size - 12));

		CAM_INFO(CAM_OIS, "OIS new_fw_ver 0x%x", new_fw_ver);

		if (current_fw_ver != 0) {
			reg_val = 0;
			rc = sem1218s_cci_read_byte(&(o_ctrl->io_master_info), REG_OIS_STS, &reg_val);
			CAM_INFO(CAM_OIS, "OIS REG_OIS_STS reg_val 0x%x", reg_val);
			if (rc < 0) {
				CAM_ERR(CAM_OIS, "Read REG_OIS_STS failed, rc %d", rc);
				return -EINVAL;
			}

			if (reg_val != STATE_READY) {
				rc = sem1218s_cci_write_byte(&(o_ctrl->io_master_info), REG_OIS_CTRL, OIS_OFF);
				if (rc < 0) {
					CAM_ERR(CAM_OIS, "Write REG_OIS_CTRL failed, rc %d", rc);
					return -EINVAL;
				}
			}
		}

		rc = sem1218s_cci_write_byte(&(o_ctrl->io_master_info), REG_FWUP_CTRL, (FWUP_CTRL_256_SET | SECURE_ROOT));
		if (rc < 0) {
			CAM_ERR(CAM_OIS, "Write REG_FWUP_CTRL failed, rc %d", rc);
			return -EINVAL;
		}

		sem1218s_delay_ms(200);

		cam_ois_power_down_vddio(o_ctrl);

		rc = cam_ois_power_up_vddio(o_ctrl);
		if (rc) {
			CAM_ERR(CAM_OIS, " OIS Power up failed");
			return -EINVAL;
		}

		rc = sem1218s_cci_write_u32_little_endian(&(o_ctrl->io_master_info), REG_BOOT_LOCK, BOOT_KEY);
		if (rc < 0) {
			CAM_ERR(CAM_OIS, "Write REG_BOOT_LOCK failed, rc %d", rc);
			return -EINVAL;
		}
		rc = sem1218s_cci_write_byte(&(o_ctrl->io_master_info), REG_BOOT_CONFIG, BOOT_VDDIO_1_8V);
		if (rc < 0) {
			CAM_ERR(CAM_OIS, "Write REG_BOOT_CONFIG failed, rc %d", rc);
			return -EINVAL;
		}
		sem1218s_delay_ms(100);
	}

fw_update:

	new_fw_ver = *(uint32_t *)(pFwData + (fw->size - 12));

	CAM_INFO(CAM_OIS, "OIS new_fw_ver 0x%x", new_fw_ver);

	if (current_fw_ver == new_fw_ver ||
		current_fw_ver > new_fw_ver) {
		CAM_INFO(CAM_OIS, "Skip firmware upgrade, current_fw_ver 0x%x, new_fw_ver 0x%x", current_fw_ver, new_fw_ver);
		return 0;
	}

	if (current_fw_ver != 0) {
		reg_val = 0;
		rc = sem1218s_cci_read_byte(&(o_ctrl->io_master_info), REG_OIS_STS, &reg_val);
		CAM_INFO(CAM_OIS, "OIS REG_OIS_STS reg_val 0x%x", reg_val);
		if (rc < 0) {
			CAM_ERR(CAM_OIS, "Read REG_OIS_STS failed, rc %d", rc);
			return -EINVAL;
		}

		if (reg_val != STATE_READY) {
			rc = sem1218s_cci_write_byte(&(o_ctrl->io_master_info), REG_OIS_CTRL, OIS_OFF);
			if (rc < 0) {
				CAM_ERR(CAM_OIS, "Write REG_OIS_CTRL failed, rc %d", rc);
				return -EINVAL;
			}
		}
	}

	rc = sem1218s_cci_write_byte(&(o_ctrl->io_master_info), REG_FWUP_CTRL, (FWUP_CTRL_256_SET | SECURE_ROOT));
	if (rc < 0) {
		CAM_ERR(CAM_OIS, "Write REG_FWUP_CTRL failed, rc %d", rc);
		return -EINVAL;
	}

	sem1218s_delay_ms(200);

	remain_bytes = fw->size;

	CAM_INFO(CAM_OIS, "OIS FW download start, fw->size %d", fw->size);

	while (remain_bytes) {
		pI2CRegisterArray = i2c_register_array;
		wr_bytes = (remain_bytes >= SEM1218S_CHUNCK_SIZE) ? SEM1218S_CHUNCK_SIZE : remain_bytes;
		remain_bytes -= wr_bytes;
		i2c_register_setting.addr_type = CAMERA_SENSOR_I2C_TYPE_WORD;
		i2c_register_setting.data_type = CAMERA_SENSOR_I2C_TYPE_BYTE;
		i2c_register_setting.reg_setting = i2c_register_array;
		i2c_register_setting.size = wr_bytes;

		for (i = 0; (i < wr_bytes) && (pFwData != NULL) && (pI2CRegisterArray != NULL) && (i < SEM1218S_CHUNCK_SIZE); i++) {
			pI2CRegisterArray->reg_addr = REG_DATA_BUF;
			pI2CRegisterArray->reg_data = *pFwData;
			buff[i] = *pFwData;
			pI2CRegisterArray->delay = 0;
			pI2CRegisterArray->data_mask = 0;

			pI2CRegisterArray++;
			pFwData++;
		}

		rc = camera_io_dev_write_continuous(&(o_ctrl->io_master_info), &i2c_register_setting, CAM_SENSOR_I2C_WRITE_BURST);
		if (rc < 0) {
			CAM_ERR(CAM_OIS, "FW Download error. rc (%d)", rc);
			return -EINVAL;
		}
		sem1218s_delay_ms(10);
	}

	crc = sem1218s_calculateCRC32((uint8_t *)fw->data, fw->size);
	CAM_INFO(CAM_OIS, "OIS FW crc 0x%x", crc);

	rc = sem1218s_cci_write_u32_little_endian(&(o_ctrl->io_master_info), REG_FWUP_CRC, crc);
	if (rc < 0) {
		CAM_ERR(CAM_OIS, "Write REG_FWUP_CHKSUM failed, rc %d", rc);
		return -EINVAL;
	}
	sem1218s_delay_ms(200);

	reg_val = 0;
	rc = sem1218s_cci_read_byte(&(o_ctrl->io_master_info), REG_FWUP_ERR, &reg_val);
	if (rc < 0) {
		CAM_ERR(CAM_OIS, "Read REG_FWUP_ERR failed, rc %d", rc);
		return -EINVAL;
	}

	if (reg_val != NO_ERROR) {
		CAM_ERR(CAM_OIS, "OIS FW download Error 0x%x", reg_val);
		return -EINVAL;
	}

	rc = sem1218s_cci_write_byte(&(o_ctrl->io_master_info), REG_FWUP_CTRL, RESET_REQ);
	if (rc < 0) {
		CAM_ERR(CAM_OIS, "Write REG_FWUP_CTRL failed, rc %d", rc);
		return -EINVAL;
	}
	sem1218s_delay_ms(200);

	rc = sem1218s_cci_read_u32_little_endian(&(o_ctrl->io_master_info), REG_APP_VER, &updated_ver);
	if (rc < 0) {
		CAM_ERR(CAM_OIS, "Read updated_ver fw version failed, rc %d", rc);
		return -EINVAL;
	}

	CAM_INFO(CAM_OIS, "OIS updated_ver 0x%x", updated_ver);

	if (updated_ver != new_fw_ver) /* Compare updated_ver and new_fw_ver */
	{
		CAM_ERR(CAM_OIS, "OIS FW download Error in FW version");
		return -EINVAL;
	}

	CAM_INFO(CAM_OIS, "OIS FW download Success done");

	reg_vddio = 0xff;
	rc = sem1218s_cci_read_byte(&(o_ctrl->io_master_info), REG_VDDIO_CHECK, &reg_vddio);
	if (rc < 0) {
		CAM_ERR(CAM_OIS, "Read vddio check register failed, rc %d", rc);
		return -EINVAL;
	}
	CAM_INFO(CAM_OIS, "OIS 0x1031 reg_vddio 0x%x", reg_vddio);

	return 0;
#else
	new_fw_ver = *(uint32_t *)(pFwData + (fw->size - 12));

	if (current_fw_ver == new_fw_ver ||
            current_fw_ver > new_fw_ver) {
		CAM_INFO(CAM_OIS, "Skip firmware upgrade, current_fw_ver 0x%x, new_fw_ver 0x%x", current_fw_ver, new_fw_ver);
		return 0;
	}

	CAM_INFO(CAM_OIS, "OIS new_fw_ver 0x%x", new_fw_ver);

	if (current_fw_ver != 0) {
		reg_val = 0;
		rc = sem1218s_cci_read_byte(&(o_ctrl->io_master_info), REG_OIS_STS, &reg_val);
		if (rc < 0) {
			CAM_ERR(CAM_OIS, "Read REG_OIS_STS failed, rc %d", rc);
			return -EINVAL;
		}

		if (reg_val != STATE_READY) {
			rc = sem1218s_cci_write_byte(&(o_ctrl->io_master_info), REG_OIS_CTRL, OIS_OFF);
			if (rc < 0) {
				CAM_ERR(CAM_OIS, "Write REG_OIS_CTRL failed, rc %d", rc);
				return -EINVAL;
			}
		}
	}

	rc = sem1218s_cci_write_byte(&(o_ctrl->io_master_info), REG_FWUP_CTRL, (FWUP_CTRL_256_SET | SECURE_ROOT));
	if (rc < 0) {
		CAM_ERR(CAM_OIS, "Write REG_FWUP_CTRL failed, rc %d", rc);
		return -EINVAL;
	}
	sem1218s_delay_ms(200);

	remain_bytes = fw->size;

	CAM_INFO(CAM_OIS, "OIS FW download start, fw->size %d", fw->size);

	while (remain_bytes) {
		pI2CRegisterArray = i2c_register_array;
		wr_bytes = (remain_bytes >= SEM1218S_CHUNCK_SIZE) ? SEM1218S_CHUNCK_SIZE : remain_bytes;
		remain_bytes -= wr_bytes;
		i2c_register_setting.addr_type = CAMERA_SENSOR_I2C_TYPE_WORD;
		i2c_register_setting.data_type = CAMERA_SENSOR_I2C_TYPE_BYTE;
		i2c_register_setting.reg_setting = i2c_register_array;
		i2c_register_setting.size = wr_bytes;

		for (i = 0; (i < wr_bytes) && (pFwData != NULL) && (pI2CRegisterArray != NULL) && (i < SEM1218S_CHUNCK_SIZE); i++) {
			pI2CRegisterArray->reg_addr = REG_DATA_BUF;
			pI2CRegisterArray->reg_data = *pFwData;
			buff[i] = *pFwData;
			pI2CRegisterArray->delay = 0;
			pI2CRegisterArray->data_mask = 0;

			pI2CRegisterArray++;
			pFwData++;
		}

		rc = camera_io_dev_write_continuous(&(o_ctrl->io_master_info), &i2c_register_setting, CAM_SENSOR_I2C_WRITE_BURST);
		if (rc < 0) {
			CAM_ERR(CAM_OIS, "FW Download error. rc (%d)", rc);
			return -EINVAL;
		}
		sem1218s_delay_ms(10);
	}

	crc = sem1218s_calculateCRC32((uint8_t *)fw->data, fw->size);
	CAM_INFO(CAM_OIS, "OIS FW crc 0x%x", crc);

	rc = sem1218s_cci_write_u32_little_endian(&(o_ctrl->io_master_info), REG_FWUP_CRC, crc);
	if (rc < 0) {
		CAM_ERR(CAM_OIS, "Write REG_FWUP_CHKSUM failed, rc %d", rc);
		return -EINVAL;
	}
	sem1218s_delay_ms(200);

	reg_val = 0;
	rc = sem1218s_cci_read_byte(&(o_ctrl->io_master_info), REG_FWUP_ERR, &reg_val);
	if (rc < 0) {
		CAM_ERR(CAM_OIS, "Read REG_FWUP_ERR failed, rc %d", rc);
		return -EINVAL;
	}

	if (reg_val != NO_ERROR) {
		CAM_ERR(CAM_OIS, "OIS FW download Error 0x%x", reg_val);
		return -EINVAL;
	}

	rc = sem1218s_cci_write_byte(&(o_ctrl->io_master_info), REG_FWUP_CTRL, RESET_REQ);
	if (rc < 0) {
		CAM_ERR(CAM_OIS, "Write REG_FWUP_CTRL failed, rc %d", rc);
		return -EINVAL;
	}
	sem1218s_delay_ms(200);

	rc = sem1218s_cci_read_u32_little_endian(&(o_ctrl->io_master_info), REG_APP_VER, &updated_ver);
	if (rc < 0) {
		CAM_ERR(CAM_OIS, "Read updated_ver fw version failed, rc %d", rc);
		return -EINVAL;
	}

	CAM_INFO(CAM_OIS, "OIS updated_ver 0x%x", updated_ver);

	if (updated_ver != new_fw_ver) /* Compare updated_ver and new_fw_ver */
	{
		CAM_ERR(CAM_OIS, "OIS FW download Error in FW version");
		return -EINVAL;
	}

	CAM_INFO(CAM_OIS, "OIS FW download Success done");
	return 0;
#endif
}
