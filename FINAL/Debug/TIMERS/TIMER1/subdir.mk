################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TIMERS/TIMER1/TIMER1_INTERFACE.c 

OBJS += \
./TIMERS/TIMER1/TIMER1_INTERFACE.o 

C_DEPS += \
./TIMERS/TIMER1/TIMER1_INTERFACE.d 


# Each subdirectory must supply rules for building sources it contributes
TIMERS/TIMER1/%.o: ../TIMERS/TIMER1/%.c TIMERS/TIMER1/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


