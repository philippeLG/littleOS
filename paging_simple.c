// osdev.org - http://wiki.osdev.org/Setting_Up_Paging 
//             http://wiki.osdev.org/Paging
//             http://wiki.osdev.org/Page_Tables
// 1ere version : creation page table + page directory 
#include "paging.h"
#include "serial.h" // pour afficher un msg



extern void enablePaging(unsigned int*);

// paging mode : 
// NON PAE 4K Mode (32 bit) - level 0 page, 1 PT, 2 PD 
// NON PAE 4M Mode (32 bit) - level 0 page, 2 PD 
// PAE 4K Mode (32 bit) - level 0 page, 1 PT, 2 PD, 3 PDP 
// PAE 4M Mode (32 bit) - level 0 page, 2 PD, 3 PDP
// LONG MODE 4K (64 bit) - level 0 page, 1 PT, 2 PD, 3 PDP, 4 PML4


unsigned int page_directory[NUM_PAGES] __attribute__((aligned(PAGE_FRAME_SIZE)));
unsigned int page_table[NUM_PAGES] __attribute__((aligned(PAGE_FRAME_SIZE)));


void init_paging() {
	int i;

	// Create page directory, supervisor mode, read/write, not present : 0 1 0 = 2   
	for (i = 0; i < NUM_PAGES; i++) {
		page_directory[i] = 0x00000002;
        //page_directory[i] = (unsigned int)directory;    
     	}     

	// Create page table, supervisor mode, read/write, present : 0 1 1 = 3   
	// As the address is page aligned, it will always leave 12 bits zeroed.  
	for (i = 0; i < NUM_PAGES; i++) { 
	        page_table[i] = (i * 0x1000) | 3;
	}	

	// put page_table into page_directory supervisor level, read/write, present
	page_directory[0] = ((unsigned int)page_table) | 3;
	 	
   	enablePaging(page_directory);

   	//register_interrupt_handler(14, handle_page_fault);
}

void page_fault() {
	char message[]= "Page Fault";
	serial_write(message,sizeof(message));
}
