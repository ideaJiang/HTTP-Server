################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../classes/timestamp/base/Timestamp.cpp 

OBJS += \
./classes/timestamp/base/Timestamp.o 

CPP_DEPS += \
./classes/timestamp/base/Timestamp.d 


# Each subdirectory must supply rules for building sources it contributes
classes/timestamp/base/%.o: ../classes/timestamp/base/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


