#include "io.h"
#include "framebuffer.h"

/* ------------------------------------------------------------------------- */
/* ----------------------  Framebuffer --------------------------------------*/
/* ------------------------------------------------------------------------- */
unsigned short __fb_present_pos = 0x00000000;

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos)
{
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
        outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
        outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
        outb(FB_DATA_PORT,    pos & 0x00FF);
	__fb_present_pos = pos;
}

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
	char *fb = (char *) FRAMEBUFFER_ADDRESS;
	fb[i] = c;
        fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void fb_write_simple()
{
	fb_write_cell(0, 'T', FB_GREEN, FB_DARK_GREY);
}

int fb_write_str(char *buf, unsigned int len) {
	
	unsigned int i;
	for(i=0; i<len; i++) {
		
		/* Write character at position i */
		fb_write_cell(2*__fb_present_pos, buf[i], FB_GREEN, FB_DARK_GREY);
		fb_move_cursor(__fb_present_pos + 1);
		
		}		
	return len;
}

void fb_clear(){
  /*char *fb=(char *)FRAMEBUFFER_ADDRESS;*/
  
  unsigned int i=0;
  while(i<80*25*2) {
  	    fb_write_cell(2*i, ' ', FB_BLACK, FB_BLACK);
    	i=i+1;
  }
  return;
}
