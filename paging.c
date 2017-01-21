// osdev.org - http://wiki.osdev.org/Setting_Up_Paging and http://wiki.osdev.org/Paging
#define NUM_PAGES 1024

extern void enablePaging(unsigned int*);

unsigned int page_directory[NUM_PAGES] __attribute__((aligned(4096)));
unsigned int page_table[NUM_PAGES] __attribute__((aligned(4096)));

void enable_paging() {
    for (int i = 0; i < NUM_PAGES; i++) {
        // This sets the following flags to the pages:
        //   Supervisor: Only kernel-mode can access them
        //   Write Enabled: It can be both read from and written to
        //   Not Present: The page table is not present
        page_directory[i] = 0x00000002;
    }

    for (int i = 0; i < NUM_PAGES; i++) { // We want to start mapping the pages at the beginning of memory
        // As the address is page aligned, it will always leave 12 bits zeroed
        // to be used as attributes. 
        page_table[i] = (i << 12) | 3;
    }
    
    page_directory[0] = ((unsigned int)page_table) | 3;
    
    enablePaging(page_directory);

}
