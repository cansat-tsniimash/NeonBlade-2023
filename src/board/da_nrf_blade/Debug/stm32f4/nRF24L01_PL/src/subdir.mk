################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
X:/Cansat\ 2023/Neon\ Blade/Software/lib-tsniimash/stm32f4/nRF24L01_PL/src/nrf24_lower_api_stm32.c \
X:/Cansat\ 2023/Neon\ Blade/Software/lib-tsniimash/stm32f4/nRF24L01_PL/src/nrf24_upper_api.c 

OBJS += \
./stm32f4/nRF24L01_PL/src/nrf24_lower_api_stm32.o \
./stm32f4/nRF24L01_PL/src/nrf24_upper_api.o 

C_DEPS += \
./stm32f4/nRF24L01_PL/src/nrf24_lower_api_stm32.d \
./stm32f4/nRF24L01_PL/src/nrf24_upper_api.d 


# Each subdirectory must supply rules for building sources it contributes
stm32f4/nRF24L01_PL/src/nrf24_lower_api_stm32.o: X:/Cansat\ 2023/Neon\ Blade/Software/lib-tsniimash/stm32f4/nRF24L01_PL/src/nrf24_lower_api_stm32.c stm32f4/nRF24L01_PL/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"X:/Cansat 2023/Neon Blade/Software/lib-tsniimash/stm32f4" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32f4/nRF24L01_PL/src/nrf24_upper_api.o: X:/Cansat\ 2023/Neon\ Blade/Software/lib-tsniimash/stm32f4/nRF24L01_PL/src/nrf24_upper_api.c stm32f4/nRF24L01_PL/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"X:/Cansat 2023/Neon Blade/Software/lib-tsniimash/stm32f4" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-stm32f4-2f-nRF24L01_PL-2f-src

clean-stm32f4-2f-nRF24L01_PL-2f-src:
	-$(RM) ./stm32f4/nRF24L01_PL/src/nrf24_lower_api_stm32.d ./stm32f4/nRF24L01_PL/src/nrf24_lower_api_stm32.o ./stm32f4/nRF24L01_PL/src/nrf24_upper_api.d ./stm32f4/nRF24L01_PL/src/nrf24_upper_api.o

.PHONY: clean-stm32f4-2f-nRF24L01_PL-2f-src
