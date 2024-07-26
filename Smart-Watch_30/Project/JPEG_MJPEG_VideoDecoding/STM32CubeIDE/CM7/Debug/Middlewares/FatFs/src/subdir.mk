################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/src/diskio.c \
C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/src/ff.c \
C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/src/ff_gen_drv.c \
C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/src/option/syscall.c \
C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/src/option/unicode.c 

OBJS += \
./Middlewares/FatFs/src/diskio.o \
./Middlewares/FatFs/src/ff.o \
./Middlewares/FatFs/src/ff_gen_drv.o \
./Middlewares/FatFs/src/syscall.o \
./Middlewares/FatFs/src/unicode.o 

C_DEPS += \
./Middlewares/FatFs/src/diskio.d \
./Middlewares/FatFs/src/ff.d \
./Middlewares/FatFs/src/ff_gen_drv.d \
./Middlewares/FatFs/src/syscall.d \
./Middlewares/FatFs/src/unicode.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FatFs/src/diskio.o: C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/src/diskio.c Middlewares/FatFs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Middlewares/FatFs/src/diskio.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FatFs/src/ff.o: C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/src/ff.c Middlewares/FatFs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Middlewares/FatFs/src/ff.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FatFs/src/ff_gen_drv.o: C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/src/ff_gen_drv.c Middlewares/FatFs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Middlewares/FatFs/src/ff_gen_drv.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FatFs/src/syscall.o: C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/src/option/syscall.c Middlewares/FatFs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Middlewares/FatFs/src/syscall.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FatFs/src/unicode.o: C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/Smart-Watch_30/Middlewares/Third_Party/FatFs/src/option/unicode.c Middlewares/FatFs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Middlewares/FatFs/src/unicode.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-FatFs-2f-src

clean-Middlewares-2f-FatFs-2f-src:
	-$(RM) ./Middlewares/FatFs/src/diskio.cyclo ./Middlewares/FatFs/src/diskio.d ./Middlewares/FatFs/src/diskio.o ./Middlewares/FatFs/src/diskio.su ./Middlewares/FatFs/src/ff.cyclo ./Middlewares/FatFs/src/ff.d ./Middlewares/FatFs/src/ff.o ./Middlewares/FatFs/src/ff.su ./Middlewares/FatFs/src/ff_gen_drv.cyclo ./Middlewares/FatFs/src/ff_gen_drv.d ./Middlewares/FatFs/src/ff_gen_drv.o ./Middlewares/FatFs/src/ff_gen_drv.su ./Middlewares/FatFs/src/syscall.cyclo ./Middlewares/FatFs/src/syscall.d ./Middlewares/FatFs/src/syscall.o ./Middlewares/FatFs/src/syscall.su ./Middlewares/FatFs/src/unicode.cyclo ./Middlewares/FatFs/src/unicode.d ./Middlewares/FatFs/src/unicode.o ./Middlewares/FatFs/src/unicode.su

.PHONY: clean-Middlewares-2f-FatFs-2f-src

