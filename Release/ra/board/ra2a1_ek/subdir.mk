################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/board/ra2a1_ek/board_init.c \
../ra/board/ra2a1_ek/board_leds.c 

C_DEPS += \
./ra/board/ra2a1_ek/board_init.d \
./ra/board/ra2a1_ek/board_leds.d 

OBJS += \
./ra/board/ra2a1_ek/board_init.o \
./ra/board/ra2a1_ek/board_leds.o 

SREC += \
mmp.srec 

MAP += \
mmp.map 


# Each subdirectory must supply rules for building sources it contributes
ra/board/ra2a1_ek/%.o: ../ra/board/ra2a1_ek/%.c
	$(file > $@.in,-mcpu=cortex-m23 -mthumb -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM23 -D_RA_ORDINAL=1 -I"C:/Workspace_Aevice/workspace_fsp_adc_example_EKRA2A1_no_release_self/mmp/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"C:/Workspace_Aevice/workspace_fsp_adc_example_EKRA2A1_no_release_self/mmp/src" -I"C:/Workspace_Aevice/workspace_fsp_adc_example_EKRA2A1_no_release_self/mmp/ra/fsp/inc" -I"C:/Workspace_Aevice/workspace_fsp_adc_example_EKRA2A1_no_release_self/mmp/ra/fsp/inc/api" -I"C:/Workspace_Aevice/workspace_fsp_adc_example_EKRA2A1_no_release_self/mmp/ra/fsp/inc/instances" -I"C:/Workspace_Aevice/workspace_fsp_adc_example_EKRA2A1_no_release_self/mmp/ra_gen" -I"C:/Workspace_Aevice/workspace_fsp_adc_example_EKRA2A1_no_release_self/mmp/ra_cfg/fsp_cfg" -I"C:/Workspace_Aevice/workspace_fsp_adc_example_EKRA2A1_no_release_self/mmp/ra_cfg/fsp_cfg/bsp" -I"." -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"
