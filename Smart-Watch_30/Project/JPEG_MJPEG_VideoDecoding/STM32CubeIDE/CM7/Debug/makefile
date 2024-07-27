################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/FatFs/src/subdir.mk
-include Example/User/Startup/subdir.mk
-include Example/User/CM7/Src/subdir.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/Legacy/subdir.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Drivers/BSP/STM32H747I_DISCO/subdir.mk
-include Drivers/BSP/Components/otm8009a/subdir.mk
-include Drivers/BSP/Components/nt35510/subdir.mk
-include Drivers/BSP/Components/is42s32800j/subdir.mk
-include Drivers/BSP/Components/adv7533/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := JPEG_MJPEG_VideoDecoding_CM7
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
JPEG_MJPEG_VideoDecoding_CM7.elf \

MAP_FILES += \
JPEG_MJPEG_VideoDecoding_CM7.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
JPEG_MJPEG_VideoDecoding_CM7.list \


# All Target
all: main-build

# Main-build Target
main-build: JPEG_MJPEG_VideoDecoding_CM7.elf secondary-outputs

# Tool invocations
JPEG_MJPEG_VideoDecoding_CM7.elf JPEG_MJPEG_VideoDecoding_CM7.map: $(OBJS) $(USER_OBJS) D:\Andrea\Embedded\repositories\Smart-Watch\Smart-Watch_30\Project\JPEG_MJPEG_VideoDecoding\STM32CubeIDE\CM7\STM32H747XIHX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "JPEG_MJPEG_VideoDecoding_CM7.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"D:\Andrea\Embedded\repositories\Smart-Watch\Smart-Watch_30\Project\JPEG_MJPEG_VideoDecoding\STM32CubeIDE\CM7\STM32H747XIHX_FLASH.ld" --specs=nosys.specs -Wl,-Map="JPEG_MJPEG_VideoDecoding_CM7.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

JPEG_MJPEG_VideoDecoding_CM7.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "JPEG_MJPEG_VideoDecoding_CM7.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) JPEG_MJPEG_VideoDecoding_CM7.elf JPEG_MJPEG_VideoDecoding_CM7.list JPEG_MJPEG_VideoDecoding_CM7.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
