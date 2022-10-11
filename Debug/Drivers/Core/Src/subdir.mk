################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Core/Src/gpio.c \
../Drivers/Core/Src/stm32f4xx_hal_msp.c \
../Drivers/Core/Src/stm32f4xx_it.c \
../Drivers/Core/Src/syscalls.c \
../Drivers/Core/Src/sysmem.c \
../Drivers/Core/Src/system_stm32f4xx.c \
../Drivers/Core/Src/tim.c \
../Drivers/Core/Src/usart.c 

OBJS += \
./Drivers/Core/Src/gpio.o \
./Drivers/Core/Src/stm32f4xx_hal_msp.o \
./Drivers/Core/Src/stm32f4xx_it.o \
./Drivers/Core/Src/syscalls.o \
./Drivers/Core/Src/sysmem.o \
./Drivers/Core/Src/system_stm32f4xx.o \
./Drivers/Core/Src/tim.o \
./Drivers/Core/Src/usart.o 

C_DEPS += \
./Drivers/Core/Src/gpio.d \
./Drivers/Core/Src/stm32f4xx_hal_msp.d \
./Drivers/Core/Src/stm32f4xx_it.d \
./Drivers/Core/Src/syscalls.d \
./Drivers/Core/Src/sysmem.d \
./Drivers/Core/Src/system_stm32f4xx.d \
./Drivers/Core/Src/tim.d \
./Drivers/Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Core/Src/%.o Drivers/Core/Src/%.su: ../Drivers/Core/Src/%.c Drivers/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/cfunes/CESE/PdM/Drivers/Core/Inc" -I"/home/cfunes/CESE/PdM/Drivers/maxim_ds18b20" -I"/home/cfunes/CESE/PdM/Drivers/maxim_ds18b20/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Core-2f-Src

clean-Drivers-2f-Core-2f-Src:
	-$(RM) ./Drivers/Core/Src/gpio.d ./Drivers/Core/Src/gpio.o ./Drivers/Core/Src/gpio.su ./Drivers/Core/Src/stm32f4xx_hal_msp.d ./Drivers/Core/Src/stm32f4xx_hal_msp.o ./Drivers/Core/Src/stm32f4xx_hal_msp.su ./Drivers/Core/Src/stm32f4xx_it.d ./Drivers/Core/Src/stm32f4xx_it.o ./Drivers/Core/Src/stm32f4xx_it.su ./Drivers/Core/Src/syscalls.d ./Drivers/Core/Src/syscalls.o ./Drivers/Core/Src/syscalls.su ./Drivers/Core/Src/sysmem.d ./Drivers/Core/Src/sysmem.o ./Drivers/Core/Src/sysmem.su ./Drivers/Core/Src/system_stm32f4xx.d ./Drivers/Core/Src/system_stm32f4xx.o ./Drivers/Core/Src/system_stm32f4xx.su ./Drivers/Core/Src/tim.d ./Drivers/Core/Src/tim.o ./Drivers/Core/Src/tim.su ./Drivers/Core/Src/usart.d ./Drivers/Core/Src/usart.o ./Drivers/Core/Src/usart.su

.PHONY: clean-Drivers-2f-Core-2f-Src

