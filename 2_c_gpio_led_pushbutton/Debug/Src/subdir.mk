################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main_led_pushbutton.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main_led_pushbutton.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main_led_pushbutton.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I/home/lenovo/Simulation_Linux/stm32_dev/F4_chip_headers/CMSIS/Device/ST/STM32F4xx/Include -I/home/lenovo/Simulation_Linux/stm32_dev/F4_chip_headers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main_led_pushbutton.cyclo ./Src/main_led_pushbutton.d ./Src/main_led_pushbutton.o ./Src/main_led_pushbutton.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

