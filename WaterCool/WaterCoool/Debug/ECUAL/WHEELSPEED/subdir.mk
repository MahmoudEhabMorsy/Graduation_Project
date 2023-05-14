################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECUAL/WHEELSPEED/a3144_wss.c 

OBJS += \
./ECUAL/WHEELSPEED/a3144_wss.o 

C_DEPS += \
./ECUAL/WHEELSPEED/a3144_wss.d 


# Each subdirectory must supply rules for building sources it contributes
ECUAL/WHEELSPEED/%.o: ../ECUAL/WHEELSPEED/%.c ECUAL/WHEELSPEED/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


