rwildcard = $(foreach d, $(wildcard $1*), $(filter $(subst *, %, $2), $d) $(call rwildcard, $d/, $2))

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/base_tools

name := Instalador

dir_source := source
dir_build := build
dir_out := out

ASFLAGS := -mcpu=arm946e-s
CFLAGS := -Wall -Wextra -MMD -MP -marm $(ASFLAGS) -fno-builtin -fshort-wchar -std=c11 -Wno-main -O2 -flto -ffast-math
LDFLAGS := -nostartfiles

objects= $(patsubst $(dir_source)/%.s, $(dir_build)/%.o, \
         $(patsubst $(dir_source)/%.c, $(dir_build)/%.o, \
	 $(call rwildcard, $(dir_source), *.s *.c)))

.PHONY: all
all: a9lh 

.PHONY: a9lh
a9lh: $(dir_out)/instalador.bin

.PHONY: clean
clean:
	@rm -rf $(dir_out) $(dir_build)

$(dir_out) $(dir_build):
	@mkdir -p "$@"

$(dir_out)/instalador.bin: $(dir_build)/main.bin $(dir_out)
	@cp -av $(dir_build)/main.bin $@

$(dir_build)/main.bin: $(dir_build)/main.elf
	$(OBJCOPY) -S -O binary $< $@

$(dir_build)/main.elf: $(objects)
	$(LINK.o) -T linker.ld $(OUTPUT_OPTION) $^

$(dir_build)/memory.o $(dir_build)/strings.o: CFLAGS += -O3
$(dir_build)/main.o: CFLAGS += 

$(dir_build)/%.o: $(dir_source)/%.c
	@mkdir -p "$(@D)"
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(dir_build)/%.o: $(dir_source)/%.s
	@mkdir -p "$(@D)"
	$(COMPILE.s) $(OUTPUT_OPTION) $<
