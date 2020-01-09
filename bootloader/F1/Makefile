TARGET = hid_bootloader
FLASH  = st-flash
DEVICE = STM32F10X_MD

VECTOR_TABLE_OFFSET = 0x0000

# The default Flash Page size (Sector size) for LOW and MEDIUM STM32F103 devices is 1024 bytes
# High Density STM32F103 devices have 2 kB Flash Page size  
PAGE_SIZE = 1024 

C_SRCS = Src/main.c Src/usb.c Src/hid.c Src/led.c Src/flash.c

# Be silent per default, but 'make V=1' will show all compiler calls.
# If you're insane, V=99 will print out all sorts of things.
V?=0
ifeq ($(V),0)
Q	:= @
NULL	:= 2>/dev/null
endif

INCLUDE_DIRS += -I Inc
INCLUDE_DIRS += -I CMSIS/Device/ST/STM32F10x/Include 
INCLUDE_DIRS += -I CMSIS/Include

SRCS += $(C_SRCS)
vpath %.c $(sort $(dir $(C_SRCS)))
OBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SRCS:.c=.o)))

CFLAGS += -mcpu=cortex-m3 -mthumb -Wall -Os
CFLAGS += -std=gnu99
CFLAGS += -fno-common -static
CFLAGS += -specs=nano.specs -specs=nosys.specs
CFLAGS += -Wextra -Wshadow -Wno-unused-variable -Wimplicit-function-declaration
CFLAGS += -Wredundant-decls -Wstrict-prototypes -Wmissing-prototypes
CFLAGS += $(INCLUDE_DIRS)
CFLAGS += -D$(DEVICE)
CFLAGS += -DVECTOR_TABLE_OFFSET=$(VECTOR_TABLE_OFFSET)
CFLAGS += -nostdlib
CFLAGS += $(TARGETFLAGS)
CFLAGS += -DPAGE_SIZE=$(PAGE_SIZE)

LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,--print-memory-usage
LDFLAGS += -Wl,--no-wchar-size-warning
LDFLAGS += -nostdlib
LDFLAGS += -T$(LINKER_SCRIPT)

# Tool paths.
PREFIX	?= arm-none-eabi-
CC = $(PREFIX)gcc
LD = $(PREFIX)ld
OBJDUMP = $(PREFIX)objdump
OBJCOPY = $(PREFIX)objcopy
SIZE = $(PREFIX)size
GDB = $(PREFIX)gdb

ECHO = @echo
CP = cp
MKDIR = mkdir
RM = rm
RMDIR = rmdir

BUILD_DIR = build
BIN_DIR = bootloader_only_binaries

program: $(BUILD_DIR)/$(TARGET).hex
	$(FLASH) write $(BUILD_DIR)/$(TARGET).bin 0x8000000
.PHONY: all build output info size clean flash

all: $(SRCS) clean gccversion output info size

maple-mini: $(SRCS) clean gccversion build_maple-mini copy_maple_mini info size
generic-pc13: $(SRCS) clean gccversion build_generic-pc13 copy_generic-pc13 info size
generic-pd2: $(SRCS) clean gccversion build_generic-pd2 copy_generic-pd2 info size
generic-pd1: $(SRCS) clean gccversion build_generic-pd1 copy_generic-pd1 info size
generic-pa1: $(SRCS) clean gccversion build_generic-pa1 copy_generic-pa1 info size
generic-pb9: $(SRCS) clean gccversion build_generic-pb9 copy_generic-pb9 info size
generic-pe2: $(SRCS) clean gccversion build_generic-pe2 copy_generic-pe2 info size
generic-pa9: $(SRCS) clean gccversion build_generic-pa9 copy_generic-pa9 info size
generic-pe5: $(SRCS) clean gccversion build_generic-pe5 copy_generic-pe5 info size
generic-pb7: $(SRCS) clean gccversion build_generic-pb7 copy_generic-pb7 info size
generic-pb0: $(SRCS) clean gccversion build_generic-pb0 copy_generic-pb0 info size
generic-pb12: $(SRCS) clean gccversion build_generic-pb12 copy_generic-pb12 info size
mini-stm32v3: $(SRCS) clean gccversion build_mini-stm32v3 copy_mini-stm32v3 info size

