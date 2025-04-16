# === Collect source files ===

# Kernel C files (including subdirectories)
kernel_source_files := $(shell find src/impl/kernel -name *.c)
kernel_object_files := $(patsubst src/impl/kernel/%.c, build/kernel/%.o, $(kernel_source_files))

# Kernel ASM files (.s files like irq.s)
kernel_asm_source_files := $(shell find src/impl/kernel/asm -name *.s)
kernel_asm_object_files := $(patsubst src/impl/kernel/%.s, build/kernel/%.o, $(kernel_asm_source_files))

# x86_64 C and ASM files (already existing)
x86_64_c_source_files := $(shell find src/impl/x86_64 -name *.c)
x86_64_c_object_files := $(patsubst src/impl/x86_64/%.c, build/x86_64/%.o, $(x86_64_c_source_files))

x86_64_asm_source_files := $(shell find src/impl/x86_64 -name *.asm)
x86_64_asm_object_files := $(patsubst src/impl/x86_64/%.asm, build/x86_64/%.o, $(x86_64_asm_source_files))

x86_64_object_files := $(x86_64_c_object_files) $(x86_64_asm_object_files)

# === Compilation rules ===

# Kernel C
$(kernel_object_files): build/kernel/%.o : src/impl/kernel/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I src/impl/kernel/include/headers -ffreestanding $(patsubst build/kernel/%.o, src/impl/kernel/%.c, $@) -o $@

# Kernel ASM
$(kernel_asm_object_files): build/kernel/%.o : src/impl/kernel/%.s
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/kernel/%.o, src/impl/kernel/%.s, $@) -o $@

# x86_64 C
$(x86_64_c_object_files): build/x86_64/%.o : src/impl/x86_64/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I src/impl/kernel/include/headers -ffreestanding $(patsubst build/x86_64/%.o, src/impl/x86_64/%.c, $@) -o $@

# x86_64 ASM
$(x86_64_asm_object_files): build/x86_64/%.o : src/impl/x86_64/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/x86_64/%.o, src/impl/x86_64/%.asm, $@) -o $@

# === Final kernel build ===

.PHONY: build-x86_64
build-x86_64: $(kernel_object_files) $(kernel_asm_object_files) $(x86_64_object_files)
	mkdir -p dist/x86_64 && \
	x86_64-elf-ld -n -o dist/x86_64/kernel.bin -T targets/x86_64/linker.ld $(kernel_object_files) $(kernel_asm_object_files) $(x86_64_object_files) && \
	cp dist/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/kernel.iso targets/x86_64/iso
