################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/App/Src/app_fsm_task.c \
../Core/App/Src/maxim_ds18b20_port.c 

OBJS += \
./Core/App/Src/app_fsm_task.o \
./Core/App/Src/maxim_ds18b20_port.o 

C_DEPS += \
./Core/App/Src/app_fsm_task.d \
./Core/App/Src/maxim_ds18b20_port.d 


# Each subdirectory must supply rules for building sources it contributes
Core/App/Src/%.o Core/App/Src/%.su: ../Core/App/Src/%.c Core/App/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/cfunes/CESE/PdM/Drivers/Core/Inc" -I"/home/cfunes/CESE/PdM/Drivers/maxim_ds18b20" -I"/home/cfunes/CESE/PdM/Drivers/maxim_ds18b20/Inc" -I"/home/cfunes/CESE/PdM/Drivers/API/Inc" -I"/home/cfunes/CESE/PdM/Core/App/Inc" -I"/home/cfunes/CESE/PdM/Drivers/BSP/STM32F4xx_Nucleo_144" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-App-2f-Src

clean-Core-2f-App-2f-Src:
	-$(RM) ./Core/App/Src/app_fsm_task.d ./Core/App/Src/app_fsm_task.o ./Core/App/Src/app_fsm_task.su ./Core/App/Src/maxim_ds18b20_port.d ./Core/App/Src/maxim_ds18b20_port.o ./Core/App/Src/maxim_ds18b20_port.su

.PHONY: clean-Core-2f-App-2f-Src

