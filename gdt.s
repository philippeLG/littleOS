;Load the Global Descriptor Table

global segments_load_gdt
global segments_load_registers

segments_load_gdt:
	lgdt [esp + 4]
	ret

segments_load_registers:
	mov ax, 0x10
	mov ds, ax ; 0x10 - an offset into GDT for the third (kernel data segment) record.
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	jmp 0x08:flush_cs ; 0x08 - an offset into GDT for the second (kernel code segment) record. 

flush_cs:
	ret
