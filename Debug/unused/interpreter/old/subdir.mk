################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../unused/interpreter/old/stack_object.cpp \
../unused/interpreter/old/validator_object.cpp 

OBJS += \
./unused/interpreter/old/stack_object.o \
./unused/interpreter/old/validator_object.o 

CPP_DEPS += \
./unused/interpreter/old/stack_object.d \
./unused/interpreter/old/validator_object.d 


# Each subdirectory must supply rules for building sources it contributes
unused/interpreter/old/%.o: ../unused/interpreter/old/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/loki/boost_1_43_0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


