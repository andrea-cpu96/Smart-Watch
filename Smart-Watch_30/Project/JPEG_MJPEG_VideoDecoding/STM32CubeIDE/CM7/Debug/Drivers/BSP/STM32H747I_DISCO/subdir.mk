################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.c \
C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.c \
C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sd.c \
C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.c 

OBJS += \
./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery.o \
./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_bus.o \
./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_sd.o \
./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_sdram.o 

C_DEPS += \
./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery.d \
./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_bus.d \
./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_sd.d \
./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_sdram.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery.o: C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.c Drivers/BSP/STM32H747I_DISCO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_bus.o: C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.c Drivers/BSP/STM32H747I_DISCO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_bus.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_sd.o: C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sd.c Drivers/BSP/STM32H747I_DISCO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_sd.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_sdram.o: C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.c Drivers/BSP/STM32H747I_DISCO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_sdram.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32H747I_DISCO

clean-Drivers-2f-BSP-2f-STM32H747I_DISCO:
	-$(RM) ./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery.cyclo ./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery.d ./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery.o ./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery.su ./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_bus.cyclo ./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_bus.d ./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_bus.o ./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_bus.su ./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_sd.cyclo ./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_sd.d ./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_sd.o ./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_sd.su ./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_sdram.cyclo ./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_sdram.d ./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_sdram.o ./Drivers/BSP/STM32H747I_DISCO/stm32h747i_discovery_sdram.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32H747I_DISCO

