################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../indexing.cc \
../latticetest.cc \
../linkclass.cc \
../main.cc \
../phasesgen.cc \
../plaqclass.cc \
../stapleclass.cc \
../wallclass.cc 

CC_DEPS += \
./indexing.d \
./latticetest.d \
./linkclass.d \
./main.d \
./phasesgen.d \
./plaqclass.d \
./stapleclass.d \
./wallclass.d 

OBJS += \
./indexing.o \
./latticetest.o \
./linkclass.o \
./main.o \
./phasesgen.o \
./plaqclass.o \
./stapleclass.o \
./wallclass.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


