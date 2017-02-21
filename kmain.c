#include "io.h"
#include "serial.h"
#include "framebuffer.h"
#include "keyboard.h"
#include "memory_segments.h"
#include "interrupts.h"
#include "multiboot.h"
#include "paging.h"

char message[]= "Little OS";

int kmain(multiboot_info_t *mbinfo)
{
	/* Test appel module 
	module_t* modules = (module_t*) mbinfo->mods_addr;       
	unsigned int address_of_module = modules->mod_start;     

	typedef void (*call_module_t)(void);
	call_module_t start_program = (call_module_t) address_of_module;
    	start_program(); */

	/*fb_clear();*/
	fb_move_cursor(6*80);
	fb_write_str(message,sizeof(message));
	/*fb_write_str("hello\n",5); TODO */
	serial_write(message,sizeof(message));
	segments_install_gdt();
	interrupts_install_idt();
	
	init_paging();
	/* test page fault 	
	unsigned int *ptr = (unsigned int*)0xA0000000;
   	unsigned int do_page_fault = *ptr;*/
	
	return 0;
}
