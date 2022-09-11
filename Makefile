# This file was automagically generated by mbed.org. For more information, 
# see http://mbed.org/handbook/Exporting-to-GCC-ARM-Embedded

###############################################################################
# Boiler-plate

# cross-platform directory manipulation
ifeq ($(shell echo $$OS),$$OS)
    MAKEDIR = if not exist "$(1)" mkdir "$(1)"
    RM = rmdir /S /Q "$(1)"
else
    MAKEDIR = '$(SHELL)' -c "mkdir -p \"$(1)\""
    RM = '$(SHELL)' -c "rm -rf \"$(1)\""
endif

OBJDIR := BUILD
# Move to the build directory
ifeq (,$(filter $(OBJDIR),$(notdir $(CURDIR))))
.SUFFIXES:
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
MAKETARGET = '$(MAKE)' --no-print-directory -C $(OBJDIR) -f '$(mkfile_path)' \
		'SRCDIR=$(CURDIR)' $(MAKECMDGOALS)
.PHONY: $(OBJDIR) clean
all:
	+@$(call MAKEDIR,$(OBJDIR))
	+@$(MAKETARGET)
$(OBJDIR): all
Makefile : ;
% :: $(OBJDIR) ; :
clean :
	$(call RM,$(OBJDIR))

else

# trick rules into thinking we are in the root, when we are in the bulid dir
VPATH = ..

# Boiler-plate
###############################################################################
# Project settings

PROJECT := Project_DDS


# Project settings
###############################################################################
# Objects and Paths

OBJECTS += OV7670/OV7670.o
OBJECTS += SDFileSystem/FATFileSystem/ChaN/ccsbcs.o
OBJECTS += SDFileSystem/FATFileSystem/ChaN/diskio.o
OBJECTS += SDFileSystem/FATFileSystem/ChaN/ff.o
OBJECTS += SDFileSystem/FATFileSystem/FATDirHandle.o
OBJECTS += SDFileSystem/FATFileSystem/FATFileHandle.o
OBJECTS += SDFileSystem/FATFileSystem/FATFileSystem.o
OBJECTS += SDFileSystem/SDCRC.o
OBJECTS += SDFileSystem/SDFileSystem.o
OBJECTS += SIM800H/SIM800H.o
OBJECTS += main/main.o

 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/board.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/cmsis_nvic.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/hal_tick.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/mbed_overrides.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/retarget.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/startup_stm32l476xx.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_adc.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_adc_ex.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_can.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_comp.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_cortex.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_crc.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_crc_ex.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_cryp.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_cryp_ex.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_dac.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_dac_ex.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_dfsdm.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_dma.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_firewall.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_flash.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_flash_ex.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_flash_ramfunc.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_gpio.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_hcd.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_i2c.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_i2c_ex.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_irda.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_iwdg.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_lcd.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_lptim.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_msp_template.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_nand.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_nor.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_opamp.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_opamp_ex.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_pcd.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_pcd_ex.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_pwr.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_pwr_ex.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_qspi.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_rcc.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_rcc_ex.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_rng.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_rtc.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_rtc_ex.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_sai.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_sd.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_smartcard.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_smartcard_ex.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_smbus.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_spi.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_spi_ex.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_sram.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_swpmi.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_tim.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_tim_ex.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_tsc.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_uart.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_uart_ex.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_usart.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_hal_wwdg.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_ll_fmc.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_ll_sdmmc.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/stm32l4xx_ll_usb.o
 SYS_OBJECTS += mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/system_stm32l4xx.o

INCLUDE_PATHS += -I../
INCLUDE_PATHS += -I../.
INCLUDE_PATHS += -I..//usr/src/mbed-sdk
INCLUDE_PATHS += -I../OV7670
INCLUDE_PATHS += -I../SDFileSystem
INCLUDE_PATHS += -I../SDFileSystem/FATFileSystem
INCLUDE_PATHS += -I../SDFileSystem/FATFileSystem/ChaN
INCLUDE_PATHS += -I../SIM800H
INCLUDE_PATHS += -I../main
INCLUDE_PATHS += -I../mbed
INCLUDE_PATHS += -I../mbed/TARGET_NUCLEO_L476RG
INCLUDE_PATHS += -I../mbed/TARGET_NUCLEO_L476RG/TARGET_STM/TARGET_STM32L4
INCLUDE_PATHS += -I../mbed/TARGET_NUCLEO_L476RG/TARGET_STM/TARGET_STM32L4/TARGET_NUCLEO_L476RG

