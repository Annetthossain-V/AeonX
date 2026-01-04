.suffix:

override OUTPUT := aecore

# using llvm toolchain
CC := clang
LD := ld.lld

# controllable C Flags
CFLAGS := -O0 -pipe -flto -Wno-unused-parameter -msse4.2 -march=native -mtune=native

CPPFLAGS := -Isrc/kernel/libkrn/ -Isrc/kernel/ -masm=intel
NASMFLAGS :=
LDFLAGS := -O2

# target
override CC += -target x86_64-unknown-none-elf
override CXX += -target x86_64-unknown-none-elf

# internal C flags that should not change
# fno-lto -mno-sse
compiler := -Wall \
		-Wextra	\
		-ffreestanding \
		-fno-stack-protector \
		-fno-stack-check \
		-fno-PIC \
		-ffunction-sections \
		-fdata-sections \
		-m64 \
		-march=x86-64 \
		-mabi=sysv \
		-mno-80387 \
		-mno-mmx \
		-mno-red-zone \
		-mcmodel=kernel

override CFLAGS += \
				$(compiler) \
				-std=gnu11


# internal C preprocessor flags that should not be changed
override CPPFLAGS += \
		-I src \
		-DLIMINE_API_REVISION=3 \
		-MMD \
		-MP \
		-I limine

override NASMFLAGS := \
		-f elf64 \
		-Wall

override LDFLAGS += \
		-m elf_x86_64 \
		-nostdlib \
		-static \
		-z max-page-size=0x1000 \
		--gc-sections \
		-T linker.lds

override SRCFILES := $(shell find -L src/kernel -type f 2>/dev/null | LC_ALL=C sort)
override CFILES := $(filter %.c,$(SRCFILES))
override ASFILES := $(filter %.S,$(SRCFILES))
override NASMFILES := $(filter %.asm,$(SRCFILES))
override OBJ = $(addprefix obj/,$(CFILES:.c=.c.o) $(ASFILES:.S=.S.o) $(NASMFILES:.asm=.asm.o))
	override HEADER_DEPS := $(addprefix obj/,$(CFILES:.c=.c.d) $(ASFILES:.S=.S.d) $(NASMFILES:.asm=.asm.d))

.PHONY: all
all: bin/$(OUTPUT)

-include $(HEADER_DEPS)

bin/$(OUTPUT): GNUmakefile linker.lds $(OBJ)
		mkdir -p "$(dir $@)"
		$(LD) $(LDFLAGS) $(OBJ) -o $@

obj/%.c.o: %.c GNUmakefile
		mkdir -p "$(dir $@)"
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

obj/%.S.o: %.S GNUmakefile
		mkdir -p "$(dir $@)"
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

obj/%.asm.o: %.asm GNUmakefile
		mkdir -p "$(dir $@)"
		nasm $(NASMFLAGS) $< -o $@

.PHONY: clean
clean:
		rm -rf bin obj
