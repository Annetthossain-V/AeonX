.suffix:

override OUTPUT := aecore

# using gnu toolchain
# release builds still should be using clang
TOOLCHAIN_PREFIX = x86_64-elf

CC := $(TOOLCHAIN_PREFIX)-gcc
CXX := $(TOOLCHAIN_PREFIX)-g++
AS := $(TOOLCHAIN_PREFIX)-as
LD := $(TOOLCHAIN_PREFIX)-ld

# CC_RELEASE := clang
# CXX_RELEASE := clang++
# AS_RELEASE := llvm-mc
# LD_RELEASE := ld.lld

# controllable C Flags
CC_COMMON := -pipe -O2 -msse4.2 -march=native -mtune=native -finline-functions
CFLAGS := $(CC_COMMON) -std=c23
CXXFLAGS := $(CC_COMMON) -std=c++23
ASFLAGS := -O2 -mtune=corei7
CPPFLAGS := -Isrc/kernel/libkrn/ -Isrc/kernel/ -masm=intel
LDFLAGS := -O2

# target (not needed anymore since we're using gcc now)
# override CC += -target x86_64-unknown-none-elf
# override CXX += -target x86_64-unknown-none-elf
# override AS += -filetype=obj -triple=x86_64-unknown-none --mattr=+sse,+sse2,+sse3,+sse4.2,-avx

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
		-mcmodel=kernel \
		-fno-lto

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

override SRCFILES := $(shell find -L src/kernel -type f 2>/dev/null | LC_ALL=C sort)
override CFILES := $(filter %.c,$(SRCFILES))
override ASFILES := $(filter %.s,$(SRCFILES))
override CXXFILES := $(filter %.cc,$(SRCFILES))
override OBJ = $(addprefix target/obj/,$(CFILES:.c=.c.o) $(ASFILES:.s=.s.o) $(CXXFILES:.cc=.cc.o))
override HEADER_DEPS := $(addprefix target/obj/,$(CFILES:.c=.c.d) $(ASFILES:.s=.s.d) $(CXXFILES:.cc=.cc.d))

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
		$(AS) $(ASFLAGS) $< -o $@

target/obj/%.cc.o: %.cc GNUmakefile
		mkdir -p "$(dir $@)"
		$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

limine-protocol:
		git clone --dept=1  https://codeberg.org/Limine/limine-protocol.git ./limine-protocol

.PHONY: clean
clean:
		rm -rf target aeonx.iso rootfs limine limine-protocol
