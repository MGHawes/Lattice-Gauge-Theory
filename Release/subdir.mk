################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../indexing.cc \
../latticetest.cc \
../linkclass.cc \
../loop.cc \
../main.cc \
../phasesgen.cc \
../plaqclass.cc \
../setup.cc \
../stapleclass.cc \
../wallclass.cc \
../wilsonwall.cc 

CC_DEPS += \
./indexing.d \
./latticetest.d \
./linkclass.d \
./loop.d \
./main.d \
./phasesgen.d \
./plaqclass.d \
./setup.d \
./stapleclass.d \
./wallclass.d \
./wilsonwall.d 

OBJS += \
./indexing.o \
./latticetest.o \
./linkclass.o \
./loop.o \
./main.o \
./phasesgen.o \
./plaqclass.o \
./setup.o \
./stapleclass.o \
./wallclass.o \
./wilsonwall.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


