################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BaseMessageClass.cpp \
../messageQueueClass.cpp \
../messageTransport.cpp \
../udpMessageTransport.cpp 

OBJS += \
./BaseMessageClass.o \
./messageQueueClass.o \
./messageTransport.o \
./udpMessageTransport.o 

CPP_DEPS += \
./BaseMessageClass.d \
./messageQueueClass.d \
./messageTransport.d \
./udpMessageTransport.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


