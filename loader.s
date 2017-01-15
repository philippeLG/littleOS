global loader                   ; the entry symbol for ELF

extern kmain 

KERNEL_STACK_SIZE equ 4096      ; size of stack in bytes

MAGIC_NUMBER    equ 0x1BADB002     ; define the magic number constant
FLAGS           equ 0x00000001     ; 1 : tell GRUB to align modules

CHECKSUM        equ -(MAGIC_NUMBER + FLAGS ) ; calculate the checksum (all options + checksum should equal 0)


section .bss
align 4                         ; align at 4 bytes
kernel_stack:                   ; label points to beginning of memory
    resb KERNEL_STACK_SIZE      ; reserve stack for the kernel

section .text:                  ; start of the text (code) section
align 4                         ; the code must be 4 byte aligned
    dd MAGIC_NUMBER             ; write the magic number to the machine code,
    dd FLAGS                    ; the flags,
    dd CHECKSUM                 ; and the checksum

mov esp, kernel_stack + KERNEL_STACK_SIZE       ; point esp to the start of the
                                                ; stack (end of memory area)
loader:                         ; the loader label (defined as entry point in linker script)
    mov eax, 0xCAFEBABE         ; place the number 0xCAFEBABE in the register eax
    
    add  esp, 4
    push ebx                    ; multiboot info in ebx 
    call kmain
   
.loop:
    jmp .loop                   ; loop forever

