################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Example/User/Startup/startup_stm32h747xihx.s 

OBJS += \
./Example/User/Startup/startup_stm32h747xihx.o 

S_DEPS += \
./Example/User/Startup/startup_stm32h747xihx.d 


# Each subdirectory must supply rules for building sources it contributes
Example/User/Startup/%.o: ../Example/User/Startup/%.s Example/User/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Example-2f-User-2f-Startup

clean-Example-2f-User-2f-Startup:
	-$(RM) ./Example/User/Startup/startup_stm32h747xihx.d ./Example/User/Startup/startup_stm32h747xihx.o

.PHONY: clean-Example-2f-User-2f-Startup