build_maple-mini: TARGETFLAGS= -DTARGET_MAPLE_MINI
build_maple-mini: LINKER_SCRIPT=STM32F103C8T6.ld
build_maple-mini: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
copy_maple_mini: $(BIN_DIR)
	$(ECHO) "COPY    $(BIN_DIR)/hid_maple_mini.bin"
	$(Q)$(CP) $(BUILD_DIR)/$(TARGET).bin $(BIN_DIR)/hid_maple_mini.bin

build_generic-pc13: TARGETFLAGS= -DTARGET_GENERIC_F103_PC13
build_generic-pc13: LINKER_SCRIPT=STM32F103C8T6.ld
build_generic-pc13: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
copy_generic-pc13: $(BIN_DIR)
	$(ECHO) "COPY    $(BIN_DIR)/hid_generic_pc13.bin"
	$(Q)$(CP) $(BUILD_DIR)/$(TARGET).bin $(BIN_DIR)/hid_generic_pc13.bin

build_generic-pd2: TARGETFLAGS= -DTARGET_GENERIC_F103_PD2
build_generic-pd2: LINKER_SCRIPT=STM32F103C8T6.ld
build_generic-pd2: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
copy_generic-pd2: $(BIN_DIR)
	$(ECHO) "COPY    $(BIN_DIR)/hid_generic_pd2.bin"
	$(Q)$(CP) $(BUILD_DIR)/$(TARGET).bin $(BIN_DIR)/hid_generic_pd2.bin

build_generic-pd1: TARGETFLAGS= -DTARGET_GENERIC_F103_PD1
build_generic-pd1: LINKER_SCRIPT=STM32F103C8T6.ld
build_generic-pd1: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
copy_generic-pd1: $(BIN_DIR)
	$(ECHO) "COPY    $(BIN_DIR)/hid_generic_pd1.bin"
	$(Q)$(CP) $(BUILD_DIR)/$(TARGET).bin $(BIN_DIR)/hid_generic_pd1.bin

build_generic-pa1: TARGETFLAGS= -DTARGET_GENERIC_F103_PA1
build_generic-pa1: LINKER_SCRIPT=STM32F103C8T6.ld
build_generic-pa1: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
copy_generic-pa1: $(BIN_DIR)
	$(ECHO) "COPY    $(BIN_DIR)/hid_generic_pa1.bin"
	$(Q)$(CP) $(BUILD_DIR)/$(TARGET).bin $(BIN_DIR)/hid_generic_pa1.bin

build_generic-pb9: TARGETFLAGS= -DTARGET_GENERIC_F103_PB9
build_generic-pb9: LINKER_SCRIPT=STM32F103C8T6.ld
build_generic-pb9: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
copy_generic-pb9: $(BIN_DIR)
	$(ECHO) "COPY    $(BIN_DIR)/hid_generic_pb9.bin"
	$(Q)$(CP) $(BUILD_DIR)/$(TARGET).bin $(BIN_DIR)/hid_generic_pb9.bin

build_generic-pe2: TARGETFLAGS= -DTARGET_GENERIC_F103_PE2
build_generic-pe2: LINKER_SCRIPT=STM32F103C8T6.ld
build_generic-pe2: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
copy_generic-pe2: $(BIN_DIR)
	$(ECHO) "COPY    $(BIN_DIR)/hid_generic_pe2.bin"
	$(Q)$(CP) $(BUILD_DIR)/$(TARGET).bin $(BIN_DIR)/hid_generic_pe2.bin

build_generic-pa9: TARGETFLAGS= -DTARGET_GENERIC_F103_PA9
build_generic-pa9: LINKER_SCRIPT=STM32F103C8T6.ld
build_generic-pa9: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
copy_generic-pa9: $(BIN_DIR)
	$(ECHO) "COPY    $(BIN_DIR)/hid_generic_pa9.bin"
	$(Q)$(CP) $(BUILD_DIR)/$(TARGET).bin $(BIN_DIR)/hid_generic_pa9.bin

