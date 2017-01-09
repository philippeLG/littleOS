#include "io.h"
#include "serial.h"
#include "framebuffer.h"
#include "keyboard.h"
#include "memory_segments.h"
#include "interrupts.h"

/**************************************************************************/

int sum_of_three(int arg1, int arg2, int arg3)
{
	return arg1 + arg2 + arg3;
}

/***************************************************************************/

char myname[] = "Test";


void kmain()
{
	fb_clear();
	fb_write_str(myname,4);
	serial_write(myname,4);
	segments_install_gdt();
	interrupts_install_idt();
	
	/*char code = keyboard_read_scan_code();
	serial_write(&code,2);*/
}
