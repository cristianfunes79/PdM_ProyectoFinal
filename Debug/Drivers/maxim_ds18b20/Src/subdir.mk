################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/maxim_ds18b20/Src/maxim_ds18b20.c \
../Drivers/maxim_ds18b20/Src/maxim_ds18b20_port.c 

OBJS += \
./Drivers/maxim_ds18b20/Src/maxim_ds18b20.o \
./Drivers/maxim_ds18b20/Src/maxim_ds18b20_port.o 

C_DEPS += \
./Drivers/maxim_ds18b20/Src/maxim_ds18b20.d \
./Drivers/maxim_ds18b20/Src/maxim_ds18b20_port.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/maxim_ds18b20/Src/%.o Drivers/maxim_ds18b20/Src/%.su: ../Drivers/maxim_ds18b20/Src/%.c Drivers/maxim_ds18b20/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/cfunes/CESE/PdM/Drivers/Core/Inc" -I"/home/cfunes/CESE/PdM/Drivers/maxim_ds18b20" -I"/home/cfunes/CESE/PdM/Drivers/maxim_ds18b20/Inc" -I"/home/cfunes/CESE/PdM/Drivers/API/Inc" -I"/home/cfunes/CESE/PdM/Core/App/Inc" -I"/home/cfunes/CESE/PdM/Drivers/BSP/STM32F4xx_Nucleo_144" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-maxim_ds18b20-2f-Src

clean-Drivers-2f-maxim_ds18b20-2f-Src:
	-$(RM) ./Drivers/maxim_ds18b20/Src/maxim_ds18b20.d ./Drivers/maxim_ds18b20/Src/maxim_ds18b20.o ./Drivers/maxim_ds18b20/Src/maxim_ds18b20.su ./Drivers/maxim_ds18b20/Src/maxim_ds18b20_port.d ./Drivers/maxim_ds18b20/Src/maxim_ds18b20_port.o ./Drivers/maxim_ds18b20/Src/maxim_ds18b20_port.su

.PHONY: clean-Drivers-2f-maxim_ds18b20-2f-Src

