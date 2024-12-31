################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Project/JPEG_MJPEG_VideoDecoding/Common/Src/system_stm32h7xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32h7xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32h7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32h7xx.o: C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Project/JPEG_MJPEG_VideoDecoding/Common/Src/system_stm32h7xx.c Drivers/CMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32H747xx -DUSE_STM32H747I_DISCO -DCORE_CM4 -DUSE_HAL_DRIVER -c -I../../../Common/Inc -I../../../CM4/Inc -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../../Utilities/lcd -I../../../../../../../../Utilities/Fonts -I../../../../../../../../Utilities/CPU -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/CMSIS/system_stm32h7xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS

clean-Drivers-2f-CMSIS:
	-$(RM) ./Drivers/CMSIS/system_stm32h7xx.cyclo ./Drivers/CMSIS/system_stm32h7xx.d ./Drivers/CMSIS/system_stm32h7xx.o ./Drivers/CMSIS/system_stm32h7xx.su

.PHONY: clean-Drivers-2f-CMSIS

