.suffix:
override OUTPUT := aecore

# using llvm toolchain

CC := clang
AS := llvm-mc
RUSTC := rustc
LD := ld.lld 

# controllable C Flags
CFLAGS := -target x86_64-unknown-none -pipe -O0 -march=native -mtune=native -msse -flto -std=gnu23
ASFLAGS := -filetype=obj -triple x86_64-unknown-none
CPPFLAGS := -Isrc/kernel/libkrn/ -Isrc/kernel/ -masm=intel
LDFLAGS := -O2

RUST_TARGET := x86_64-unknown-none

RUSTFLAGS := \
		--target $(RUST_TARGET) \
		--edition 2024 \
		-C opt-level=0 \
		-C panic=abort \
		-C relocation-model=static \
		-C code-model=kernel \
		-C target-feature=+sse,-avx,-avx2 \
		--emit obj \
		-C debuginfo=0 \
		-C lto=fat

RUST_SYSROOT := $(shell rustc --print sysroot)

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

override SRCFILES := $(shell find -L src/kernel -type f 2>/dev/null | LC_ALL=C sort)
override CFILES := $(filter %.c,$(SRCFILES))
override ASFILES := $(filter %.s,$(SRCFILES))

# Rust build
RUST_KERNEL := src/kernel/core/rust.rs
RUST_KERNEL_OBJ := src/kernel/core/rust.o

override OBJ = $(addprefix target/obj/,$(CFILES:.c=.c.o) $(ASFILES:.s=.s.o) $(RUST_KERNEL_OBJ))
override HEADER_DEPS := $(addprefix target/obj/,$(CFILES:.c=.c.d) $(ASFILES:.s=.s.d))

.PHONY: all
all: target/bin/$(OUTPUT)

target/obj/$(RUST_KERNEL_OBJ): $(RUST_KERNEL) GNUmakefile
		mkdir -p "$(dir $@)"
		$(RUSTC) $(RUSTFLAGS) \
			--crate-type staticlib \
			--extern core=$(RUST_SYSROOT)/lib/rustlib/x86_64-unknown-none/lib/libcore-7fdbb61355ee61c7.rlib \
			--extern core=$(RUST_SYSROOT)/lib/rustlib/x86_64-unknown-none/lib/libcore-7fdbb61355ee61c7.rmeta \
			--extern compiler_builtins=$(RUST_SYSROOT)/lib/rustlib/x86_64-unknown-none/lib/libcompiler_builtins-108e80388f1e02eb.rlib \
			--extern compiler_builtins=$(RUST_SYSROOT)/lib/rustlib/x86_64-unknown-none/lib/libcompiler_builtins-108e80388f1e02eb.rmeta \
			-o $@ $(RUST_KERNEL)

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

limine-protocol:
		git clone --dept=1  https://codeberg.org/Limine/limine-protocol.git ./limine-protocol

.PHONY: clean
clean:
		rm -rf target aeonx.iso rootfs limine limine-protocol
