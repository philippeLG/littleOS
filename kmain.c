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

char message[]= "Little OS";



void kmain()
{
	/*fb_clear();*/
	fb_move_cursor(6*80);
	fb_write_str(message,sizeof(message));
	serial_write(message,sizeof(message));
	segments_install_gdt();
	interrupts_install_idt();
}
