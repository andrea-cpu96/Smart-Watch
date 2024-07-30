################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Drivers/BSP/Components/is42s32800j/is42s32800j.c 

OBJS += \
./Drivers/BSP/Components/is42s32800j/is42s32800j.o 

C_DEPS += \
./Drivers/BSP/Components/is42s32800j/is42s32800j.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/is42s32800j/is42s32800j.o: C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Drivers/BSP/Components/is42s32800j/is42s32800j.c Drivers/BSP/Components/is42s32800j/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/Components/is42s32800j/is42s32800j.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-is42s32800j

clean-Drivers-2f-BSP-2f-Components-2f-is42s32800j:
	-$(RM) ./Drivers/BSP/Components/is42s32800j/is42s32800j.cyclo ./Drivers/BSP/Components/is42s32800j/is42s32800j.d ./Drivers/BSP/Components/is42s32800j/is42s32800j.o ./Drivers/BSP/Components/is42s32800j/is42s32800j.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-is42s32800j

