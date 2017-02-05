// osdev.org - http://wiki.osdev.org/Setting_Up_Paging 
//             http://wiki.osdev.org/Paging
//             http://wiki.osdev.org/Page_Tables
// http://www.jamesmolloy.co.uk/tutorial_html/6.-Paging.html
//
#define NUM_PAGES 1024
#define PAGE_FRAME_SIZE 4096

extern void enablePaging(unsigned int*);

// paging mode : 
// NON PAE 4K Mode (32 bit) - level 0 page, 1 PT, 2 PD 
// NON PAE 4M Mode (32 bit) - level 0 page, 2 PD 
// PAE 4K Mode (32 bit) - level 0 page, 1 PT, 2 PD, 3 PDP 
// PAE 4M Mode (32 bit) - level 0 page, 2 PD, 3 PDP
// LONG MODE 4K (64 bit) - level 0 page, 1 PT, 2 PD, 3 PDP, 4 PML4

// page directory structure 32 bits :
// 0 present        : 1;   // Page present in memory
// 1 rw             : 1;   // Read-only if clear, readwrite if set
// 2 user           : 1;   // Supervisor level only if clear
// 3 Write through  : 1 
// 4 cache disabled : 1
// 5 accessed       : 1;   // Has the page been accessed since last refresh?
// 6 page size      : 1;   // 0 for 4KB
// 7 dirty          : 1;   // Has the page been written to since last refresh?
// 8 unused         : 3;   // Amalgamation of unused and reserved bits
// 12 frame         : 20;  // Frame address (shifted right 12 bits)

// page structure 32 bits :
// 0 present        : 1;   // Page present in memory
// 1 rw             : 1;   // Read-only if clear, readwrite if set
// 2 user           : 1;   // Supervisor level only if clear
// 3 Write through  : 1 
// 4 cache disabled : 1
// 5 accessed       : 1;   // Has the page been accessed since last refresh?
// 6 page size      : 1;   // 0 for 4KB
// 7 dirty          : 1;   // Has the page been written to since last refresh?
// 8 unused         : 3;   // Amalgamation of unused and reserved bits
// 12 frame         : 20;  // Frame address (shifted right 12 bits)

unsigned int page_directory[NUM_PAGES] __attribute__((aligned(PAGE_FRAME_SIZE)));
unsigned int page_table[NUM_PAGES] __attribute__((aligned(PAGE_FRAME_SIZE)));


void init_paging() {

	// Create page directory, supervisor mode, read/write, not present : 0 1 0 = 2   
	for (int i = 0; i < NUM_PAGES; i++) {
        page_directory[i] = 0x00000002;    
     }     

    // Create page table, supervisor mode, read/write, present : 0 1 1 = 3   
    // As the address is page aligned, it will always leave 12 bits zeroed.  
    for (int i = 0; i < NUM_PAGES; i++) { 
        page_table[i] = (i * 0x1000) | 3;
    }

    // put page_table into page_directory supervisor level, read/write, present
    page_directory[0] = ((unsigned int)page_table) | 3;
	 	
   	enablePaging(page_directory);

   	//register_interrupt_handler(14, handle_page_fault);
}