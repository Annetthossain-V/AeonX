.suffix:
override OUTPUT := aecore

# using llvm toolchain

CC := icx
AS := icx
LD := ld.lld 

# controllable C Flags
CFLAGS := -target x86_64-unknown-none -pipe -O3 -flto -std=gnu17 -march=native -mtune=native
ASFLAGS := -target x86_64-unknown-none
CPPFLAGS := -Ikernel/libkrn/ -Ikernel/ -masm=intel
LDFLAGS := -O2

# internal C flags that should not change
override COMPILER_FLAGS := \
		-Wall \
		-Wextra	\
		-ffreestanding \
		-fno-stack-protector \
		-fno-stack-check \
		-fno-PIC \
		-ffunction-sections \
		-fdata-sections \
		-m64 \
		-mabi=sysv \
		-mno-80387 \
		-mno-mmx \
		-mno-red-zone \
		-mcmodel=kernel \
		-msse4.2

override CFLAGS += $(COMPILER_FLAGS)

# internal C preprocessor flags that should not be changed
override CPPFLAGS += \
		-I src \
		-DLIMINE_API_REVISION=4 \
		-MMD \
		-MP \
		-I limine-protocol/include

override LDFLAGS += \
		-m elf_x86_64 \
		-nostdlib \
		-static \
		-z max-page-size=0x1000 \
		--gc-sections \
		-T linker.lds

override SRCFILES := $(shell find -L kernel/ -type f 2>/dev/null | LC_ALL=C sort)
override CFILES := $(filter %.c,$(SRCFILES))
override ASFILES := $(filter %.s,$(SRCFILES))

override OBJ = $(addprefix target/obj/,$(CFILES:.c=.c.o) $(ASFILES:.s=.s.o))
override HEADER_DEPS := $(addprefix target/obj/,$(CFILES:.c=.c.d) $(ASFILES:.s=.s.d))

.PHONY: all
all: target/bin/$(OUTPUT)

-include $(HEADER_DEPS)

target/bin/$(OUTPUT): GNUmakefile linker.lds limine-protocol  $(OBJ)
		mkdir -p "$(dir $@)"
		$(LD) $(LDFLAGS) $(OBJ) -o $@

target/obj/%.c.o: %.c GNUmakefile
		mkdir -p "$(dir $@)"
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

target/obj/%.s.o: %.s GNUmakefile
		mkdir -p "$(dir $@)"
		$(AS) $(ASFLAGS) -c $< -o $@

limine-protocol:
		git clone --dept=1  https://codeberg.org/Limine/limine-protocol.git ./limine-protocol

.PHONY: clean
clean:
		rm -rf target aeonx.iso rootfs limine limine-protocol
