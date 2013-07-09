################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../server.types/HTTP/HTTPserver.cpp 

OBJS += \
./server.types/HTTP/HTTPserver.o 

CPP_DEPS += \
./server.types/HTTP/HTTPserver.d 


# Each subdirectory must supply rules for building sources it contributes
server.types/HTTP/%.o: ../server.types/HTTP/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


