SOURCES=start.o main.o scrn.o gdt.o idt.o isrs.o irq.o timer.o kb.o kheap.o paging.o cmd.o

CFLAGS=-nostdlib -nostdinc -fno-builtin
LDFLAGS=-Tlink.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
	
#kernel.bin:start.o main.o scrn.o gdt.o idt.o isrs.o irq.o timer.o kb.o kheap.o paging.o
#	ld -T link.ld -o kernel.bin start.o main.o scrn.o gdt.o idt.o isrs.o irq.o timer.o kb.o kheap.o paging.o
	
#start.o:start.asm
#	nasm -felf -o start.o start.asm
	
main.o:main.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o main.o main.c
	
scrn.o :scrn.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o scrn.o scrn.c
	
gdt.o :gdt.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o gdt.o gdt.c
	
idt.o :idt.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o idt.o idt.c
	
isrs.o :isrs.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o isrs.o isrs.c
	
irq.o :irq.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o irq.o irq.c
	
timer.o :timer.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o timer.o timer.c
	
kb.o :kb.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o kb.o kb.c
	
kheap.o :kheap.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o kheap.o kheap.c
	
paging.o :paging.c
	gcc -Wall -O -fstrength-reduce -finline-functions -nostdinc -fno-builtin -I./include -c -o paging.o paging.c
	
cmd.o :cmd.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o cmd.o cmd.c	
