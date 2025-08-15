################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/gpio_driver.c 

OBJS += \
./driver/gpio_driver.o 

C_DEPS += \
./driver/gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
driver/%.o driver/%.su driver/%.cyclo: ../driver/%.c driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"/home/lenovo/Simulation_Linux/stm32_dev/gpio/driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-driver

clean-driver:
	-$(RM) ./driver/gpio_driver.cyclo ./driver/gpio_driver.d ./driver/gpio_driver.o ./driver/gpio_driver.su

.PHONY: clean-driver

