################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TIMERS/TIMER0/TIMER0_INTERFACE.c 

OBJS += \
./TIMERS/TIMER0/TIMER0_INTERFACE.o 

C_DEPS += \
./TIMERS/TIMER0/TIMER0_INTERFACE.d 


# Each subdirectory must supply rules for building sources it contributes
TIMERS/TIMER0/%.o: ../TIMERS/TIMER0/%.c TIMERS/TIMER0/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


