################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MAIN/APP_EarlyDetection.c \
../MAIN/APP_SteeringLock.c \
../MAIN/APP_WaterCooling.c \
../MAIN/NODE_main.c 

OBJS += \
./MAIN/APP_EarlyDetection.o \
./MAIN/APP_SteeringLock.o \
./MAIN/APP_WaterCooling.o \
./MAIN/NODE_main.o 

C_DEPS += \
./MAIN/APP_EarlyDetection.d \
./MAIN/APP_SteeringLock.d \
./MAIN/APP_WaterCooling.d \
./MAIN/NODE_main.d 


# Each subdirectory must supply rules for building sources it contributes
MAIN/%.o: ../MAIN/%.c MAIN/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


