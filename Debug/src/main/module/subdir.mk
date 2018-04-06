################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/main/module/debug.c 

C_DEPS += \
./src/main/module/debug.d 

OBJS += \
./src/main/module/debug.obj 


# Each subdirectory must supply rules for building sources it contributes
src/main/module/%.obj: ../src/main/module/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c99   -include="/include"  -debug -nomessage -isa=rxv1 -fpu -nologo  -define=__RX=1   "$<"
	ccrx -lang=c99 -output=obj="$(@:%.d=%.obj)"  -include="/include"  -debug -nomessage -isa=rxv1 -fpu -nologo  -define=__RX=1   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

