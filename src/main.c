#include <system.h>
extern int attrib;
extern int MAX_CMD;
extern char *cmd[];


void *memcpy(void *dest, const void *src, size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}
int strlen(const char *str)
{
    /* This loops through character array 'str', returning how
    *  many characters it needs to check before it finds a 0.
    *  In simple words, it returns the length in bytes of a string */
    int rval=0;
    for(;*str!='\0';str++) rval++;
    //rval--;
    return(rval);

}
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}


// Compare two strings. Should return -1 if
// str1 < str2, 0 if they are equal or 1 otherwise.
int strcmp(char *str1, char *str2)
{
      int i = 0;
      int failed = 0;
      while(str1[i] != '\0' && str2[i] != '\0')
      {
          if(str1[i] != str2[i])
          {
              failed = 1;
              break;
          }
          i++;
      }
      // why did the loop exit?
      if( (str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0') )
          failed = 1;

      return failed;
}


// Concatenate the NULL-terminated string src onto
// the end of dest, and return dest.
char *strcat(char *dest, const char *src)
{
    while (*dest != 0)
    {
        dest++;
    }

    do
    {
        *dest++ = *src++;
    }
    while (*src != 0);
    return dest;
}


int pow(int i,int j)
{
	int x=1;
	puts("inside POW();");
	printf("pow(%d,",i);printf("%d)=",j);

	while(j!=0)
	{
		x=x*i;
		j--;
	}
printf("[%d]",x);
	return(x);
}

int atoi(unsigned char *s1,int base)
{

if(base < 2 || base > 35) return 0;

	int i=0,j=0,k=0,l=0;
	puts("\nFIND ATOI for ");puts(s1);
	i=strlen(s1);
	puts("strlen of cmd=");printf("[%d]",i);
	l=i-1;
	do
	{
		j=j+(s1[l]-48)*pow(base,k);
		printf("j=[%d]\n",j);
		k++;
		l--;
		i--;
	}while(i!=0);

	puts("atoi(");puts(s1);puts(")=");printf("[%d]",j);
	return(j);
}

void strreverse(char *begin, char *end) {
	
	char aux;
	
	while(end>begin)
	{
		aux=*end;
		*end--=*begin;
		*begin++=aux;
	}
	
}
	
void itoa(int value, char *str, int base) 
{
	
	static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";	
	char* wstr=str;	
	int sign;	
	// Validate base	
	if (base<2 || base>35){ *wstr='\0'; return; }	
	// Take care of sign	
	if ((sign=value) < 0) value = -value;	
	// Conversion. Number is reversed.	
	do *wstr++ = num[value%base]; while(value/=base);	
	if(sign<0) *wstr++='-';	
	if(base==16)
	{
		*wstr++='x';
		*wstr++='0';	
	}
	*wstr='\0';	
	// Reverse string	
	strreverse(str,wstr-1);	
}

int strstr(unsigned char *s1,unsigned char *s2)
{
	puts("inside STRSTR():\n");
	int j=0,i=0,temp=0;
while(s1[j]!='\0')
{
	if(s1[j]==s2[i])
	{
		temp=j;
		while((s1[j+i]==s2[i]) && s2[i]!='\0' && s1[j+i]!='\0')
		{
			printf("i=[%d]>",i);putch(s1[j+i]);putch('=');putch(s2[i]);putch('\n');
			i++;
		}
		i++;
		printf("strlen=%d,",strlen(s2));
		if(i==strlen(s2)+1)
		{
			printf("i=[%d]",i);
			puts("returning=1\n");
			//return(temp);
			return(1);
		}
		else
		{
			printf("i=[%d]",i);
			puts("returning=0\n");
			return(0);
		}
	}
	j++;
}

}



void commands(unsigned char *s1)
{
	int flag_cmd=0;
	int i;
//	puts("inside:COMMANDS()\n");

	for(i=0;i<MAX_CMD;i++)
	{
		if(strstr(s1,cmd[i])!=0)
		{
			flag_cmd=1;
			docmdno(i,s1);
			break;
		}
	}
	if(flag_cmd==0)
	{
		//puts("s1[");printf("%d]",strlen(s1));puts("!= ' ' \n");
		puts("\nunknown command type help to see options");
	}

}



extern void panic(const char *message, const char *file, u32int line)
{
    // We encountered a massive problem and have to stop.
    asm volatile("cli"); // Disable interrupts.

    puts("PANIC(");
    puts(message);
    puts(") at ");
    puts(file);
    puts(":");
    puts(line);
    puts("\n");
    // Halt by going into an infinite loop.
    for(;;);
}

extern void panic_assert(const char *file, unsigned int line, const char *desc)
{
    // An assertion failed, and we have to panic.
    asm volatile("cli"); // Disable interrupts.

    puts("ASSERTION-FAILED(");
    puts(desc);
    puts(") at ");
    puts(file);
    puts(":");
    puts(line);
    puts("\n");
    // Halt by going into an infinite loop.
    for(;;);
}



unsigned char *msg[]={

	"VIMAL'S KERNEL.....\n",
	"INSTALLING GDT\n",
	"INSTALLING IDT\n",
	"INSTALLING ISR\n",
	"INSTALLING IRQ\n"
	"INSTALLING TIMER\n"
	"INSTALLING KEYBOARD\n"
	"INSTALLING PAGE DIRECTORY & PAGE TABLE FOR KERNEL\n"
};

void main(struct multiboot *mboot_ptr)
{
	init_video();
	puts("BOCHS IN LINUX :)\n");
	puts(msg[0]);
	/* You would add commands after here */
	puts(msg[1]);
	gdt_install();
	
	puts(msg[2]);
	idt_install();
	
	puts(msg[3]);
	isrs_install();

	puts(msg[4]);
	irq_install();
	
	puts(msg[5]);
	timer_install();
	
	puts(msg[6]);
	keyboard_install();
	/////////////////////////////////////////////////////////////////
	puts(msg[7]);
	initialise_paging();

	puts("Enabling all interuppts...\n");
	__asm__ __volatile__ ("sti");

	puts("Hello, paging world!\n");


	int i;
	unsigned int *ptr = (u32int*)0xA0000000;
	unsigned int do_page_fault;
	do_page_fault = *ptr;
	i=i/0;
	putch(i/0);


    /* ...and leave this loop in. There is an endless loop in
    *  'start.asm' also, if you accidentally delete this next line */
    for (;;);
}


