################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Andrea/Embedded/repositories/Smart-Watch/Smart-Watch_30/Drivers/BSP/Components/ft6x06/ft6x06.c \
D:/Andrea/Embedded/repositories/Smart-Watch/Smart-Watch_30/Drivers/BSP/Components/ft6x06/ft6x06_reg.c 

OBJS += \
./Drivers/BSP/Components/ft6x06/ft6x06.o \
./Drivers/BSP/Components/ft6x06/ft6x06_reg.o 

C_DEPS += \
./Drivers/BSP/Components/ft6x06/ft6x06.d \
./Drivers/BSP/Components/ft6x06/ft6x06_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/ft6x06/ft6x06.o: D:/Andrea/Embedded/repositories/Smart-Watch/Smart-Watch_30/Drivers/BSP/Components/ft6x06/ft6x06.c Drivers/BSP/Components/ft6x06/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/Components/ft6x06/ft6x06_reg.o: D:/Andrea/Embedded/repositories/Smart-Watch/Smart-Watch_30/Drivers/BSP/Components/ft6x06/ft6x06_reg.c Drivers/BSP/Components/ft6x06/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-ft6x06

clean-Drivers-2f-BSP-2f-Components-2f-ft6x06:
	-$(RM) ./Drivers/BSP/Components/ft6x06/ft6x06.cyclo ./Drivers/BSP/Components/ft6x06/ft6x06.d ./Drivers/BSP/Components/ft6x06/ft6x06.o ./Drivers/BSP/Components/ft6x06/ft6x06.su ./Drivers/BSP/Components/ft6x06/ft6x06_reg.cyclo ./Drivers/BSP/Components/ft6x06/ft6x06_reg.d ./Drivers/BSP/Components/ft6x06/ft6x06_reg.o ./Drivers/BSP/Components/ft6x06/ft6x06_reg.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-ft6x06

