################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../server.types/Telnet/DateTimeServer.cpp 

OBJS += \
./server.types/Telnet/DateTimeServer.o 

CPP_DEPS += \
./server.types/Telnet/DateTimeServer.d 


# Each subdirectory must supply rules for building sources it contributes
server.types/Telnet/%.o: ../server.types/Telnet/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


