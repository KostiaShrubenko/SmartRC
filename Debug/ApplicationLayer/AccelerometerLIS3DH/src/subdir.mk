################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ApplicationLayer/AccelerometerLIS3DH/src/LIS3DH.c 

OBJS += \
./ApplicationLayer/AccelerometerLIS3DH/src/LIS3DH.o 

C_DEPS += \
./ApplicationLayer/AccelerometerLIS3DH/src/LIS3DH.d 


# Each subdirectory must supply rules for building sources it contributes
ApplicationLayer/AccelerometerLIS3DH/src/LIS3DH.o: ../ApplicationLayer/AccelerometerLIS3DH/src/LIS3DH.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DUSE_FULL_LL_DRIVER -c -I../Core/inc -I../Startup -I"../CMSIS/inc" -I../LowLevelDrivers/inc -I../Config -I../ApplicationLayer/CapSensDriver/inc -I../ApplicationLayer/Debug/inc -I../ApplicationLayer/SensorProcessing/inc -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ApplicationLayer/AccelerometerLIS3DH/src/LIS3DH.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

