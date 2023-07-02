################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECUAL/BMP/bmp180.c 

OBJS += \
./ECUAL/BMP/bmp180.o 

C_DEPS += \
./ECUAL/BMP/bmp180.d 


# Each subdirectory must supply rules for building sources it contributes
ECUAL/BMP/%.o: ../ECUAL/BMP/%.c ECUAL/BMP/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