LIBRARY_PATHS := -L../mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM 
LIBRARIES := -lmbed 
LINKER_SCRIPT ?= ../mbed/TARGET_NUCLEO_L476RG/TOOLCHAIN_GCC_ARM/STM32L476XX.ld

# Objects and Paths
###############################################################################
# Tools and Flags

AS      = arm-none-eabi-gcc
CC      = arm-none-eabi-gcc
CPP     = arm-none-eabi-g++
LD      = arm-none-eabi-gcc
ELF2BIN = arm-none-eabi-objcopy
PREPROC = arm-none-eabi-cpp -E -P -Wl,--gc-sections -Wl,--wrap,main --specs=nano.specs -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -fmessage-length=0 -fno-exceptions -ffunction-sections -fdata-sections -funsigned-char -MMD -fomit-frame-pointer -Os -g -DMBED_TRAP_ERRORS_ENABLED=1 -DMBED_RTOS_SINGLE_THREAD -D__NEWLIB_NANO -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp


C_FLAGS += -c
C_FLAGS += -std=gnu11
C_FLAGS += -include
C_FLAGS += mbed_config.h
C_FLAGS += -DMBED_BUILD_TIMESTAMP=1592142379.7962322
C_FLAGS += -DDEVICE_I2CSLAVE=1
C_FLAGS += -DDEVICE_SLEEP=1
C_FLAGS += -DDEVICE_PWMOUT=1
C_FLAGS += -DTARGET_STM
C_FLAGS += -DDEVICE_RTC=1
C_FLAGS += -DTOOLCHAIN_GCC_ARM
C_FLAGS += -DDEVICE_PORTOUT=1
C_FLAGS += -D__MBED_CMSIS_RTOS_CM
C_FLAGS += -DTARGET_FF_ARDUINO
C_FLAGS += -DDEVICE_STDIO_MESSAGES=1
C_FLAGS += -D__MBED__=1
C_FLAGS += -DDEVICE_PORTIN=1
C_FLAGS += -DTARGET_RTOS_M4_M7
C_FLAGS += -DTARGET_CORTEX
C_FLAGS += -DTARGET_NUCLEO_L476RG
C_FLAGS += -DDEVICE_I2C=1
C_FLAGS += -D__CORTEX_M4
C_FLAGS += -DTARGET_STM32L4
C_FLAGS += -DTARGET_FF_MORPHO
C_FLAGS += -DDEVICE_INTERRUPTIN=1
C_FLAGS += -D__FPU_PRESENT=1
C_FLAGS += -DDEVICE_SPISLAVE=1
C_FLAGS += -DTARGET_LIKE_MBED
C_FLAGS += -DARM_MATH_CM4
C_FLAGS += -DDEVICE_ANALOGOUT=1
C_FLAGS += -DTARGET_NAME=NUCLEO_L476RG
C_FLAGS += -DTARGET_LIKE_CORTEX_M4
C_FLAGS += -DDEVICE_SERIAL=1
C_FLAGS += -DTARGET_M4
C_FLAGS += -DTOOLCHAIN_GCC
C_FLAGS += -DTARGET_RELEASE
C_FLAGS += -DDEVICE_PORTINOUT=1
C_FLAGS += -D__CMSIS_RTOS
C_FLAGS += -DDEVICE_SPI=1
C_FLAGS += -DDEVICE_SERIAL_FC=1
C_FLAGS += -DTARGET_STM32L476RG
C_FLAGS += -DTARGET_CORTEX_M
C_FLAGS += -DDEVICE_ANALOGIN=1
C_FLAGS += -include
C_FLAGS += mbed_config.h
C_FLAGS += -c
C_FLAGS += -std=gnu11
C_FLAGS += -Wall
C_FLAGS += -Wextra
C_FLAGS += -Wno-unused-parameter
C_FLAGS += -Wno-missing-field-initializers
C_FLAGS += -fmessage-length=0
C_FLAGS += -fno-exceptions
C_FLAGS += -ffunction-sections
C_FLAGS += -fdata-sections
C_FLAGS += -funsigned-char
C_FLAGS += -MMD
C_FLAGS += -fomit-frame-pointer
C_FLAGS += -Os
C_FLAGS += -g
C_FLAGS += -DMBED_TRAP_ERRORS_ENABLED=1
C_FLAGS += -DMBED_RTOS_SINGLE_THREAD
C_FLAGS += -D__NEWLIB_NANO
C_FLAGS += -mcpu=cortex-m4
C_FLAGS += -mthumb
C_FLAGS += -mfpu=fpv4-sp-d16
C_FLAGS += -mfloat-abi=softfp

