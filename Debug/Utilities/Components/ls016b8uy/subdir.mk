################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/Components/ls016b8uy/ls016b8uy.c 

OBJS += \
./Utilities/Components/ls016b8uy/ls016b8uy.o 

C_DEPS += \
./Utilities/Components/ls016b8uy/ls016b8uy.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/Components/ls016b8uy/%.o: ../Utilities/Components/ls016b8uy/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DSTM32F4DISCOVERY -DDEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/ili9325" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/s25fl512s" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/cs43l22" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/ili9341" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/ampire480272" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/n25q512a" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/s5k5cag" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/mfxstm32l152" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/CMSIS/device" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/n25q128a" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/ts3510" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/st7735" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/HAL_Driver/Inc/Legacy" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/lis302dl" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/otm8009a" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/stmpe1600" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/Common" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/ov2640" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/l3gd20" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/HAL_Driver/Inc" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/stmpe811" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/lis3dsh" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/wm8994" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/n25q256a" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/inc" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/ls016b8uy" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/ft6x06" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/STM32F4-Discovery" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/exc7200" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/st7789h2" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/ampire640480" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/Utilities/Components/lsm303dlhc" -I"C:/Users/Sebastien/Desktop/arm_projet/uart_correction/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


