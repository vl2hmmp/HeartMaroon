################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/main/module/adconverter.c \
..\src/main/module/debug.c \
..\src/main/module/encorder.c \
..\src/main/module/motor.c \
..\src/main/module/photoreflector.c \
..\src/main/module/psdsensor.c \
..\src/main/module/timer.c \
..\src/main/module/utils.c 

C_DEPS += \
./src/main/module/adconverter.d \
./src/main/module/debug.d \
./src/main/module/encorder.d \
./src/main/module/motor.d \
./src/main/module/photoreflector.d \
./src/main/module/psdsensor.d \
./src/main/module/timer.d \
./src/main/module/utils.d 

OBJS += \
./src/main/module/adconverter.obj \
./src/main/module/debug.obj \
./src/main/module/encorder.obj \
./src/main/module/motor.obj \
./src/main/module/photoreflector.obj \
./src/main/module/psdsensor.obj \
./src/main/module/timer.obj \
./src/main/module/utils.obj 


# Each subdirectory must supply rules for building sources it contributes
src/main/module/%.obj: ../src/main/module/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c99   -include="C:\PROGRA~2\Renesas\RX\2_6_0/include"  -debug -nomessage -isa=rxv1 -fpu -nologo  -define=__RX=1   "$<"
	ccrx -lang=c99 -output=obj="$(@:%.d=%.obj)"  -include="C:\PROGRA~2\Renesas\RX\2_6_0/include"  -debug -nomessage -isa=rxv1 -fpu -nologo  -define=__RX=1   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

