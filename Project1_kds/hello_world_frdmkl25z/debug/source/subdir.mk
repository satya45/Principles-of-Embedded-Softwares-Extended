################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Freescale/KSDK_1.3.0/examples/frdmkl25z/demo_apps/hello_world/fsl_lptmr_irq.c \
C:/Freescale/KSDK_1.3.0/examples/frdmkl25z/demo_apps/hello_world/main.c 

OBJS += \
./source/fsl_lptmr_irq.o \
./source/main.o 

C_DEPS += \
./source/fsl_lptmr_irq.d \
./source/main.d 


# Each subdirectory must supply rules for building sources it contributes
source/fsl_lptmr_irq.o: C:/Freescale/KSDK_1.3.0/examples/frdmkl25z/demo_apps/hello_world/fsl_lptmr_irq.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DCPU_MKL25Z128VLK4 -DFRDM_KL25Z -DFREEDOM -I../../../../../../platform/osa/inc -I../../../../../../platform/utilities/inc -I../../../../../../platform/CMSIS/Include -I../../../../../../platform/devices -I../../../../../../platform/devices/MKL25Z4/include -I../../../../../../platform/devices/MKL25Z4/startup -I../../../../../../platform/hal/inc -I../../../../../../platform/drivers/inc -I../../../../../../platform/system/inc -I../../../.. -I"C:\Freescale\KSDK_1.3.0\examples\frdmkl25z\demo_apps\hello_world\kds\headers" -I"C:\Freescale\KSDK_1.3.0\examples\frdmkl25z\demo_apps\hello_world\kds\src" -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/main.o: C:/Freescale/KSDK_1.3.0/examples/frdmkl25z/demo_apps/hello_world/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DCPU_MKL25Z128VLK4 -DFRDM_KL25Z -DFREEDOM -I../../../../../../platform/osa/inc -I../../../../../../platform/utilities/inc -I../../../../../../platform/CMSIS/Include -I../../../../../../platform/devices -I../../../../../../platform/devices/MKL25Z4/include -I../../../../../../platform/devices/MKL25Z4/startup -I../../../../../../platform/hal/inc -I../../../../../../platform/drivers/inc -I../../../../../../platform/system/inc -I../../../.. -I"C:\Freescale\KSDK_1.3.0\examples\frdmkl25z\demo_apps\hello_world\kds\headers" -I"C:\Freescale\KSDK_1.3.0\examples\frdmkl25z\demo_apps\hello_world\kds\src" -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


