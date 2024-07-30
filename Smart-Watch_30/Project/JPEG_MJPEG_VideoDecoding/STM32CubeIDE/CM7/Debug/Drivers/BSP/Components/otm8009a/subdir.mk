################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Drivers/BSP/Components/otm8009a/otm8009a.c \
C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Drivers/BSP/Components/otm8009a/otm8009a_reg.c 

OBJS += \
./Drivers/BSP/Components/otm8009a/otm8009a.o \
./Drivers/BSP/Components/otm8009a/otm8009a_reg.o 

C_DEPS += \
./Drivers/BSP/Components/otm8009a/otm8009a.d \
./Drivers/BSP/Components/otm8009a/otm8009a_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/otm8009a/otm8009a.o: C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Drivers/BSP/Components/otm8009a/otm8009a.c Drivers/BSP/Components/otm8009a/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/Components/otm8009a/otm8009a.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/Components/otm8009a/otm8009a_reg.o: C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Drivers/BSP/Components/otm8009a/otm8009a_reg.c Drivers/BSP/Components/otm8009a/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/Components/otm8009a/otm8009a_reg.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-otm8009a

clean-Drivers-2f-BSP-2f-Components-2f-otm8009a:
	-$(RM) ./Drivers/BSP/Components/otm8009a/otm8009a.cyclo ./Drivers/BSP/Components/otm8009a/otm8009a.d ./Drivers/BSP/Components/otm8009a/otm8009a.o ./Drivers/BSP/Components/otm8009a/otm8009a.su ./Drivers/BSP/Components/otm8009a/otm8009a_reg.cyclo ./Drivers/BSP/Components/otm8009a/otm8009a_reg.d ./Drivers/BSP/Components/otm8009a/otm8009a_reg.o ./Drivers/BSP/Components/otm8009a/otm8009a_reg.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-otm8009a

