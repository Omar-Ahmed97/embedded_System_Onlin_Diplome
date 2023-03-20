################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AOES_RTOS/AOES_FIFO.c \
../AOES_RTOS/CortexMX_OS_porting.c \
../AOES_RTOS/scheduler.c 

OBJS += \
./AOES_RTOS/AOES_FIFO.o \
./AOES_RTOS/CortexMX_OS_porting.o \
./AOES_RTOS/scheduler.o 

C_DEPS += \
./AOES_RTOS/AOES_FIFO.d \
./AOES_RTOS/CortexMX_OS_porting.d \
./AOES_RTOS/scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
AOES_RTOS/AOES_FIFO.o: ../AOES_RTOS/AOES_FIFO.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/learn in depth/Embedded-System-Projects/STM32CubeIDE/workspace_1.4.0/AOES_RTOS1/AOES_RTOS/inc" -I"F:/learn in depth/Embedded-System-Projects/STM32CubeIDE/workspace_1.4.0/AOES_RTOS1/CMSISV5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"AOES_RTOS/AOES_FIFO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
AOES_RTOS/CortexMX_OS_porting.o: ../AOES_RTOS/CortexMX_OS_porting.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/learn in depth/Embedded-System-Projects/STM32CubeIDE/workspace_1.4.0/AOES_RTOS1/AOES_RTOS/inc" -I"F:/learn in depth/Embedded-System-Projects/STM32CubeIDE/workspace_1.4.0/AOES_RTOS1/CMSISV5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"AOES_RTOS/CortexMX_OS_porting.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
AOES_RTOS/scheduler.o: ../AOES_RTOS/scheduler.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/learn in depth/Embedded-System-Projects/STM32CubeIDE/workspace_1.4.0/AOES_RTOS1/AOES_RTOS/inc" -I"F:/learn in depth/Embedded-System-Projects/STM32CubeIDE/workspace_1.4.0/AOES_RTOS1/CMSISV5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"AOES_RTOS/scheduler.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

