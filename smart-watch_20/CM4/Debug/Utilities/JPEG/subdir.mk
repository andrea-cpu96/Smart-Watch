################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Andrea/Embedded/repositories/Smart-Watch/smart-watch_20/Utilities/JPEG/jpeg_utils.c 

OBJS += \
./Utilities/JPEG/jpeg_utils.o 

C_DEPS += \
./Utilities/JPEG/jpeg_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/JPEG/jpeg_utils.o: D:/Andrea/Embedded/repositories/Smart-Watch/smart-watch_20/Utilities/JPEG/jpeg_utils.c Utilities/JPEG/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H747xx -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Utilities-2f-JPEG

clean-Utilities-2f-JPEG:
	-$(RM) ./Utilities/JPEG/jpeg_utils.cyclo ./Utilities/JPEG/jpeg_utils.d ./Utilities/JPEG/jpeg_utils.o ./Utilities/JPEG/jpeg_utils.su

.PHONY: clean-Utilities-2f-JPEG

