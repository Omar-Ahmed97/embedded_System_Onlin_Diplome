################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/LCD_Driver/lcd_driver.c 

OBJS += \
./HAL/LCD_Driver/lcd_driver.o 

C_DEPS += \
./HAL/LCD_Driver/lcd_driver.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/LCD_Driver/lcd_driver.o: ../HAL/LCD_Driver/lcd_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/learn_in_depth/embedde_System_Onlin_Diplome_Repo/Assignments/Unit7_MCUessentials/New folder/Drivers/HAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/LCD_Driver/lcd_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

