#include"./system.h"

/* These define our textpointer, our background and foreground
*  colors (attributes), and x and y cursor coordinates */
unsigned short *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;
int new_prompt_count=0;

/* Scrolls the screen */
void scroll(void)
{
    unsigned blank, temp;

    /* A blank is defined as a space... we need to give it
    *  backcolor too */
    blank = 0x20 | (attrib << 8);

    /* Row 25 is the end, this means we need to scroll up */
    if(csr_y >= 25)
    {
        /* Move the current text chunk that makes up the screen
        *  back in the buffer by a line */
        temp = csr_y - 25 + 1;
        memcpy (textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);

        /* Finally, we set the chunk of memory that occupies
        *  the last line of text to our 'blank' character */
        memsetw (textmemptr + (25 - temp) * 80, blank, 80);
        csr_y = 25 - 1;
    }
}

/* Updates the hardware cursor: the little blinking line
*  on the screen under the last character pressed! */
void move_csr(void)
{
    unsigned temp;

    /* The equation for finding the index in a linear
    *  chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    temp = csr_y * 80 + csr_x;

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. */
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

void goto_xy(unsigned int x,unsigned int y)
{
	//same as above
    unsigned temp;
    temp = y * 80 + x;
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

/* Clears the screen */
void cls()
{
    unsigned short blank;
    int i;

    /* we need the 'short' that will be used to
    *  represent a space with black color bkground*/
    blank = 0x20 | (attrib << 8);

    /* Sets the entire screen to spaces in our current
    *  color */
    for(i = 0; i < 25; i++)
        memsetw(textmemptr + i * 80, blank, 80);

    /* Update out virtual cursor, and then move the
    *  hardware cursor */
    csr_x = 0;
    csr_y = 0;
    move_csr();
}

/* Puts a single character on the screen */
void putch(unsigned char c)
{
    unsigned short *where;
    unsigned att = attrib << 8;
    unsigned int addr=0;

    /* Handle a backspace, by moving the cursor back one space */
    /*
	*if a bkspace is encountered and if this
    *is not the starting of the line then delete the last char*/
    if(c == 0x08)
    {
		if(!(csr_x < 6 && new_prompt_count == 0))
		{
			if(csr_x != 0)
			{
				csr_x--;
				where = textmemptr + (csr_y * 80 + csr_x);
				*where = 0x20 | att;	/* Character AND attributes: color */

			}
		}
    }
    /* Handles a tab by incrementing the cursor's x, but only
    *  to a point that will make it divisible by 8 */
    else if(c == 0x09)
    {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    /* Handles a 'Carriage Return', which simply brings the
    *  cursor back to the margin */
    else if(c == '\r')
    {
        csr_x = 0;
        new_prompt_count++;
    }
    /* We handle our newlines the way DOS and the BIOS do: we
    *  treat it as if a 'CR' was also there, so we bring the
    *  cursor to the margin and we increment the 'y' value */
    else if(c == '\n')
    {
        csr_x = 0;
        csr_y++;
        new_prompt_count++;
    }


    /* Any character greater than and including a space, is a
    *  printable character. The equation for finding the index
    *  in a linear chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    else if(c >= ' ')
    {
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;	/* Character AND attributes: color */
        csr_x++;
    }

    /* If the cursor has reached the edge of the screen's width, we
    *  insert a new line in there */
    if(csr_x >= 80)
    {
        csr_x = 0;
        csr_y++;
    }

    /* Scroll the screen if needed, and finally move the cursor */
    scroll();
    move_csr();
}

/* Uses the above routine to output a string... */
void puts(unsigned char *text)
{
    int i;

    for (i = 0; i < strlen(text); i++)
    {
        putch(text[i]);
    }
}

/* Sets the forecolor and backcolor that we will use */
void settextcolor(unsigned char forecolor, unsigned char backcolor)
{
    /* Top 4 bytes are the background, bottom 4 bytes
    *  are the foreground color */
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}

/* Sets our text-mode VGA pointer, then clears the screen for us */
void init_video(void)
{
    textmemptr = (unsigned short *)0xB8000;
    cls();
}


void showint(unsigned int x)
{
	int j,k,cnt=0;
	char ch[10];
	while(x!=0)
	{
		j=x;
		j=(j/10)*10;
		k=x-j;
		ch[cnt++]=(k+48);
		x=x/10;
	}
	ch[cnt]='\0';
	cnt--;
	for(;cnt>=0;cnt--)
	{
	putch(ch[cnt]);
	}
}
///////////////////////////////////////////////////////////
void showhex(unsigned int x)
{
	int j,k,cnt=0;
	char ch[10];
	while(x!=0)
	{
		j=x;
		j=(j/16)*16;
		k=x-j;
		if(k>=0 & k<=9) ch[cnt++]=(k+48);
		else if(k>=10 & k<=15) ch[cnt++]=(k-10+65);
		x=x/16;
	}
	ch[cnt++]='x';
	ch[cnt++]='0';

	for(;cnt>=0;cnt--)
	{
	putch(ch[cnt]);
	}
}
/////////////////////////////////////////////////////////
void show_char(char x)
{
	putch(x);
}
/////////////////////////////////////////////////////////
void printf(char *str,int x)
{

int flag_int=0;
char i_str[15];

	for(;(*str)!='\0';str++)
	{
		if((*str)=='%')
		{
		str++;
			switch(*str)
			{
				case('d'):
				{
					flag_int=1;
					//showint(x);
					itoa(x,i_str,10);
					puts(i_str);
					break;
				}
				case('x'):
				{
					flag_int=1;
					//showhex(x);
					itoa(x,i_str,16);
					puts(i_str);
					break;
				}
				case('c'):
				{
					show_char((char)x);
				}
				default:
				{
					str--;
					putch(*str);
				}
			}
		}

		if((*str)>=' ' && flag_int!=1)
		{
			putch(*str);
		}
		if(*str=='\n'||*str=='\b')
		{
			putch(*str);
		}
		flag_int=0;

	}

}
///////////////////////////////////////////////////////////////////
void new_prompt()
{
	puts("\nroot#");
	new_prompt_count=0;
}


