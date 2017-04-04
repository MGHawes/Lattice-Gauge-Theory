################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../indexing.cc \
../linkclass.cc \
../main.cc \
../stapleclass.cc 

CC_DEPS += \
./indexing.d \
./linkclass.d \
./main.d \
./stapleclass.d 

OBJS += \
./indexing.o \
./linkclass.o \
./main.o \
./stapleclass.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


