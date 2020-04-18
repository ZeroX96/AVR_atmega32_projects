################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../TEST.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
TEST.o

OBJS_AS_ARGS +=  \
TEST.o

C_DEPS +=  \
TEST.d

C_DEPS_AS_ARGS +=  \
TEST.d

OUTPUT_FILE_PATH +=TEST.elf

OUTPUT_FILE_PATH_AS_ARGS +=TEST.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler



./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR32/GNU C Compiler : 3.4.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.2.435\avr32-gnu-toolchain\bin\avr32-gcc.exe$(QUOTE)  -DDEBUG  -O1 -ffunction-sections -masm-addr-pseudos -g3 -Wall -mpart=uc3a0512 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<"
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: AVR32/GNU Linker : 3.4.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.2.435\avr32-gnu-toolchain\bin\avr32-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="TEST.map" -Wl,--start-group -lm  -Wl,--end-group -Wl,--gc-sections --rodata-writable -Wl,--direct-data -mpart=uc3a0512 
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.2.435\avr32-gnu-toolchain\bin\avr32-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "TEST.elf" "TEST.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.2.435\avr32-gnu-toolchain\bin\avr32-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "TEST.elf" "TEST.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.2.435\avr32-gnu-toolchain\bin\avr32-objdump.exe" -h -S "TEST.elf" > "TEST.lss"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.2.435\avr32-gnu-toolchain\bin\avr32-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "TEST.elf" "TEST.srec"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.2.435\avr32-gnu-toolchain\bin\avr32-size.exe" "TEST.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "TEST.elf" "TEST.a" "TEST.hex" "TEST.lss" "TEST.eep" "TEST.map" "TEST.srec"
	