F7X2RE_TARGETS += $(TARGET)
FEATURES    = VCP SDCARD_SPI

TARGET_SRC = \
            drivers/accgyro/accgyro_fake.c \
            drivers/barometer/barometer_fake.c \
            drivers/compass/compass_fake.c \
            drivers/accgyro/accgyro_mpu6500.c \
            drivers/accgyro/accgyro_spi_mpu6500.c \
            drivers/barometer/barometer_bmp280.c \
            drivers/barometer/barometer_ms5611.c \
            drivers/compass/compass_hmc5883l.c \
            drivers/compass/compass_lis3mdl.c \
            drivers/max7456.c \
