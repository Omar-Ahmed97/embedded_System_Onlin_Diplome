################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/I2C_Slave_EEPROM/I2C_Slave_EEPROM.c 

OBJS += \
./HAL/I2C_Slave_EEPROM/I2C_Slave_EEPROM.o 

C_DEPS += \
./HAL/I2C_Slave_EEPROM/I2C_Slave_EEPROM.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/I2C_Slave_EEPROM/I2C_Slave_EEPROM.o: ../HAL/I2C_Slave_EEPROM/I2C_Slave_EEPROM.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/learn_in_depth/embedde_System_Onlin_Diplome_Repo/Assignments/Unit8_Interfacing/New folder/Drivers/HAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/I2C_Slave_EEPROM/I2C_Slave_EEPROM.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

