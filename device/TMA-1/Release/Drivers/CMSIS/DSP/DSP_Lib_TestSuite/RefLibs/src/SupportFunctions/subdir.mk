################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/copy.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fill.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fixed_to_fixed.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fixed_to_float.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/float_to_fixed.c 

C_DEPS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/copy.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fill.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fixed_to_fixed.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fixed_to_float.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/float_to_fixed.d 

OBJS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/copy.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fill.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fixed_to_fixed.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fixed_to_float.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/float_to_fixed.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/%.o Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/%.su Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/%.cyclo: ../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/%.c Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../../Core/Inc -I../../FATFS/Target -I../../FATFS/App -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FatFs/src -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-SupportFunctions

clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-SupportFunctions:
	-$(RM) ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/copy.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/copy.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/copy.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/copy.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fill.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fill.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fill.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fill.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fixed_to_fixed.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fixed_to_fixed.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fixed_to_fixed.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fixed_to_fixed.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fixed_to_float.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fixed_to_float.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fixed_to_float.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/fixed_to_float.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/float_to_fixed.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/float_to_fixed.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/float_to_fixed.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/SupportFunctions/float_to_fixed.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-SupportFunctions

