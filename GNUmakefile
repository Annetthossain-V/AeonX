.suffix:

override OUTPUT := aecore

# using llvm toolchain
CC := clang
CXX := clang++
AS := llvm-mc
LD := ld.lld

# controllable C Flags
CC_COMMON := -pipe -O2 -flto -msse4.2 -march=native -mtune=native -finline-functions
CFLAGS := $(CC_COMMON) -std=gnu23
CXXFLAGS := $(CC_COMMON) -std=gnu++23
ASFLAGS := -filetype=obj -triple=x86_64-unknown-none --mattr=+sse,+sse2,+sse3,+sse4.2,-avx
CPPFLAGS := -Isrc/kernel/libkrn/ -Isrc/kernel/ -masm=intel
LDFLAGS := -O2

# target
override CC += -target x86_64-unknown-none-elf
override CXX += -target x86_64-unknown-none-elf

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
		-march=x86-64 \
		-mabi=sysv \
		-mno-80387 \
		-mno-mmx \
		-mno-red-zone \
		-mcmodel=kernel

override CFLAGS += $(COMPILER_FLAGS)
override CXXFLAGS += $(COMPILER_FLAGS) \
		-fno-rtti \
		-fno-exceptions \
		-fno-unwind-tables \
		-fno-asynchronous-unwind-tables \
		-fno-threadsafe-statics \
		-fno-use-cxa-atexit

# internal C preprocessor flags that should not be changed
override CPPFLAGS += \
		-I src \
		-DLIMINE_API_REVISION=3 \
		-MMD \
		-MP \
		-I limine

override LDFLAGS += \
		-m elf_x86_64 \
		-nostdlib \
		-static \
		-z max-page-size=0x1000 \
		--gc-sections \
		-T linker.lds

override SRCFILES := $(shell find -L src/kernel -type f 2>/dev/null | LC_ALL=C sort)
override CFILES := $(filter %.c,$(SRCFILES))
override ASFILES := $(filter %.s,$(SRCFILES))
override CXXFILES := $(filter %.cc,$(SRCFILES))
override OBJ = $(addprefix target/obj/,$(CFILES:.c=.c.o) $(ASFILES:.s=.s.o) $(CXXFILES:.cc=.cc.o))
override HEADER_DEPS := $(addprefix target/obj/,$(CFILES:.c=.c.d) $(ASFILES:.s=.s.d) $(CXXFILES:.cc=.cc.d))

.PHONY: all
all: target/bin/$(OUTPUT)

-include $(HEADER_DEPS)

target/bin/$(OUTPUT): GNUmakefile linker.lds $(OBJ)
		mkdir -p "$(dir $@)"
		$(LD) $(LDFLAGS) $(OBJ) -o $@

target/obj/%.c.o: %.c GNUmakefile
		mkdir -p "$(dir $@)"
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

target/obj/%.s.o: %.s GNUmakefile
		mkdir -p "$(dir $@)"
		$(AS) $(ASFLAGS) $< -o $@

target/obj/%.cc.o: %.cc GNUmakefile
		mkdir -p "$(dir $@)"
		$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
		rm -rf target aeonx.iso  # rootfs
