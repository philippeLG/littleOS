#ifndef PAGING_H
#define PAGING_H

// paging mode : 
// NON PAE 4K Mode (32 bit) - level 0 page, 1 PT, 2 PD  <--  
// NON PAE 4M Mode (32 bit) - level 0 page, 2 PD 
// PAE 4K Mode (32 bit) - level 0 page, 1 PT, 2 PD, 3 PDP 
// PAE 4M Mode (32 bit) - level 0 page, 2 PD, 3 PDP
// LONG MODE 4K (64 bit) - level 0 page, 1 PT, 2 PD, 3 PDP, 4 PML4


#define NUM_PAGES 1024
#define PAGE_FRAME_SIZE 4096

#define PRESENT         1
#define PAGE_READONLY   0
#define PAGE_READWRITE  1
#define PAGE_USER       1
#define PAGE_KERNEL     0
#define PAGE_SIZE_4KB   0
#define PAGE_SIZE_4MB   1

typedef struct page
{
   unsigned int present    : 1;   // Page present in memory
   unsigned int rw         : 1;   // Read-only if clear, readwrite if set
   unsigned int user       : 1;   // Supervisor level only if clear
   unsigned int accessed   : 1;   // Has the page been accessed since last refresh?
   unsigned int dirty      : 1;   // Has the page been written to since last refresh?
   unsigned int unused     : 7;   // Amalgamation of unused and reserved bits
   unsigned int frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
   page_t pages[1024] __attribute__((aligned(4096)));
} page_table_t;

typedef struct page_directory
{
   /**
      Array of pointers to pagetables.
   **/
   page_table_t *tables[1024];
   /**
      Array of pointers to the pagetables above, but gives their *physical*
      location, for loading into the CR3 register.
   **/
   unsigned int tablesPhysical[1024];
   /**
      The physical address of tablesPhysical. This comes into play
      when we get our kernel heap allocated and the directory
      may be in a different location in virtual memory.
   **/
   unsigned int physicalAddr;
} page_directory_t;



/**
  Sets up the environment, page directories etc and
  enables paging.
**/
void init_paging();

void page_fault();

#endif
