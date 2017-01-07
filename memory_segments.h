#ifndef INCLUDE_MEMORY_SEGMENTS
#define INCLUDE_MEMORY_SEGMENTS

struct GDT 
{
	unsigned short size;
	unsigned int address;
} __attribute__((packed));

struct GDTDescriptor
{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access_byte;
	unsigned char limit_and_flags;
	unsigned char base_high;
} __attribute__((packed));

void segments_init_descriptor(int index, unsigned int base_address, unsigned int limit, unsigned char access_byte, unsigned char flags);
void segments_install_gdt();

// Wrappers around ASM.
void segments_load_gdt(struct GDT gdt);
void segments_load_registers();

#endif /* INCLUDE_MEMORY_SEGMENTS */

