################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/smart-watch_20/Middlewares/Third_Party/FatFs/src/diskio.c \
C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/smart-watch_20/Middlewares/Third_Party/FatFs/src/ff.c \
C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/smart-watch_20/Middlewares/Third_Party/FatFs/src/ff_gen_drv.c \
C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/smart-watch_20/Middlewares/Third_Party/FatFs/src/option/syscall.c 

OBJS += \
./Middlewares/Third_Party/FatFs/diskio.o \
./Middlewares/Third_Party/FatFs/ff.o \
./Middlewares/Third_Party/FatFs/ff_gen_drv.o \
./Middlewares/Third_Party/FatFs/syscall.o 

C_DEPS += \
./Middlewares/Third_Party/FatFs/diskio.d \
./Middlewares/Third_Party/FatFs/ff.d \
./Middlewares/Third_Party/FatFs/ff_gen_drv.d \
./Middlewares/Third_Party/FatFs/syscall.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FatFs/diskio.o: C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/smart-watch_20/Middlewares/Third_Party/FatFs/src/diskio.c Middlewares/Third_Party/FatFs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H747xx -c -I../FATFS/Target -I../FATFS/App -I../LIBJPEG/App -I../LIBJPEG/Target -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Utilities/JPEG -I../../Middlewares/Third_Party/FatFs/src -I../../Middlewares/Third_Party/LibJPEG/include -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Middlewares/Third_Party/FatFs/diskio.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Third_Party/FatFs/ff.o: C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/smart-watch_20/Middlewares/Third_Party/FatFs/src/ff.c Middlewares/Third_Party/FatFs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H747xx -c -I../FATFS/Target -I../FATFS/App -I../LIBJPEG/App -I../LIBJPEG/Target -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Utilities/JPEG -I../../Middlewares/Third_Party/FatFs/src -I../../Middlewares/Third_Party/LibJPEG/include -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Middlewares/Third_Party/FatFs/ff.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Third_Party/FatFs/ff_gen_drv.o: C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/smart-watch_20/Middlewares/Third_Party/FatFs/src/ff_gen_drv.c Middlewares/Third_Party/FatFs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H747xx -c -I../FATFS/Target -I../FATFS/App -I../LIBJPEG/App -I../LIBJPEG/Target -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Utilities/JPEG -I../../Middlewares/Third_Party/FatFs/src -I../../Middlewares/Third_Party/LibJPEG/include -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Middlewares/Third_Party/FatFs/ff_gen_drv.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Third_Party/FatFs/syscall.o: C:/Users/Fato/Desktop/Nuova\ cartella/Smart-Watch/smart-watch_20/Middlewares/Third_Party/FatFs/src/option/syscall.c Middlewares/Third_Party/FatFs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H747xx -c -I../FATFS/Target -I../FATFS/App -I../LIBJPEG/App -I../LIBJPEG/Target -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Utilities/JPEG -I../../Middlewares/Third_Party/FatFs/src -I../../Middlewares/Third_Party/LibJPEG/include -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Middlewares/Third_Party/FatFs/syscall.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-FatFs

clean-Middlewares-2f-Third_Party-2f-FatFs:
	-$(RM) ./Middlewares/Third_Party/FatFs/diskio.cyclo ./Middlewares/Third_Party/FatFs/diskio.d ./Middlewares/Third_Party/FatFs/diskio.o ./Middlewares/Third_Party/FatFs/diskio.su ./Middlewares/Third_Party/FatFs/ff.cyclo ./Middlewares/Third_Party/FatFs/ff.d ./Middlewares/Third_Party/FatFs/ff.o ./Middlewares/Third_Party/FatFs/ff.su ./Middlewares/Third_Party/FatFs/ff_gen_drv.cyclo ./Middlewares/Third_Party/FatFs/ff_gen_drv.d ./Middlewares/Third_Party/FatFs/ff_gen_drv.o ./Middlewares/Third_Party/FatFs/ff_gen_drv.su ./Middlewares/Third_Party/FatFs/syscall.cyclo ./Middlewares/Third_Party/FatFs/syscall.d ./Middlewares/Third_Party/FatFs/syscall.o ./Middlewares/Third_Party/FatFs/syscall.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-FatFs

