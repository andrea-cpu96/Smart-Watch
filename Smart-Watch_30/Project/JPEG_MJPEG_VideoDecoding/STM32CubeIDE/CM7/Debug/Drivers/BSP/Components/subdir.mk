################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/adv7533.c \
../Drivers/BSP/Components/adv7533_reg.c \
../Drivers/BSP/Components/is42s32800j.c \
../Drivers/BSP/Components/nt35510.c \
../Drivers/BSP/Components/nt35510_reg.c \
../Drivers/BSP/Components/otm8009a.c \
../Drivers/BSP/Components/otm8009a_reg.c 

OBJS += \
./Drivers/BSP/Components/adv7533.o \
./Drivers/BSP/Components/adv7533_reg.o \
./Drivers/BSP/Components/is42s32800j.o \
./Drivers/BSP/Components/nt35510.o \
./Drivers/BSP/Components/nt35510_reg.o \
./Drivers/BSP/Components/otm8009a.o \
./Drivers/BSP/Components/otm8009a_reg.o 

C_DEPS += \
./Drivers/BSP/Components/adv7533.d \
./Drivers/BSP/Components/adv7533_reg.d \
./Drivers/BSP/Components/is42s32800j.d \
./Drivers/BSP/Components/nt35510.d \
./Drivers/BSP/Components/nt35510_reg.d \
./Drivers/BSP/Components/otm8009a.d \
./Drivers/BSP/Components/otm8009a_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/%.o Drivers/BSP/Components/%.su Drivers/BSP/Components/%.cyclo: ../Drivers/BSP/Components/%.c Drivers/BSP/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_LCD_HDMI -DSTM32H747xx -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DCORE_CM7 -c -I../../../Common/Inc -I../../../CM7/Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/STM32H747I-DISCO -I../../../../../Drivers/BSP/Components/Common -I../../../../../Utilities/CPU -I../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../Middlewares/Third_Party/FatFs/src/option -I../../../../../Drivers/STM32H7xxHAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components

clean-Drivers-2f-BSP-2f-Components:
	-$(RM) ./Drivers/BSP/Components/adv7533.cyclo ./Drivers/BSP/Components/adv7533.d ./Drivers/BSP/Components/adv7533.o ./Drivers/BSP/Components/adv7533.su ./Drivers/BSP/Components/adv7533_reg.cyclo ./Drivers/BSP/Components/adv7533_reg.d ./Drivers/BSP/Components/adv7533_reg.o ./Drivers/BSP/Components/adv7533_reg.su ./Drivers/BSP/Components/is42s32800j.cyclo ./Drivers/BSP/Components/is42s32800j.d ./Drivers/BSP/Components/is42s32800j.o ./Drivers/BSP/Components/is42s32800j.su ./Drivers/BSP/Components/nt35510.cyclo ./Drivers/BSP/Components/nt35510.d ./Drivers/BSP/Components/nt35510.o ./Drivers/BSP/Components/nt35510.su ./Drivers/BSP/Components/nt35510_reg.cyclo ./Drivers/BSP/Components/nt35510_reg.d ./Drivers/BSP/Components/nt35510_reg.o ./Drivers/BSP/Components/nt35510_reg.su ./Drivers/BSP/Components/otm8009a.cyclo ./Drivers/BSP/Components/otm8009a.d ./Drivers/BSP/Components/otm8009a.o ./Drivers/BSP/Components/otm8009a.su ./Drivers/BSP/Components/otm8009a_reg.cyclo ./Drivers/BSP/Components/otm8009a_reg.d ./Drivers/BSP/Components/otm8009a_reg.o ./Drivers/BSP/Components/otm8009a_reg.su

.PHONY: clean-Drivers-2f-BSP-2f-Components

