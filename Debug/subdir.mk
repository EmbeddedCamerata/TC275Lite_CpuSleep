################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cpu0_Main.c \
../Cpu1_Main.c \
../Cpu2_Main.c \
../bsp_led_button.c \
../bsp_stm.c \
../bsp_uart.c \
../scu_sleep.c 

OBJS += \
./Cpu0_Main.o \
./Cpu1_Main.o \
./Cpu2_Main.o \
./bsp_led_button.o \
./bsp_stm.o \
./bsp_uart.o \
./scu_sleep.o 

COMPILED_SRCS += \
./Cpu0_Main.src \
./Cpu1_Main.src \
./Cpu2_Main.src \
./bsp_led_button.src \
./bsp_stm.src \
./bsp_uart.src \
./scu_sleep.src 

C_DEPS += \
./Cpu0_Main.d \
./Cpu1_Main.d \
./Cpu2_Main.d \
./bsp_led_button.d \
./bsp_stm.d \
./bsp_uart.d \
./scu_sleep.d 


# Each subdirectory must supply rules for building sources it contributes
%.src: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc27xd "-fC:/Users/74067/AURIX-v1.7.2-workspace/demo/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

%.o: ./%.src subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


