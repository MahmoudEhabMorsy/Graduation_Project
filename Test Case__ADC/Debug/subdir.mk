################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../adc.c \
../adc_testcase.c \
../dio.c \
../lcd.c \
../lm35_driver.c 

OBJS += \
./adc.o \
./adc_testcase.o \
./dio.o \
./lcd.o \
./lm35_driver.o 

C_DEPS += \
./adc.d \
./adc_testcase.d \
./dio.d \
./lcd.d \
./lm35_driver.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


