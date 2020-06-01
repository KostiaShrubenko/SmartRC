################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/src/TaskManager.c \
../Core/src/main.c \
../Core/src/scheduler.c \
../Core/src/stm32f1xx_it.c 

OBJS += \
./Core/src/TaskManager.o \
./Core/src/main.o \
./Core/src/scheduler.o \
./Core/src/stm32f1xx_it.o 

C_DEPS += \
./Core/src/TaskManager.d \
./Core/src/main.d \
./Core/src/scheduler.d \
./Core/src/stm32f1xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
Core/src/TaskManager.o: ../Core/src/TaskManager.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DUSE_FULL_LL_DRIVER -c -I../Core/inc -I../Startup -I"../CMSIS/inc" -I../LowLevelDrivers/inc -I../Config -I../ApplicationLayer/CapSensDriver/inc -I../ApplicationLayer/Debug/inc -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/src/TaskManager.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/src/main.o: ../Core/src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DUSE_FULL_LL_DRIVER -c -I../Core/inc -I../Startup -I"../CMSIS/inc" -I../LowLevelDrivers/inc -I../Config -I../ApplicationLayer/CapSensDriver/inc -I../ApplicationLayer/Debug/inc -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/src/scheduler.o: ../Core/src/scheduler.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DUSE_FULL_LL_DRIVER -c -I../Core/inc -I../Startup -I"../CMSIS/inc" -I../LowLevelDrivers/inc -I../Config -I../ApplicationLayer/CapSensDriver/inc -I../ApplicationLayer/Debug/inc -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/src/scheduler.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/src/stm32f1xx_it.o: ../Core/src/stm32f1xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DUSE_FULL_LL_DRIVER -c -I../Core/inc -I../Startup -I"../CMSIS/inc" -I../LowLevelDrivers/inc -I../Config -I../ApplicationLayer/CapSensDriver/inc -I../ApplicationLayer/Debug/inc -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/src/stm32f1xx_it.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

