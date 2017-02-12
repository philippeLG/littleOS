#ifndef PAGING_H
#define PAGING_H

#define PRESENT         1
#define PAGE_READONLY   0
#define PAGE_READWRITE  1
#define PAGE_USER       1
#define PAGE_KERNEL     0
#define PAGE_SIZE_4KB   0
#define PAGE_SIZE_4MB   1

struct directory {
  unsigned char present:1;        //  0: 1 if present
  unsigned char rw:1;             //  1: Read-only if 0, readwrite if 1 
  unsigned char us:1;             //  2: 1 user or 0 supervisor 
  unsigned char pwt:1;            //  3: page-level write-through
  unsigned char pcd:1;            //  4: page-level cache disable
  unsigned char a:1;              //  5: accessed since last refresh
  unsigned char ignored:1;        //  6:
  unsigned char ps:1;             //  7: page size, 0=4KB 1=4MB
  unsigned char ignored2:4;       //  8 - 11
  unsigned int page_table:20;     //  12 - 31: physical address of 4KB aligned page table referenced by this entry
} __attribute__((packed));
typedef struct directory directory_t;

struct page {
  unsigned char present:1;        //  0: 1 if present
  unsigned char rw:1;             //  1: Read-only if 0, readwrite if 1
  unsigned char us:1;             //  2: 1 user or 0 supervisor 
  unsigned char pwt:1;            //  3: page-level write-through
  unsigned char pcd:1;            //  4: page-level cache disable
  unsigned char a:1;              //  5: accessed
  unsigned char d:1;              //  6: dirty, as the page been written to since last refresh?
  unsigned char pat:1;            //  7: must be 0 unless PAT supported
  unsigned char g:1;              //  8: global translation
  unsigned char ignored2:3;       //  9 - 11
  unsigned int page_frame:20;     //  12 - 31: physical address of 4KB page frame
} __attribute__((packed));
typedef struct page page_t;

/**
  Sets up the environment, page directories etc and
  enables paging.
**/
void init_paging();

void page_fault();

#endif
