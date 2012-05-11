################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../unused/interpreter/oldtypes/type.cpp 

OBJS += \
./unused/interpreter/oldtypes/type.o 

CPP_DEPS += \
./unused/interpreter/oldtypes/type.d 


# Each subdirectory must supply rules for building sources it contributes
unused/interpreter/oldtypes/%.o: ../unused/interpreter/oldtypes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/loki/boost_1_43_0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


