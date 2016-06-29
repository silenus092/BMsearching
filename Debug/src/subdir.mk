################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BM.cpp \
../src/BMsearching.cpp \
../src/Downloadsources.cpp \
../src/Horspool.cpp 

OBJS += \
./src/BM.o \
./src/BMsearching.o \
./src/Downloadsources.o \
./src/Horspool.o 

CPP_DEPS += \
./src/BM.d \
./src/BMsearching.d \
./src/Downloadsources.d \
./src/Horspool.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/note/Downloads/mysql-connector/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


