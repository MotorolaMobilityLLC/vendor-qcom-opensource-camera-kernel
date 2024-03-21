# Settings for compiling tank camera architecture
# Localized KCONFIG settings
CONFIG_CCI_DEBUG_INTF := y
ccflags-y += -DCONFIG_CCI_DEBUG_INTF=1
CONFIG_CAM_SENSOR_PROBE_DEBUG := y
ccflags-y += -DCONFIG_CAM_SENSOR_PROBE_DEBUG=1

# Flags to pass into C preprocessor
CONFIG_MOT_OIS_DW9784_DRIVER := y
CONFIG_MOT_OIS_EARLY_UPGRADE_FW := y
ccflags-y += -DCONFIG_MOT_OIS_DW9784_DRIVER=1
ccflags-y += -DCONFIG_MOT_OIS_EARLY_UPGRADE_FW=1