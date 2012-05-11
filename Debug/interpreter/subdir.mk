################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../interpreter/stack_object.cpp \
../interpreter/validator_object.cpp 

OBJS += \
./interpreter/stack_object.o \
./interpreter/validator_object.o 

CPP_DEPS += \
./interpreter/stack_object.d \
./interpreter/validator_object.d 


# Each subdirectory must supply rules for building sources it contributes
interpreter/%.o: ../interpreter/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/loki/boost_1_43_0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


