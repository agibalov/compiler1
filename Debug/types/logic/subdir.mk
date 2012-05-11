################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../types/logic/logic_binary_op_type.cpp \
../types/logic/logic_equal_types.cpp \
../types/logic/logic_flat_type.cpp \
../types/logic/logic_type_rank.cpp \
../types/logic/logic_unary_op_type.cpp 

OBJS += \
./types/logic/logic_binary_op_type.o \
./types/logic/logic_equal_types.o \
./types/logic/logic_flat_type.o \
./types/logic/logic_type_rank.o \
./types/logic/logic_unary_op_type.o 

CPP_DEPS += \
./types/logic/logic_binary_op_type.d \
./types/logic/logic_equal_types.d \
./types/logic/logic_flat_type.d \
./types/logic/logic_type_rank.d \
./types/logic/logic_unary_op_type.d 


# Each subdirectory must supply rules for building sources it contributes
types/logic/%.o: ../types/logic/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/loki/boost_1_49_0 -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