CXX_FLAGS += -c
CXX_FLAGS += -std=gnu++14
CXX_FLAGS += -fno-rtti
CXX_FLAGS += -Wvla
CXX_FLAGS += -include
CXX_FLAGS += mbed_config.h
CXX_FLAGS += -DMBED_BUILD_TIMESTAMP=1592142379.7962322
CXX_FLAGS += -DDEVICE_I2CSLAVE=1
CXX_FLAGS += -DDEVICE_SLEEP=1
CXX_FLAGS += -DDEVICE_PWMOUT=1
CXX_FLAGS += -DTARGET_STM
CXX_FLAGS += -DDEVICE_RTC=1
CXX_FLAGS += -DTOOLCHAIN_GCC_ARM
CXX_FLAGS += -DDEVICE_PORTOUT=1
CXX_FLAGS += -D__MBED_CMSIS_RTOS_CM
CXX_FLAGS += -DTARGET_FF_ARDUINO
CXX_FLAGS += -DDEVICE_STDIO_MESSAGES=1
CXX_FLAGS += -D__MBED__=1
CXX_FLAGS += -DDEVICE_PORTIN=1
CXX_FLAGS += -DTARGET_RTOS_M4_M7
CXX_FLAGS += -DTARGET_CORTEX
CXX_FLAGS += -DTARGET_NUCLEO_L476RG
CXX_FLAGS += -DDEVICE_I2C=1
CXX_FLAGS += -D__CORTEX_M4
CXX_FLAGS += -DTARGET_STM32L4
CXX_FLAGS += -DTARGET_FF_MORPHO
CXX_FLAGS += -DDEVICE_INTERRUPTIN=1
CXX_FLAGS += -D__FPU_PRESENT=1
CXX_FLAGS += -DDEVICE_SPISLAVE=1
CXX_FLAGS += -DTARGET_LIKE_MBED
CXX_FLAGS += -DARM_MATH_CM4
CXX_FLAGS += -DDEVICE_ANALOGOUT=1
CXX_FLAGS += -DTARGET_NAME=NUCLEO_L476RG
CXX_FLAGS += -DTARGET_LIKE_CORTEX_M4
CXX_FLAGS += -DDEVICE_SERIAL=1
CXX_FLAGS += -DTARGET_M4
CXX_FLAGS += -DTOOLCHAIN_GCC
CXX_FLAGS += -DTARGET_RELEASE
CXX_FLAGS += -DDEVICE_PORTINOUT=1
CXX_FLAGS += -D__CMSIS_RTOS
CXX_FLAGS += -DDEVICE_SPI=1
CXX_FLAGS += -DDEVICE_SERIAL_FC=1
CXX_FLAGS += -DTARGET_STM32L476RG
CXX_FLAGS += -DTARGET_CORTEX_M
CXX_FLAGS += -DDEVICE_ANALOGIN=1
CXX_FLAGS += -include
CXX_FLAGS += mbed_config.h
CXX_FLAGS += -c
CXX_FLAGS += -std=gnu++14
CXX_FLAGS += -fno-rtti
CXX_FLAGS += -Wvla
CXX_FLAGS += -Wall
CXX_FLAGS += -Wextra
CXX_FLAGS += -Wno-unused-parameter
CXX_FLAGS += -Wno-missing-field-initializers
CXX_FLAGS += -fmessage-length=0
CXX_FLAGS += -fno-exceptions
CXX_FLAGS += -ffunction-sections
CXX_FLAGS += -fdata-sections
CXX_FLAGS += -funsigned-char
CXX_FLAGS += -MMD
CXX_FLAGS += -fomit-frame-pointer
CXX_FLAGS += -Os
CXX_FLAGS += -g
CXX_FLAGS += -DMBED_TRAP_ERRORS_ENABLED=1
CXX_FLAGS += -DMBED_RTOS_SINGLE_THREAD
CXX_FLAGS += -D__NEWLIB_NANO
CXX_FLAGS += -mcpu=cortex-m4
CXX_FLAGS += -mthumb
CXX_FLAGS += -mfpu=fpv4-sp-d16
CXX_FLAGS += -mfloat-abi=softfp

