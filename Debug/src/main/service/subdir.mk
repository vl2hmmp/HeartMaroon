################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/main/service/linetrace.c \
..\src/main/service/search_line.c 

C_DEPS += \
./src/main/service/linetrace.d \
./src/main/service/search_line.d 

OBJS += \
./src/main/service/linetrace.obj \
./src/main/service/search_line.obj 


# Each subdirectory must supply rules for building sources it contributes
src/main/service/%.obj: ../src/main/service/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c99   -include="C:\PROGRA~2\Renesas\RX\2_6_0/include"  -debug -nomessage -isa=rxv1 -fpu -nologo  -define=__RX=1   "$<"
	ccrx -lang=c99 -output=obj="$(@:%.d=%.obj)"  -include="C:\PROGRA~2\Renesas\RX\2_6_0/include"  -debug -nomessage -isa=rxv1 -fpu -nologo  -define=__RX=1   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

