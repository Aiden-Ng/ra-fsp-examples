################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/r_lpm/r_lpm.c 

C_DEPS += \
./ra/fsp/src/r_lpm/r_lpm.d 

OBJS += \
./ra/fsp/src/r_lpm/r_lpm.o 

SREC += \
mmp.srec 

MAP += \
mmp.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/r_lpm/%.o: ../ra/fsp/src/r_lpm/%.c
	$(file > $@.in,-mcpu=cortex-m23 -mthumb -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM23 -D_RA_ORDINAL=1 -I"C:/Workspace_Aevice/workspace_fsp_low_power_mode_example_EKRA2A1_self/mmp/src" -I"." -I"C:/Workspace_Aevice/workspace_fsp_low_power_mode_example_EKRA2A1_self/mmp/ra/fsp/inc" -I"C:/Workspace_Aevice/workspace_fsp_low_power_mode_example_EKRA2A1_self/mmp/ra/fsp/inc/api" -I"C:/Workspace_Aevice/workspace_fsp_low_power_mode_example_EKRA2A1_self/mmp/ra/fsp/inc/instances" -I"C:/Workspace_Aevice/workspace_fsp_low_power_mode_example_EKRA2A1_self/mmp/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"C:/Workspace_Aevice/workspace_fsp_low_power_mode_example_EKRA2A1_self/mmp/ra_gen" -I"C:/Workspace_Aevice/workspace_fsp_low_power_mode_example_EKRA2A1_self/mmp/ra_cfg/fsp_cfg/bsp" -I"C:/Workspace_Aevice/workspace_fsp_low_power_mode_example_EKRA2A1_self/mmp/ra_cfg/fsp_cfg" -std=c99 -Wno-stringop-overflow -Wno-format-truncation --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"
