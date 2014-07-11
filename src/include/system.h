
#ifndef __SYSTEM_H
#define __SYSTEM_H

typedef int size_t;

#define true 1
#define false 0
#define yes 1
#define no 0

typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};

struct time{
	unsigned int sec,min,hr;
};


extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, char val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern size_t strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);
extern void commands(unsigned char *s1);
extern int strstr(unsigned char *s1,unsigned char *s2);
extern void itoa(int value, char *str, int base);
extern int pow(int i,int j);
extern void strreverse(char *begin, char *end);
extern int atoi(unsigned char *s1,int base);


extern int strcmp(char *str1, char *str2);
extern char *strcat(char *dest, const char *src);


/* CONSOLE.C */
extern void init_video(void);
extern void puts(unsigned char *text);
extern void putch(unsigned char c);
extern void cls();
extern void show_time(struct time);
extern void printf(char *str,int x);
extern void showint(unsigned int x);
extern void showhex(unsigned int x);
extern void show_char(char x);
extern void goto_xy(unsigned int x,unsigned int y);
extern void new_prompt();

/* GDT.C */
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_install();

/* IDT.C */
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

/* ISRS.C */
extern void isrs_install();

/* IRQ.C */
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();

/* TIMER.C */
extern void delay_seconds(unsigned int ticks);
extern void timer_install();
extern void timer_phase(int hz,int port);

/* KEYBOARD.C */
extern void keyboard_install();
extern void update_LED();
extern void wait_kbd();
extern void SpecialKeyScanCode();
extern void check_kbd();
extern void de_kbd();
////////////////////////////////////////////////////////////
/* CMD.C */
extern void cmd_setscrcolor(unsigned char *s1);
extern void cmd_help();
extern void docmdno(int ,unsigned char *);
//////////////////////////////////////////////////////////


void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

extern void panic(const char *message, const char *file, u32int line);
extern void panic_assert(const char *file, u32int line, const char *desc);
/////////////////////////////////////////////////////////////////////
/* paging.c */
typedef struct page
{
    u32int present    : 1;   // Page present in memory
    u32int rw         : 1;   // Read-only if clear, readwrite if set
    u32int user       : 1;   // Supervisor level only if clear
    u32int accessed   : 1;   // Has the page been accessed since last refresh?
    u32int dirty      : 1;   // Has the page been written to since last refresh?
    u32int unused     : 7;   // Amalgamation of unused and reserved bits
    u32int frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
    page_t pages[1024];
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
    u32int tablesPhysical[1024];

    /**
       The physical address of tablesPhysical. This comes into play
       when we get our kernel heap allocated and the directory
       may be in a different location in virtual memory.
    **/
    u32int physicalAddr;
} page_directory_t;

/**
   Sets up the environment, page directories etc and
   enables paging.
**/
void initialise_paging();

/**
   Causes the specified page directory to be loaded into the
   CR3 register.
**/
void switch_page_directory(page_directory_t *new);

/**
   Retrieves a pointer to the page required.
   If make == 1, if the page-table in which this page should
   reside isn't created, create it!
**/
page_t *get_page(u32int address, int make, page_directory_t *dir);

/**
   Handler for page faults.
**/
void page_fault();
//////////////////////////////////////////////////////////////////////////////
/* kheap.c */

/**
   Allocate a chunk of memory, sz in size. If align == 1,
   the chunk must be page-aligned. If phys != 0, the physical
   location of the allocated chunk will be stored into phys.

   This is the internal version of kmalloc. More user-friendly
   parameter representations are available in kmalloc, kmalloc_a,
   kmalloc_ap, kmalloc_p.
**/
unsigned int kmalloc_int(u32int sz, int align, u32int *phys);

/**
   Allocate a chunk of memory, sz in size. The chunk must be
   page aligned.
**/
unsigned int kmalloc_a(u32int sz);

/**
   Allocate a chunk of memory, sz in size. The physical address
   is returned in phys. Phys MUST be a valid pointer to u32int!
**/
unsigned int kmalloc_p(u32int sz, u32int *phys);

/**
   Allocate a chunk of memory, sz in size. The physical address
   is returned in phys. It must be page-aligned.
**/
unsigned int kmalloc_ap(u32int sz, u32int *phys);

/**
   General allocation function.
**/
unsigned int kmalloc(u32int sz);




#endif
