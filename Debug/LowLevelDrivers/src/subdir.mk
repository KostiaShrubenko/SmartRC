################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LowLevelDrivers/src/stm32f1xx_ll_gpio.c \
../LowLevelDrivers/src/stm32f1xx_ll_rcc.c \
../LowLevelDrivers/src/stm32f1xx_ll_utils.c 

OBJS += \
./LowLevelDrivers/src/stm32f1xx_ll_gpio.o \
./LowLevelDrivers/src/stm32f1xx_ll_rcc.o \
./LowLevelDrivers/src/stm32f1xx_ll_utils.o 

C_DEPS += \
./LowLevelDrivers/src/stm32f1xx_ll_gpio.d \
./LowLevelDrivers/src/stm32f1xx_ll_rcc.d \
./LowLevelDrivers/src/stm32f1xx_ll_utils.d 


# Each subdirectory must supply rules for building sources it contributes
LowLevelDrivers/src/stm32f1xx_ll_gpio.o: ../LowLevelDrivers/src/stm32f1xx_ll_gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DUSE_FULL_LL_DRIVER -c -I../Core/inc -I../Startup -I"../CMSIS/inc" -I../LowLevelDrivers/inc -I../Config -I../ApplicationLayer/CapSensDriver/inc -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"LowLevelDrivers/src/stm32f1xx_ll_gpio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
LowLevelDrivers/src/stm32f1xx_ll_rcc.o: ../LowLevelDrivers/src/stm32f1xx_ll_rcc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DUSE_FULL_LL_DRIVER -c -I../Core/inc -I../Startup -I"../CMSIS/inc" -I../LowLevelDrivers/inc -I../Config -I../ApplicationLayer/CapSensDriver/inc -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"LowLevelDrivers/src/stm32f1xx_ll_rcc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
LowLevelDrivers/src/stm32f1xx_ll_utils.o: ../LowLevelDrivers/src/stm32f1xx_ll_utils.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DUSE_FULL_LL_DRIVER -c -I../Core/inc -I../Startup -I"../CMSIS/inc" -I../LowLevelDrivers/inc -I../Config -I../ApplicationLayer/CapSensDriver/inc -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"LowLevelDrivers/src/stm32f1xx_ll_utils.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