build_generic-pe5: TARGETFLAGS= -DTARGET_GENERIC_F103_PE5
build_generic-pe5: LINKER_SCRIPT=STM32F103C8T6.ld
build_generic-pe5: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
copy_generic-pe5: $(BIN_DIR)
	$(ECHO) "COPY    $(BIN_DIR)/hid_generic_pe5.bin"
	$(Q)$(CP) $(BUILD_DIR)/$(TARGET).bin $(BIN_DIR)/hid_generic_pe5.bin

build_generic-pb7: TARGETFLAGS= -DTARGET_GENERIC_F103_PB7
build_generic-pb7: LINKER_SCRIPT=STM32F103C8T6.ld
build_generic-pb7: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
copy_generic-pb7: $(BIN_DIR)
	$(ECHO) "COPY    $(BIN_DIR)/hid_generic_pb7.bin"
	$(Q)$(CP) $(BUILD_DIR)/$(TARGET).bin $(BIN_DIR)/hid_generic_pb7.bin

build_generic-pb0: TARGETFLAGS= -DTARGET_GENERIC_F103_PB0
build_generic-pb0: LINKER_SCRIPT=STM32F103C8T6.ld
build_generic-pb0: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
copy_generic-pb0: $(BIN_DIR)
	$(ECHO) "COPY    $(BIN_DIR)/hid_generic_pb0.bin"
	$(Q)$(CP) $(BUILD_DIR)/$(TARGET).bin $(BIN_DIR)/hid_generic_pb0.bin

build_generic-pb12: TARGETFLAGS= -DTARGET_GENERIC_F103_PB12
build_generic-pb12: LINKER_SCRIPT=STM32F103C8T6.ld
build_generic-pb12: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
copy_generic-pb12: $(BIN_DIR)
	$(ECHO) "COPY    $(BIN_DIR)/hid_generic_pb12.bin"
	$(Q)$(CP) $(BUILD_DIR)/$(TARGET).bin $(BIN_DIR)/hid_generic_pb12.bin

build_mini-stm32v3: TARGETFLAGS= -DTARGET_MINI_STM32V3
build_mini-stm32v3: LINKER_SCRIPT=STM32F103CBT6.ld
build_mini-stm32v3: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
copy_mini-stm32v3: $(BIN_DIR)
	$(ECHO) "COPY    $(BIN_DIR)/hid_mini-stm32v3.bin"
	$(Q)$(CP) $(BUILD_DIR)/$(TARGET).bin $(BIN_DIR)/hid_mini-stm32v3.bin
  
$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(ECHO) "LD      $@"
	$(Q)$(CC) $(LDFLAGS) $(CFLAGS) $(OBJS) -o "$@"

.SECONDARY: $(OBJS)

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(ECHO) "CC      $<"
	$(Q)$(CC) $(CFLAGS) -c "$<" -o "$@"

output: $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(ECHO) "GENHEX  $@"
	$(Q)$(OBJCOPY) -O ihex $< $@

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(ECHO) "GENBIN  $@"
	$(Q)$(OBJCOPY) -O binary $< $@

gccversion:
	@$(CC) --version

info: $(BUILD_DIR)/$(TARGET).elf
	$(ECHO) "INFO    $<"
	$(Q)$(OBJDUMP) -x -S $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).lst
	$(Q)$(OBJDUMP) -D $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).dis
	$(Q)$(SIZE) $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).size

size: $(BUILD_DIR)/$(TARGET).elf
	$(ECHO) "SIZE    $<"
	$(Q)$(SIZE) $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR):
	$(ECHO) "MKDIR   $@"
	$(Q)$(MKDIR) $@

clean:
	$(ECHO) "CLEAN"
	$(Q)$(RM) -f $(BUILD_DIR)/$(TARGET).elf
	$(Q)$(RM) -f $(BUILD_DIR)/$(TARGET).bin
	$(Q)$(RM) -f $(BUILD_DIR)/$(TARGET).hex
	$(Q)$(RM) -f $(BUILD_DIR)/$(TARGET).size
	$(Q)$(RM) -f $(BUILD_DIR)/$(TARGET).lst
	$(Q)$(RM) -f $(BUILD_DIR)/$(TARGET).dis
	$(Q)$(RM) -f $(BUILD_DIR)/$(TARGET).map
	$(Q)$(RM) -f $(OBJS)
	-$(Q)$(RMDIR) $(BUILD_DIR)
