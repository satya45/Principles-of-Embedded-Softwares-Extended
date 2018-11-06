################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/allocate.c \
../src/dispmem.c \
../src/exit.c \
../src/free.c \
../src/help.c \
../src/inverttime.c \
../src/specifymem.c \
../src/timer.c \
../src/verifytime.c \
../src/write.c \
../src/writetime.c 

OBJS += \
./src/allocate.o \
./src/dispmem.o \
./src/exit.o \
./src/free.o \
./src/help.o \
./src/inverttime.o \
./src/specifymem.o \
./src/timer.o \
./src/verifytime.o \
./src/write.o \
./src/writetime.o 

C_DEPS += \
./src/allocate.d \
./src/dispmem.d \
./src/exit.d \
./src/free.d \
./src/help.d \
./src/inverttime.d \
./src/specifymem.d \
./src/timer.d \
./src/verifytime.d \
./src/write.d \
./src/writetime.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DCPU_MKL25Z128VLK4 -DFRDM_KL25Z -DFREEDOM -I../../../../../../platform/osa/inc -I../../../../../../platform/utilities/inc -I../../../../../../platform/CMSIS/Include -I../../../../../../platform/devices -I../../../../../../platform/devices/MKL25Z4/include -I../../../../../../platform/devices/MKL25Z4/startup -I../../../../../../platform/hal/inc -I../../../../../../platform/drivers/inc -I../../../../../../platform/system/inc -I../../../.. -I"C:\Freescale\KSDK_1.3.0\examples\frdmkl25z\demo_apps\hello_world\kds\headers" -I"C:\Freescale\KSDK_1.3.0\examples\frdmkl25z\demo_apps\hello_world\kds\src" -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


