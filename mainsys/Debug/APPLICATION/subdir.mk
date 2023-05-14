################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APPLICATION/APP_EarlyDetection.c \
../APPLICATION/APP_SteeringLock.c \
../APPLICATION/APP_WaterCooling.c 

OBJS += \
./APPLICATION/APP_EarlyDetection.o \
./APPLICATION/APP_SteeringLock.o \
./APPLICATION/APP_WaterCooling.o 

C_DEPS += \
./APPLICATION/APP_EarlyDetection.d \
./APPLICATION/APP_SteeringLock.d \
./APPLICATION/APP_WaterCooling.d 


# Each subdirectory must supply rules for building sources it contributes
APPLICATION/%.o: ../APPLICATION/%.c APPLICATION/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


