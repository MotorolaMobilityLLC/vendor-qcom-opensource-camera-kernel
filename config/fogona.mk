# Settings for compiling waipio camera architecture

# Localized KCONFIG settings
# Camera: Remove for user build

CONFIG_CAMERA_FLASH_PWM := y
CONFIG_FOGONA_CAMERA_FLASH := y
CONFIG_CAM_SENSOR_PROBE_RETRY := y
CONFIG_CAM_SYNC_MEMORY := y

ifneq (,$(filter userdebug eng, $(TARGET_BUILD_VARIANT)))
CONFIG_CCI_DEBUG_INTF := y
ccflags-y += -DCONFIG_CCI_DEBUG_INTF=1
endif

# Flags to pass into C preprocessor
ccflags-y += -DCONFIG_CAMERA_FLASH_PWM=1
ccflags-y += -DCONFIG_FOGONA_CAMERA_FLASH=1
ccflags-y += -DCONFIG_CAM_SENSOR_PROBE_RETRY=1
ccflags-y += -DCONFIG_CAM_SYNC_MEMORY=1
