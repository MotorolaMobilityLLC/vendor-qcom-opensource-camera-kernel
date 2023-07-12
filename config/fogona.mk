# Settings for compiling waipio camera architecture

# Localized KCONFIG settings
# Camera: Remove for user build

CONFIG_CAMERA_FLASH_PWM := y

# Flags to pass into C preprocessor
ccflags-y += -DCONFIG_CAMERA_FLASH_PWM=1
