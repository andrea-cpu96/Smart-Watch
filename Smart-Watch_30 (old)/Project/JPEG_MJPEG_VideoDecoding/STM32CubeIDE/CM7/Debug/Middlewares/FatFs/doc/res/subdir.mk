################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Andrea/Embedded/repositories/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/doc/res/app1.c \
D:/Andrea/Embedded/repositories/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/doc/res/app2.c \
D:/Andrea/Embedded/repositories/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/doc/res/app3.c \
D:/Andrea/Embedded/repositories/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/doc/res/app4.c 

OBJS += \
./Middlewares/FatFs/doc/res/app1.o \
./Middlewares/FatFs/doc/res/app2.o \
./Middlewares/FatFs/doc/res/app3.o \
./Middlewares/FatFs/doc/res/app4.o 

C_DEPS += \
./Middlewares/FatFs/doc/res/app1.d \
./Middlewares/FatFs/doc/res/app2.d \
./Middlewares/FatFs/doc/res/app3.d \
./Middlewares/FatFs/doc/res/app4.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FatFs/doc/res/app1.o: D:/Andrea/Embedded/repositories/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/doc/res/app1.c Middlewares/FatFs/doc/res/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FatFs/doc/res/app2.o: D:/Andrea/Embedded/repositories/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/doc/res/app2.c Middlewares/FatFs/doc/res/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FatFs/doc/res/app3.o: D:/Andrea/Embedded/repositories/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/doc/res/app3.c Middlewares/FatFs/doc/res/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FatFs/doc/res/app4.o: D:/Andrea/Embedded/repositories/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/doc/res/app4.c Middlewares/FatFs/doc/res/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-FatFs-2f-doc-2f-res

clean-Middlewares-2f-FatFs-2f-doc-2f-res:
	-$(RM) ./Middlewares/FatFs/doc/res/app1.cyclo ./Middlewares/FatFs/doc/res/app1.d ./Middlewares/FatFs/doc/res/app1.o ./Middlewares/FatFs/doc/res/app1.su ./Middlewares/FatFs/doc/res/app2.cyclo ./Middlewares/FatFs/doc/res/app2.d ./Middlewares/FatFs/doc/res/app2.o ./Middlewares/FatFs/doc/res/app2.su ./Middlewares/FatFs/doc/res/app3.cyclo ./Middlewares/FatFs/doc/res/app3.d ./Middlewares/FatFs/doc/res/app3.o ./Middlewares/FatFs/doc/res/app3.su ./Middlewares/FatFs/doc/res/app4.cyclo ./Middlewares/FatFs/doc/res/app4.d ./Middlewares/FatFs/doc/res/app4.o ./Middlewares/FatFs/doc/res/app4.su

.PHONY: clean-Middlewares-2f-FatFs-2f-doc-2f-res

