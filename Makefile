OBJECTS = loader.o kmain.o common.o framebuffer.o io.o serial.o keyboard.o gdt.o memory_segments.o idt.o interrupt_handlers.o interrupts.o pic.o paging_enable.o paging.o kheap.o  
CC = gcc
CFLAGS = -m32 -nostdlib -fno-builtin -fno-stack-protector \
         -Wno-unused -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -masm=intel 
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
            -b boot/grub/stage2_eltorito    \
            -no-emul-boot                   \
            -boot-load-size 4               \
            -A os                           \
            -input-charset utf8             \
            -quiet                          \
            -boot-info-table                \
            -o os.iso                       \
            iso


#run: os.iso
#	bochs -f bochsrc.txt -q
run: os.iso
	qemu-system-i386 -enable-kvm -boot d -cdrom os.iso -m 4 -serial stdio
run_debug: os.iso
	qemu-system-i386 -enable-kvm -boot d -cdrom os.iso -m 4 -monitor stdio

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf os.iso
