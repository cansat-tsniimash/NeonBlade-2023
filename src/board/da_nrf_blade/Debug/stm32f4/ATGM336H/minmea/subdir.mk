################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/1/Documents/git/cansat-atlas-2021-2022/lib-tsniimash/stm32f4/ATGM336H/minmea/example.c \
C:/Users/1/Documents/git/cansat-atlas-2021-2022/lib-tsniimash/stm32f4/ATGM336H/minmea/minmea.c 

OBJS += \
./stm32f4/ATGM336H/minmea/example.o \
./stm32f4/ATGM336H/minmea/minmea.o 

C_DEPS += \
./stm32f4/ATGM336H/minmea/example.d \
./stm32f4/ATGM336H/minmea/minmea.d 


# Each subdirectory must supply rules for building sources it contributes
stm32f4/ATGM336H/minmea/example.o: C:/Users/1/Documents/git/cansat-atlas-2021-2022/lib-tsniimash/stm32f4/ATGM336H/minmea/example.c stm32f4/ATGM336H/minmea/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/1/Documents/git/cansat-atlas-2021-2022/lib-tsniimash/stm32f4" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32f4/ATGM336H/minmea/minmea.o: C:/Users/1/Documents/git/cansat-atlas-2021-2022/lib-tsniimash/stm32f4/ATGM336H/minmea/minmea.c stm32f4/ATGM336H/minmea/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/1/Documents/git/cansat-atlas-2021-2022/lib-tsniimash/stm32f4" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-stm32f4-2f-ATGM336H-2f-minmea

clean-stm32f4-2f-ATGM336H-2f-minmea:
	-$(RM) ./stm32f4/ATGM336H/minmea/example.d ./stm32f4/ATGM336H/minmea/example.o ./stm32f4/ATGM336H/minmea/minmea.d ./stm32f4/ATGM336H/minmea/minmea.o

.PHONY: clean-stm32f4-2f-ATGM336H-2f-minmea

