F405_TARGETS    += $(TARGET)
FEATURES        += SDCARD_SPI VCP

TARGET_SRC = \
            drivers/accgyro/accgyro_spi_mpu6000.c \
            drivers/max7456.c

ifeq ($(TARGET), MLTYPHF4)
TARGET_SRC += \

endif