ASM_FLAGS += -c
ASM_FLAGS += -x
ASM_FLAGS += assembler-with-cpp
ASM_FLAGS += -DARM_MATH_CM4
ASM_FLAGS += -D__FPU_PRESENT=1
ASM_FLAGS += -D__CMSIS_RTOS
ASM_FLAGS += -D__CORTEX_M4
ASM_FLAGS += -D__MBED_CMSIS_RTOS_CM
ASM_FLAGS += -I/usr/src/mbed-sdk
ASM_FLAGS += -I../OV7670
ASM_FLAGS += -I../SDFileSystem
ASM_FLAGS += -I../SDFileSystem/FATFileSystem
ASM_FLAGS += -I../SDFileSystem/FATFileSystem/ChaN
ASM_FLAGS += -I../SIM800H
ASM_FLAGS += -I../main
ASM_FLAGS += -I../mbed
ASM_FLAGS += -I../mbed/TARGET_NUCLEO_L476RG
ASM_FLAGS += -I../mbed/TARGET_NUCLEO_L476RG/TARGET_STM/TARGET_STM32L4
ASM_FLAGS += -I../mbed/TARGET_NUCLEO_L476RG/TARGET_STM/TARGET_STM32L4/TARGET_NUCLEO_L476RG
ASM_FLAGS += -include
ASM_FLAGS += /filer/workspace_data/exports/5/5fa939ea5a702b577908913cd37cb3d6/Project_DDS/mbed_config.h
ASM_FLAGS += -c
ASM_FLAGS += -x
ASM_FLAGS += assembler-with-cpp
ASM_FLAGS += -Wall
ASM_FLAGS += -Wextra
ASM_FLAGS += -Wno-unused-parameter
ASM_FLAGS += -Wno-missing-field-initializers
ASM_FLAGS += -fmessage-length=0
ASM_FLAGS += -fno-exceptions
ASM_FLAGS += -ffunction-sections
ASM_FLAGS += -fdata-sections
ASM_FLAGS += -funsigned-char
ASM_FLAGS += -MMD
ASM_FLAGS += -fomit-frame-pointer
ASM_FLAGS += -Os
ASM_FLAGS += -g
ASM_FLAGS += -DMBED_TRAP_ERRORS_ENABLED=1
ASM_FLAGS += -DMBED_RTOS_SINGLE_THREAD
ASM_FLAGS += -D__NEWLIB_NANO
ASM_FLAGS += -mcpu=cortex-m4
ASM_FLAGS += -mthumb
ASM_FLAGS += -mfpu=fpv4-sp-d16
ASM_FLAGS += -mfloat-abi=softfp


LD_FLAGS :=-Wl,--gc-sections -Wl,--wrap,main --specs=nano.specs -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp 
LD_SYS_LIBS :=-Wl,--start-group -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys -lmbed -Wl,--end-group

# Tools and Flags
###############################################################################
# Rules

.PHONY: all lst size


all: $(PROJECT).bin $(PROJECT).hex size


.s.o:
	+@$(call MAKEDIR,$(dir $@))
	+@echo "Assemble: $(notdir $<)"
  
	@$(AS) -c $(ASM_FLAGS) -o $@ $<
  


.S.o:
	+@$(call MAKEDIR,$(dir $@))
	+@echo "Assemble: $(notdir $<)"
  
	@$(AS) -c $(ASM_FLAGS) -o $@ $<
  

.c.o:
	+@$(call MAKEDIR,$(dir $@))
	+@echo "Compile: $(notdir $<)"
	@$(CC) $(C_FLAGS) $(INCLUDE_PATHS) -o $@ $<

.cpp.o:
	+@$(call MAKEDIR,$(dir $@))
	+@echo "Compile: $(notdir $<)"
	@$(CPP) $(CXX_FLAGS) $(INCLUDE_PATHS) -o $@ $<


$(PROJECT).link_script.ld: $(LINKER_SCRIPT)
	@$(PREPROC) $< -o $@



$(PROJECT).elf: $(OBJECTS) $(SYS_OBJECTS) $(PROJECT).link_script.ld 
	+@echo "$(filter %.o, $^)" > .link_options.txt
	+@echo "link: $(notdir $@)"
	@$(LD) $(LD_FLAGS) -T $(filter-out %.o, $^) $(LIBRARY_PATHS) --output $@ @.link_options.txt $(LIBRARIES) $(LD_SYS_LIBS)


$(PROJECT).bin: $(PROJECT).elf
	$(ELF2BIN) -O binary $< $@
	+@echo "===== bin file ready to flash: $(OBJDIR)/$@ =====" 

$(PROJECT).hex: $(PROJECT).elf
	$(ELF2BIN) -O ihex $< $@


# Rules
###############################################################################
# Dependencies

DEPS = $(OBJECTS:.o=.d) $(SYS_OBJECTS:.o=.d)
-include $(DEPS)
endif

# Dependencies
###############################################################################
# Catch-all

%: ;

# Catch-all
###############################################################################