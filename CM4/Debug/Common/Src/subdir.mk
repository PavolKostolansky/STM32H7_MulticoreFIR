################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/GIT/STM32/STM32H7_MulticoreFIR/Common/Src/settings.c \
C:/GIT/STM32/STM32H7_MulticoreFIR/Common/Src/system_stm32h7xx_dualcore_boot_cm4_cm7.c 

OBJS += \
./Common/Src/settings.o \
./Common/Src/system_stm32h7xx_dualcore_boot_cm4_cm7.o 

C_DEPS += \
./Common/Src/settings.d \
./Common/Src/system_stm32h7xx_dualcore_boot_cm4_cm7.d 


# Each subdirectory must supply rules for building sources it contributes
Common/Src/settings.o: C:/GIT/STM32/STM32H7_MulticoreFIR/Common/Src/settings.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DCORE_CM4 -DDEBUG -DSTM32H755xx -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Common/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Common/Src/settings.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/Src/system_stm32h7xx_dualcore_boot_cm4_cm7.o: C:/GIT/STM32/STM32H7_MulticoreFIR/Common/Src/system_stm32h7xx_dualcore_boot_cm4_cm7.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DCORE_CM4 -DDEBUG -DSTM32H755xx -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Common/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Common/Src/system_stm32h7xx_dualcore_boot_cm4_cm7.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

