// kheap.c -- Kernel heap functions, also provides
//            a placement malloc() for use before the heap is
//            initialised.
//            Written for JamesM's kernel development tutorials.

#include<system.h>

// end is defined in the linker script.
extern unsigned int end;
unsigned int placement_address = (unsigned int)&end;

unsigned int kmalloc_int(u32int sz, int align, u32int *phys)
{
	printf("placement_address:[%x]\n",placement_address);
    // This will eventually call malloc() on the kernel heap.
    // For now, though, we just assign memory at placement_address
    // and increment it by sz. Even when we've coded our kernel
    // heap, this will be useful for use before the heap is initialised.
    if (align == 1 && (placement_address & 0xFFFFF000) )
    {
        // Align the placement address;
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    if (phys)
    {
        *phys = placement_address;
    }
    u32int tmp = placement_address;
    placement_address += sz;
    return tmp;
}

unsigned int kmalloc_a(u32int sz)
{
    return kmalloc_int(sz, 1, 0);
}

unsigned int kmalloc_p(u32int sz, u32int *phys)
{
    return kmalloc_int(sz, 0, phys);
}

unsigned int kmalloc_ap(u32int sz, u32int *phys)
{
    return kmalloc_int(sz, 1, phys);
}

unsigned int kmalloc(u32int sz)
{
    return kmalloc_int(sz, 0, 0);
}
