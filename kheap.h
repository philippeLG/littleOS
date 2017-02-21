#ifndef KHEAP_H
#define KHEAP_H

// from http://www.jamesmolloy.co.uk/tutorial_html/6.-Paging.html

#include "common.h"

u32int kmalloc(u32int size);
u32int kmalloc_page(u32int size);

#endif
