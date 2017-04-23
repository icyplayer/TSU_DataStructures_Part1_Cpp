################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ch2_vector/Vector.cpp \
../ch2_vector/vectorTest.cpp 

OBJS += \
./ch2_vector/Vector.o \
./ch2_vector/vectorTest.o 

CPP_DEPS += \
./ch2_vector/Vector.d \
./ch2_vector/vectorTest.d 


# Each subdirectory must supply rules for building sources it contributes
ch2_vector/%.o: ../ch2_vector/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


