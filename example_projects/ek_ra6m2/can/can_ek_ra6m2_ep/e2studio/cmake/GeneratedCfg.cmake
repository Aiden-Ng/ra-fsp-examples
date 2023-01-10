# This file was automatically generated by RASC

set(RASC_EXE_PATH "C:/Renesas/RA/sc_v2022-10_fsp_v4.2.0/eclipse/rasc.exe")
set(RASC_TARGET_DEVICE R7FA6M2AF)
set(RASC_TARGET_ARCH cortex-m4)
set(RASC_PROJECT_NAME FSP_Project)
SET(RASC_TOOLCHAIN_NAME, GCC)
SET(RASC_CMAKE_CXX_FLAGS "-g -O0 -mcpu=cortex-m4 -I ${CMAKE_CURRENT_SOURCE_DIR}/ra/arm/CMSIS_5/CMSIS/Core/Include -I ${CMAKE_CURRENT_SOURCE_DIR}/ra/fsp/inc -I ${CMAKE_CURRENT_SOURCE_DIR}/ra/fsp/inc/api -I ${CMAKE_CURRENT_SOURCE_DIR}/ra/fsp/inc/instances -I ${CMAKE_CURRENT_SOURCE_DIR}/ra_cfg/fsp_cfg -I ${CMAKE_CURRENT_SOURCE_DIR}/ra_cfg/fsp_cfg/bsp -I ${CMAKE_CURRENT_SOURCE_DIR}/ra_gen -I ${CMAKE_CURRENT_SOURCE_DIR}/src  -D_RENESAS_RA_  -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -mthumb  -std=c99 -MMD -MP -MF <SOURCE>.d -MT <OBJECT>")
SET(RASC_CMAKE_ASM_FLAGS "-g -O0 -mcpu=cortex-m4 -I ${CMAKE_CURRENT_SOURCE_DIR}/ra/arm/CMSIS_5/CMSIS/Core/Include -I ${CMAKE_CURRENT_SOURCE_DIR}/ra/fsp/inc -I ${CMAKE_CURRENT_SOURCE_DIR}/ra/fsp/inc/api -I ${CMAKE_CURRENT_SOURCE_DIR}/ra/fsp/inc/instances -I ${CMAKE_CURRENT_SOURCE_DIR}/ra_cfg/fsp_cfg -I ${CMAKE_CURRENT_SOURCE_DIR}/ra_cfg/fsp_cfg/bsp -I ${CMAKE_CURRENT_SOURCE_DIR}/ra_gen -I ${CMAKE_CURRENT_SOURCE_DIR}/src  -D_RENESAS_RA_  -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -mthumb   -x assembler-with-cpp -MMD -MP")
SET(RASC_CMAKE_C_FLAGS "-g -O0 -mcpu=cortex-m4 -I ${CMAKE_CURRENT_SOURCE_DIR}/ra/arm/CMSIS_5/CMSIS/Core/Include -I ${CMAKE_CURRENT_SOURCE_DIR}/ra/fsp/inc -I ${CMAKE_CURRENT_SOURCE_DIR}/ra/fsp/inc/api -I ${CMAKE_CURRENT_SOURCE_DIR}/ra/fsp/inc/instances -I ${CMAKE_CURRENT_SOURCE_DIR}/ra_cfg/fsp_cfg -I ${CMAKE_CURRENT_SOURCE_DIR}/ra_cfg/fsp_cfg/bsp -I ${CMAKE_CURRENT_SOURCE_DIR}/ra_gen -I ${CMAKE_CURRENT_SOURCE_DIR}/src  -D_RENESAS_RA_  -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -mthumb  -std=c99 -MMD -MP -MF <SOURCE>.d -MT <OBJECT>")
SET(RASC_CMAKE_EXE_LINKER_FLAGS "-g -O0 -mcpu=cortex-m4 -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -mthumb -T fsp.ld -Xlinker --gc-sections -Wl,-Map,${PROJECT_NAME}.map --specs=nano.specs --specs=rdimon.specs -L ${CMAKE_CURRENT_SOURCE_DIR}/ -L ${CMAKE_CURRENT_SOURCE_DIR}/script  -o ${CMAKE_CURRENT_SOURCE_DIR}/build/CMakeFiles/${RASC_PROJECT_NAME}.elf.dir/${RASC_PROJECT_NAME}.elf")
SET(RASC_ASM_FILES "${CMAKE_CURRENT_SOURCE_DIR}/ra_gen/*.asm")
