################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32_F103C6_drivers/stm32_F103C6_gpio_driver.c \
../stm32_F103C6_drivers/stm32f103c6_EXTI_driver.c \
../stm32_F103C6_drivers/stm32f103c6_I2C_driver.c \
../stm32_F103C6_drivers/stm32f103c6_RCC_driver.c \
../stm32_F103C6_drivers/stm32f103c6_SPI_driver.c \
../stm32_F103C6_drivers/stm32f103c6_USART_driver.c 

OBJS += \
./stm32_F103C6_drivers/stm32_F103C6_gpio_driver.o \
./stm32_F103C6_drivers/stm32f103c6_EXTI_driver.o \
./stm32_F103C6_drivers/stm32f103c6_I2C_driver.o \
./stm32_F103C6_drivers/stm32f103c6_RCC_driver.o \
./stm32_F103C6_drivers/stm32f103c6_SPI_driver.o \
./stm32_F103C6_drivers/stm32f103c6_USART_driver.o 

C_DEPS += \
./stm32_F103C6_drivers/stm32_F103C6_gpio_driver.d \
./stm32_F103C6_drivers/stm32f103c6_EXTI_driver.d \
./stm32_F103C6_drivers/stm32f103c6_I2C_driver.d \
./stm32_F103C6_drivers/stm32f103c6_RCC_driver.d \
./stm32_F103C6_drivers/stm32f103c6_SPI_driver.d \
./stm32_F103C6_drivers/stm32f103c6_USART_driver.d 


# Each subdirectory must supply rules for building sources it contributes
stm32_F103C6_drivers/stm32_F103C6_gpio_driver.o: ../stm32_F103C6_drivers/stm32_F103C6_gpio_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/learn_in_depth/embedde_System_Onlin_Diplome_Repo/Assignments/Unit8_Interfacing/New folder/Drivers/HAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_F103C6_drivers/stm32_F103C6_gpio_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32_F103C6_drivers/stm32f103c6_EXTI_driver.o: ../stm32_F103C6_drivers/stm32f103c6_EXTI_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/learn_in_depth/embedde_System_Onlin_Diplome_Repo/Assignments/Unit8_Interfacing/New folder/Drivers/HAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_F103C6_drivers/stm32f103c6_EXTI_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32_F103C6_drivers/stm32f103c6_I2C_driver.o: ../stm32_F103C6_drivers/stm32f103c6_I2C_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/learn_in_depth/embedde_System_Onlin_Diplome_Repo/Assignments/Unit8_Interfacing/New folder/Drivers/HAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_F103C6_drivers/stm32f103c6_I2C_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32_F103C6_drivers/stm32f103c6_RCC_driver.o: ../stm32_F103C6_drivers/stm32f103c6_RCC_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/learn_in_depth/embedde_System_Onlin_Diplome_Repo/Assignments/Unit8_Interfacing/New folder/Drivers/HAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_F103C6_drivers/stm32f103c6_RCC_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32_F103C6_drivers/stm32f103c6_SPI_driver.o: ../stm32_F103C6_drivers/stm32f103c6_SPI_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/learn_in_depth/embedde_System_Onlin_Diplome_Repo/Assignments/Unit8_Interfacing/New folder/Drivers/HAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_F103C6_drivers/stm32f103c6_SPI_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32_F103C6_drivers/stm32f103c6_USART_driver.o: ../stm32_F103C6_drivers/stm32f103c6_USART_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/learn_in_depth/embedde_System_Onlin_Diplome_Repo/Assignments/Unit8_Interfacing/New folder/Drivers/HAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_F103C6_drivers/stm32f103c6_USART_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

