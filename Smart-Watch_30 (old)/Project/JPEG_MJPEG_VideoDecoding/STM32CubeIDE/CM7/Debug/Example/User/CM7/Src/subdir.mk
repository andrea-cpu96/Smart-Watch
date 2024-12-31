################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Example/User/CM7/Src/AVI_parser.c \
../Example/User/CM7/Src/GC9A01.c \
../Example/User/CM7/Src/decode_dma.c \
../Example/User/CM7/Src/main.c \
../Example/User/CM7/Src/sd_diskio.c \
../Example/User/CM7/Src/smart_watch.c \
../Example/User/CM7/Src/stm32h7xx_hal_msp.c \
../Example/User/CM7/Src/stm32h7xx_it.c \
../Example/User/CM7/Src/syscalls.c \
../Example/User/CM7/Src/sysmem.c 

OBJS += \
./Example/User/CM7/Src/AVI_parser.o \
./Example/User/CM7/Src/GC9A01.o \
./Example/User/CM7/Src/decode_dma.o \
./Example/User/CM7/Src/main.o \
./Example/User/CM7/Src/sd_diskio.o \
./Example/User/CM7/Src/smart_watch.o \
./Example/User/CM7/Src/stm32h7xx_hal_msp.o \
./Example/User/CM7/Src/stm32h7xx_it.o \
./Example/User/CM7/Src/syscalls.o \
./Example/User/CM7/Src/sysmem.o 

C_DEPS += \
./Example/User/CM7/Src/AVI_parser.d \
./Example/User/CM7/Src/GC9A01.d \
./Example/User/CM7/Src/decode_dma.d \
./Example/User/CM7/Src/main.d \
./Example/User/CM7/Src/sd_diskio.d \
./Example/User/CM7/Src/smart_watch.d \
./Example/User/CM7/Src/stm32h7xx_hal_msp.d \
./Example/User/CM7/Src/stm32h7xx_it.d \
./Example/User/CM7/Src/syscalls.d \
./Example/User/CM7/Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Example/User/CM7/Src/%.o Example/User/CM7/Src/%.su Example/User/CM7/Src/%.cyclo: ../Example/User/CM7/Src/%.c Example/User/CM7/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../STM32CubeIDE/CM7/Example/User/CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Example-2f-User-2f-CM7-2f-Src

clean-Example-2f-User-2f-CM7-2f-Src:
	-$(RM) ./Example/User/CM7/Src/AVI_parser.cyclo ./Example/User/CM7/Src/AVI_parser.d ./Example/User/CM7/Src/AVI_parser.o ./Example/User/CM7/Src/AVI_parser.su ./Example/User/CM7/Src/GC9A01.cyclo ./Example/User/CM7/Src/GC9A01.d ./Example/User/CM7/Src/GC9A01.o ./Example/User/CM7/Src/GC9A01.su ./Example/User/CM7/Src/decode_dma.cyclo ./Example/User/CM7/Src/decode_dma.d ./Example/User/CM7/Src/decode_dma.o ./Example/User/CM7/Src/decode_dma.su ./Example/User/CM7/Src/main.cyclo ./Example/User/CM7/Src/main.d ./Example/User/CM7/Src/main.o ./Example/User/CM7/Src/main.su ./Example/User/CM7/Src/sd_diskio.cyclo ./Example/User/CM7/Src/sd_diskio.d ./Example/User/CM7/Src/sd_diskio.o ./Example/User/CM7/Src/sd_diskio.su ./Example/User/CM7/Src/smart_watch.cyclo ./Example/User/CM7/Src/smart_watch.d ./Example/User/CM7/Src/smart_watch.o ./Example/User/CM7/Src/smart_watch.su ./Example/User/CM7/Src/stm32h7xx_hal_msp.cyclo ./Example/User/CM7/Src/stm32h7xx_hal_msp.d ./Example/User/CM7/Src/stm32h7xx_hal_msp.o ./Example/User/CM7/Src/stm32h7xx_hal_msp.su ./Example/User/CM7/Src/stm32h7xx_it.cyclo ./Example/User/CM7/Src/stm32h7xx_it.d ./Example/User/CM7/Src/stm32h7xx_it.o ./Example/User/CM7/Src/stm32h7xx_it.su ./Example/User/CM7/Src/syscalls.cyclo ./Example/User/CM7/Src/syscalls.d ./Example/User/CM7/Src/syscalls.o ./Example/User/CM7/Src/syscalls.su ./Example/User/CM7/Src/sysmem.cyclo ./Example/User/CM7/Src/sysmem.d ./Example/User/CM7/Src/sysmem.o ./Example/User/CM7/Src/sysmem.su

.PHONY: clean-Example-2f-User-2f-CM7-2f-Src

