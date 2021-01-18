CROSS_COMPILE := arm-none-eabi-
AS := $(CROSS_COMPILE)as
LD := $(CROSS_COMPILE)ld
CC := $(CROSS_COMPILE)gcc
OBJCOPY := $(CROSS_COMPILE)objcopy

ASFLAGS :=
CFLAGS := -std=gnu99 -Os -mthumb -mcpu=cortex-a9 -fno-builtin-printf -fno-strict-aliasing -fno-builtin-memcpy -mno-unaligned-access -Wall -Wextra
LDFLAGS := -nodefaultlibs -nostdlib

# Use bootrom to send data
#CFLAGS += -DUSE_BROM_SEND_DATA

DUMP := dump

DUMP_SRC = dump.c common.c
ASM_SRC = start.S

OBJ = $(DUMP_SRC:%.c=%.o) $(ASM_SRC:%.S=%.o)
DEP = $(OBJ:%.o=%.d)

all: dump.bin

dump.elf: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^ -T linker.ld

%.bin: %.elf
	$(OBJCOPY) -O binary $^ $@

-include $(DEP)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	-rm -f *.o *.elf *.bin *.map
