#include <system.h>
#include".//include//kb.h"

#define N_Lock 	0x45
#define SC_Lock 0x46
#define CP_Lock 0x3A
#define Alt		0x38
#define Ctrl	0x1D
#define Ins		0x52
#define Del		0x53
#define Home	0x47
#define End		0x4F
#define Pg_Up	0x49
#define Pg_Dn	0x51
#define Left	0x4B
#define Right	0x4D
#define Up		0x48
#define Down	0x50
#define R_Shift	0x36
#define L_Shift	0x2A
#define Bksp	0x0E
#define Kbuf_max 256

extern int new_prompt_count;
unsigned char line_kb_buf[80];
unsigned int CTRL=0,CP_LOCK=0,N_LOCK=0,SC_LOCK=0,MODIFY=0,SHIFT=0,ALT=0;
unsigned short int Kbuf[Kbuf_max],buf_head,buf_tail;
extern unsigned int csr_x,csr_y;
unsigned short int kbdus[]={
/*norm 	shft 	ctrl 	alt 	num 	caps 	sh-cap 	sh-num*/
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,//
0x011b, 0x011b, 0x011b, 0x011b, 0x011b, 0x011b, 0x011b, 0x011b,// ;ESC
0x0231, 0x0221, 0x0000, 0x7800, 0x0231, 0x0231, 0x0231, 0x0321,// ;1 !
0x0332, 0x0340, 0x0300, 0x7900, 0x0332, 0x0332, 0x0332, 0x0332,// ;2 @
0x0433, 0x0423, 0x0000, 0x7a00, 0x0433, 0x0433, 0x0423, 0x0423,// ;3 #
0x0534, 0x0524, 0x0000, 0x7b00, 0x0534, 0x0534, 0x0524, 0x0524,// ;4 $
0x0635, 0x0625, 0x0000, 0x7c00, 0x0635, 0x0635, 0x0625, 0x0625,// ;5 %
0x0736, 0x075e, 0x071e, 0x7d00, 0x0736, 0x0736, 0x075e, 0x075e,// ;6 ^
0x0837, 0x0826, 0x0000, 0x7e00, 0x0837, 0x0837, 0x0826, 0x0826,// ;7 &
0x0938, 0x092a, 0x0000, 0x7f00, 0x0938, 0x0938, 0x092a, 0x092a,// ;8 *
0x0a39, 0x0a28, 0x0000, 0x8000, 0x0a39, 0x0a39, 0x0a28, 0x0a28,// ;9 (
0x0b30, 0x0b29, 0x0000, 0x8100, 0x0b30, 0x0b30, 0x0b29, 0x0b29,// ;0 )
0x0c2d, 0x0c5f, 0x0000, 0x8200, 0x0c2d, 0x0c2d, 0x0c5f, 0x0c5f,// ;- _
0x0d3d, 0x0d2b, 0x0000, 0x8300, 0x0d3d, 0x0d3d, 0x0d2b, 0x0d2b,// ;= +
0x0e08, 0x0e08, 0x0e7f, 0x0000, 0x0e08, 0x0e08, 0x0e08, 0x0e08,// ;bksp
0x0f09, 0x0f00, 0x0000, 0x0000, 0x0f09, 0x0f09, 0x0f00, 0x0f00,// ;Tab
0x1071, 0x1051, 0x1011, 0x1000, 0x1071, 0x1051, 0x1051, 0x1071,// ;Q
0x1177, 0x1057, 0x1017, 0x1100, 0x1077, 0x1057, 0x1057, 0x1077,// ;W
0x1265, 0x1245, 0x1205, 0x1200, 0x1265, 0x1245, 0x1245, 0x1265,// ;E
0x1372, 0x1352, 0x1312, 0x1300, 0x1272, 0x1252, 0x1252, 0x1272,// ;R
0x1474, 0x1454, 0x1414, 0x1400, 0x1474, 0x1454, 0x1454, 0x1474,// ;T
0x1579, 0x1559, 0x1519, 0x1500, 0x1579, 0x1559, 0x1579, 0x1559,// ;Y
0x1675, 0x1655, 0x1615, 0x1600, 0x1675, 0x1655, 0x1675, 0x1655,// ;U
0x1769, 0x1749, 0x1709, 0x1700, 0x1769, 0x1749, 0x1769, 0x1749,// ;I
0x186f, 0x184f, 0x180f, 0x1800, 0x186f, 0x184f, 0x186f, 0x184f,// ;O
0x1970, 0x1950, 0x1910, 0x1900, 0x1970, 0x1950, 0x1970, 0x1950,// ;P
0x1a5b, 0x1a7b, 0x1a1b, 0x0000, 0x1a5b, 0x1a5b, 0x1a7b, 0x1a7b,// ;[ {
0x1b5d, 0x1b7d, 0x1b1d, 0x0000, 0x1b5d, 0x1b5d, 0x1b7d, 0x1b7d,// ;] }
0x1c0d, 0x1c0d, 0x1c0a, 0x0000, 0x1c0d, 0x1c0d, 0x1c0a, 0x1c0a,// ;enter
0x1d00, 0x1d00, 0x1d00, 0x1d00, 0x1d00, 0x1d00, 0x1d00, 0x1d00,// ;ctrl
0x1e61, 0x1e41, 0x1e01, 0x1e00, 0x1e61, 0x1e41, 0x1e61, 0x1e41,// ;A
0x1f73, 0x1f5e, 0x1f13, 0x1f00, 0x1f73, 0x1f53, 0x1f73, 0x1f53,// ;S
0x2064, 0x2044, 0x2004, 0x2000, 0x2064, 0x2044, 0x2064, 0x2044,// ;D
0x2166, 0x2146, 0x2106, 0x2100, 0x2166, 0x2146, 0x2166, 0x2146,// ;F
0x2267, 0x2247, 0x2207, 0x2200, 0x2267, 0x2247, 0x2267, 0x2247,// ;G
0x2368, 0x2348, 0x2308, 0x2300, 0x2368, 0x2348, 0x2368, 0x2348,// ;H
0x246a, 0x244a, 0x240a, 0x2400, 0x246a, 0x244a, 0x246a, 0x244a,// ;J
0x256b, 0x254b, 0x250b, 0x2500, 0x256b, 0x254b, 0x256b, 0x254b,// ;K
0x266c, 0x264c, 0x260c, 0x2600, 0x266c, 0x264c, 0x266c, 0x264c,// ;L
0x273b, 0x273a, 0x0000, 0x0000, 0x273b, 0x273b, 0x273a, 0x273a,// ;; :
0x2827, 0x2822, 0x0000, 0x0000, 0x2827, 0x2827, 0x2822, 0x2822,// ;’ “
0x2960, 0x297e, 0x0000, 0x0000, 0x2960, 0x2960, 0x297e, 0x297e,// ;` ~
0x2a00, 0x2a00, 0x2a00, 0x2a00, 0x2a00, 0x2a00, 0x2a00, 0x2a00,// ;LShf
0x2b5c, 0x2b7c, 0x2b1c, 0x0000, 0x2b5c, 0x2b5c, 0x2b7c, 0x2b7c,// ;\ |
0x2c7a, 0x2c5a, 0x2c1a, 0x2c00, 0x2c7a, 0x2c5a, 0x2c7a, 0x2c5a,// ;Z
0x2d78, 0x2d58, 0x2d18, 0x2d00, 0x2d78, 0x2d58, 0x2d78, 0x2d58,// ;X
0x2e63, 0x2e43, 0x2e03, 0x2e00, 0x2e63, 0x2e43, 0x2e63, 0x2e43,// ;C
0x2f76, 0x2f56, 0x2f16, 0x2f00, 0x2f76, 0x2f56, 0x2f76, 0x2f56,// ;V
0x3062, 0x3042, 0x3002, 0x3000, 0x3062, 0x3042, 0x3062, 0x3042,// ;B
0x316e, 0x314e, 0x310e, 0x3100, 0x316e, 0x314e, 0x316e, 0x314e,// ;N
0x326d, 0x324d, 0x320d, 0x3200, 0x326d, 0x324d, 0x326d, 0x324d,// ;M
0x332c, 0x333c, 0x0000, 0x0000, 0x332c, 0x332c, 0x333c, 0x333c,// ;, <
0x342e, 0x343e, 0x0000, 0x0000, 0x342e, 0x342e, 0x343e, 0x343e,// ;. >
0x352f, 0x353f, 0x0000, 0x0000, 0x352f, 0x352f, 0x353f, 0x353f,// ;/ ?
0x3600, 0x3600, 0x3600, 0x3600, 0x3600, 0x3600, 0x3600, 0x3600,// ;rshf
0x372a, 0x0000, 0x3710, 0x0000, 0x372a, 0x372a, 0x0000, 0x0000,// ;* PS
0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800,// ;alt
0x3920, 0x3920, 0x3920, 0x0000, 0x3920, 0x3920, 0x3920, 0x3920,// ;spc
0x3a00, 0x3a00, 0x3a00, 0x3a00, 0x3a00, 0x3a00, 0x3a00, 0x3a00,// ;caps
0x3b00, 0x5400, 0x5e00, 0x6800, 0x3b00, 0x3b00, 0x5400, 0x5400,// ;F1
0x3c00, 0x5500, 0x5f00, 0x6900, 0x3c00, 0x3c00, 0x5500, 0x5500,// ;F2
0x3d00, 0x5600, 0x6000, 0x6a00, 0x3d00, 0x3d00, 0x5600, 0x5600,// ;F3
0x3e00, 0x5700, 0x6100, 0x6b00, 0x3e00, 0x3e00, 0x5700, 0x5700,// ;F4
0x3f00, 0x5800, 0x6200, 0x6c00, 0x3f00, 0x3f00, 0x5800, 0x5800,// ;F5
0x4000, 0x5900, 0x6300, 0x6d00, 0x4000, 0x4000, 0x5900, 0x5900,// ;F6
0x4100, 0x5a00, 0x6400, 0x6e00, 0x4100, 0x4100, 0x5a00, 0x5a00,// ;F7
0x4200, 0x5b00, 0x6500, 0x6f00, 0x4200, 0x4200, 0x5b00, 0x5b00,// ;F8
0x4300, 0x5c00, 0x6600, 0x7000, 0x4300, 0x4300, 0x5c00, 0x5c00,// ;F9
0x4400, 0x5d00, 0x6700, 0x7100, 0x4400, 0x4400, 0x5d00, 0x5d00,// ;F10
0x4500, 0x4500, 0x4500, 0x4500, 0x4500, 0x4500, 0x4500, 0x4500,// ;num
0x4600, 0x4600, 0x4600, 0x4600, 0x4600, 0x4600, 0x4600, 0x4600,// ;scrl
0x4700, 0x4737, 0x7700, 0x0000, 0x4737, 0x4700, 0x4737, 0x4700,// ;home
0x4800, 0x4838, 0x0000, 0x0000, 0x4838, 0x4800, 0x4838, 0x4800,// ;up
0x4900, 0x4939, 0x8400, 0x0000, 0x4939, 0x4900, 0x4939, 0x4900,// ;pgup
0x4a2d, 0x4a2d, 0x0000, 0x0000, 0x4a2d, 0x4a2d, 0x4a2d, 0x4a2d,// ;-
0x4b00, 0x4b34, 0x7300, 0x0000, 0x4b34, 0x4b00, 0x4b34, 0x4b00,// ;left
0x4c00, 0x4c35, 0x0000, 0x0000, 0x4c35, 0x4c00, 0x4c35, 0x4c00,// ;Center
0x4d00, 0x4d36, 0x7400, 0x0000, 0x4d36, 0x4d00, 0x4d36, 0x4d00,// ;right
0x4e2b, 0x4e2b, 0x0000, 0x0000, 0x4e2b, 0x4e2b, 0x4e2b, 0x4e2b,// ;+
0x4f00, 0x4f31, 0x7500, 0x0000, 0x4f31, 0x4f00, 0x4f31, 0x4f00,// ;end
0x5000, 0x5032, 0x0000, 0x0000, 0x5032, 0x5000, 0x5032, 0x5000,// ;down
0x5100, 0x5133, 0x7600, 0x0000, 0x5133, 0x5100, 0x5133, 0x5100,// ;pgdn
0x5200, 0x5230, 0x0000, 0x0000, 0x5230, 0x5200, 0x5230, 0x5200,// ;ins
0x5300, 0x532e, 0x0000, 0x0000, 0x532e, 0x5300, 0x532e, 0x5300,// ;del
0,0,0,0,0,0,0,0 ,//; --
0,0,0,0,0,0,0,0 ,//; --
0,0,0,0,0,0,0,0 ,//; -
0x5700, 0x0000, 0x0000, 0x0000, 0x5700, 0x5700, 0x0000, 0x0000,// ;F11
0x5800, 0x0000, 0x0000, 0x0000, 0x5800, 0x5800, 0x0000, 0x0000// ;F12

};

struct _KbdFlags1 KFlag1;
struct _KbdFlags2 KFlag2;
struct _KbdFlags3 KFlag3;
struct _KbdFlags4 KFlag4;


void dump_buff();
char  toggle(char x);
void de_kbd();
void wait_kbd();


char  toggle(char x)
{
	return((x)^(0xFF));//toggle all bits of byte
}

void de_kbd()
{
char temp;
int just_loop;
	temp = inportb(0x61);
	outportb(0x61,temp | 0x80);  // disable
	for(just_loop=0;just_loop<1000;just_loop++);
	outportb(0x61,temp & 0x7F);  // and re-enable
}


void wait_kbd()
{
	//while((inportb(0x64)&0x02));//wait before writing new command
	unsigned int i=3000;
	while(i!=0) i--;
}



void IS_OP_BUF_EMPTY()
{
	/*write to KEYB_PORT only if OBF=0 */
	unsigned char temp;
	temp=inportb(KEYB_CTRL);
	temp=temp&0x02;
	while(temp!=0)
	{
		temp=inportb(KEYB_CTRL);
		temp=temp&0x02;
	}
}

void WAIT_FOR_KEYB_ACK()
{
	/* Listne for keyboards acknowledgement at 0x60 input*/
//	while((inportb(KEYB_PORT))!=KEYB_ACK);
	unsigned char temp;
	temp=inportb(KEYB_PORT);
//	printf("<0x60=%x>\n",(unsigned int)temp);

	while(temp!=0xFA)
	{
		temp=inportb(KEYB_PORT);
//		printf("<0x60=%x>\n",(unsigned int)temp);
	}

}


void update_LED()
{
	unsigned char temp=0;

	if(KFlag1.CP_Lock_stat)		{temp=temp+4;	KFlag4.CP_Lock_LED=KFlag1.CP_Lock_stat;	}
	if(KFlag1.N_Lock_stat)		{temp+=0x02;	KFlag4.N_Lock_LED=KFlag1.N_Lock_stat;	}
	if(KFlag1.SC_Lock_stat)		{temp+=0x01;	KFlag4.SC_Lock_LED=KFlag1.SC_Lock_stat;	}

	wait_kbd();
	outportb(0x60,0xED);
	WAIT_FOR_KEYB_ACK();
	IS_OP_BUF_EMPTY();
	wait_kbd();
	outportb(0x60,temp);
	WAIT_FOR_KEYB_ACK();
	IS_OP_BUF_EMPTY();
	wait_kbd();

}


void put_in_kb_buf(unsigned short int ch)
{
if((ch&0xFF00)==0x1C00) putch('\n');

	if((ch & 0xFF00) == 0x0E00 && csr_x!=0 && !(new_prompt_count == 0 && csr_x < 6))//if bkspace
	{
		if(buf_tail!=0)
		{
			buf_tail=(buf_tail-1);
			//Kbuf[buf_tail]=0x0000;
		}
		else
		{
			//Kbuf[Kbuf_max]=0x0000;
			buf_tail=Kbuf_max;
		}
	return;
	}

	if(buf_head==(buf_tail+1))
	{
		//puts("KEYBOARD:buffer full\n");
		//beep();
		return;
	}

	else
	{
		Kbuf[buf_tail]=ch;

		//putch('[');
		//putch(Kbuf[buf_tail]);
		//putch(']');
		//printf("head=[%d]",buf_head);printf("tail=[%d]",buf_tail);
		buf_tail=(buf_tail+1)%Kbuf_max;
		return;
	}
}

unsigned char read_char_from_kb_buf()
{
	unsigned short int temp=buf_head;
	if(buf_head==buf_tail)
	{
		puts("KEYBOARD:buffer empty\n");
		//printf("head=[%d]",buf_head);printf("tail=[%d]",buf_tail);
		buf_head=buf_tail=0;
		return((unsigned char)0);
	}
	else
	{
		buf_head=(buf_head+1)%Kbuf_max;
		//puts("char_read=");putch((unsigned char)Kbuf[temp]);
		return((unsigned char)Kbuf[temp]);
	}
}

void get_line_kb_buf()
{
	int i,j=0;
	unsigned char ch=0;
	do
	{

		ch=read_char_from_kb_buf();
		//puts("fetched char frm buf\n");putch(ch);
		line_kb_buf[j++]=ch;
		//puts("char written to line_kb_buf\n");
	}while((ch!=0x00)&&(ch!=0x0D));

	//puts("puting delimeter\n");
line_kb_buf[j++]='\0';
//puts("done delimeter\n");
}

unsigned short int SCA_2_ASCII(unsigned char scancode)
{
	unsigned int row=scancode,col=0;
	unsigned short int ch=0;
	unsigned int i;
	unsigned char x=1;

	if(N_LOCK)
	{
		col+=4;
		if(SHIFT) col+=1;
	}
	else if(CP_LOCK)
	{
		col+=5;
		if(SHIFT) col+=1;
	}
	else if(SHIFT)
	{
		col+=1;
	}
	else if(CTRL)
	{
		col+=2;
	}
	else if(ALT)
	{
		col+=3;
	}

	ch=(row)*8 + col;
	ch=kbdus[ch];

return(ch);
}

void dump_kb_buf()
{
unsigned char x;
putch('\n');
		while(x!=0)
		{
			x=read_char_from_kb_buf();
			putch(x);
		}
		new_prompt();
		buf_tail=buf_head=0;
}

void SpecialKeyScanCode_E0_()
{
	unsigned char  scancode=0;
	unsigned int make=0;
	unsigned short int sca_ascii;
	scancode=inportb(0x60);
	if(scancode & 0x80)
	{
		make=0;
		switch(scancode-0x80)
		{

			case(Ctrl):		KFlag3.RCtrl_curr=0;
							if(KFlag2.LCtrl_curr) {CTRL=1;KFlag1.Ctrl_curr=1;}
							else {CTRL=0;KFlag1.Ctrl_curr=0;}
							break;

			case(Alt):		KFlag3.RAlt_curr=0;
							if(KFlag2.LAlt_curr) {ALT=1;KFlag1.Alt_curr=1;}
							else {ALT=0;KFlag1.Alt_curr=0;}
							break;

			case(Ins):		KFlag2.Ins_curr=0;break;

			case(Up):
			case(Down):
			case(Pg_Up):
			case(Pg_Dn):
			case(Home):
			case(End):
			case(Del):break;

			default:
			{
			}
		}
	}
	else
	{
		make=1;
		switch(scancode)
		{
			case(Ctrl):	KFlag3.RCtrl_curr=1;
						KFlag1.Ctrl_curr=1;
						CTRL=1;
						break;
			case(Alt):	KFlag3.RAlt_curr=1;
						KFlag1.Alt_curr=1;
						ALT=1;
						break;
			case(Ins):	KFlag1.Ins_stat=(KFlag1.Ins_stat)^(0x01);
						break;
			case(End):	goto_xy(csr_x,csr_y);
						break;//not much useful right now
			case(Home):	goto_xy(0,csr_y);
						break;
			case(Left):	{goto_xy(csr_x-1,csr_y);break;}
			case(Right):{goto_xy(csr_x+1,csr_y);break;}
			case(Up):	{break;}
			case(Down):	{break;}
			default:
			{

			}
		}
	}


	if(make)	sca_ascii=SCA_2_ASCII(scancode);
	if((((unsigned char)sca_ascii)>=32 && ((unsigned char)sca_ascii<=126)) || ((unsigned char)sca_ascii)==0x08||((unsigned char )sca_ascii)==0x0D||((unsigned char )sca_ascii)==0x0A)
	{
		put_in_kb_buf(sca_ascii);
		putch((unsigned char)(sca_ascii & 0x00ff));
	}

//if(scancode==0x1c) dump_kb_buf();
KFlag3.E0=0;
}

/* Handles the keyboard interrupt */
void keyboard_handler(struct regs *r)
{
    unsigned char scancode,temp;
    unsigned short int sca_ascii;
    unsigned int make=0;
    /* Read from the keyboard's data buffer */
    scancode = inportb(KEYB_PORT);
    /*The driver reads the scan code from port 0x60,
    *which causes the 8042 to de-assert IRQ 1 and
    *reset the IBF flag of the status register(port=0x64,Bit#1).*/
    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
//    printf("[%x]",(unsigned int)scancode);

    if (scancode & 0x80)
    {
		make=0;
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */

        switch(scancode-0x80)
        {
			case(R_Shift):	KFlag1.Rshift_curr=0;
							if(KFlag1.Lshift_curr) SHIFT=1;
							else SHIFT=0;
							break;
			case(L_Shift):	KFlag1.Lshift_curr=0;
							if(KFlag1.Rshift_curr) SHIFT=1;
							else SHIFT=0;
							break;
			case(Ctrl):		KFlag2.LCtrl_curr=0;//R_Ctrl has special scancode
							if(KFlag3.RCtrl_curr) {CTRL=1;KFlag1.Ctrl_curr=1;}
							else {CTRL=0;KFlag1.Ctrl_curr=0;}
							break;
			case(Alt):		KFlag2.LAlt_curr=0;//R_Alt has special scancode
							if(KFlag3.RAlt_curr)	{ALT=1;KFlag1.Alt_curr=0;}
							else {ALT=0;KFlag1.Alt_curr=0;}
							break;
			case(CP_Lock):	KFlag2.CP_Lock_curr=0;
							break;
			case(SC_Lock):	KFlag2.SC_Lock_curr=0;
							break;
			case(N_Lock):	KFlag2.N_Lock_curr=0;
							break;

			case(Bksp):		break;


			default:
			{
			}
		}
    }
    else
    {
		make=1;
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
        switch(scancode)
        {					//////
			case(0xaa):			//
			case(0xba):			//
			case(0x41):			//
			case(0xee):			//just ignore these scancodes
			case(0xfa):			//
			case(0xfe):break;	//
							//////
																			//////
			case(0xfc):puts("KEYBOARD:BAT(Basic Assurance Test) FAILED");break;	//
			case(0xff):puts("KEYBOARD:KEYBOARD ERROR");break;					//KBD IS SCREWED UP
																			//////
			case(0x00):			puts("too many keys pressed\n");
								break;
        	case(R_Shift):		KFlag1.Rshift_curr=1;
        						SHIFT=1;
        						break;
        	case(L_Shift):		KFlag1.Lshift_curr=1;
        						SHIFT=1;
        						break;
        	case(CP_Lock):		KFlag2.CP_Lock_curr=1;
        						KFlag1.CP_Lock_stat=(KFlag1.CP_Lock_stat)^(0x01);
        						if(KFlag1.CP_Lock_stat) CP_LOCK=0x01;
        						else CP_LOCK=0x00;
        						update_LED();
        						break;
        	case(SC_Lock):		KFlag2.SC_Lock_curr=1;
        						KFlag1.SC_Lock_stat=(KFlag1.SC_Lock_stat)^(0x01);
        						if(KFlag1.SC_Lock_stat) SC_LOCK=0x01;
        						else SC_LOCK=0x00;
        						update_LED();
        						break;
			case(N_Lock):		KFlag2.N_Lock_curr=1;
								KFlag1.N_Lock_stat=(KFlag1.N_Lock_stat)^(0x01);
								N_LOCK=KFlag1.N_Lock_stat;
								update_LED();
								break;
			case(Ctrl):			KFlag2.LCtrl_curr=1;
								KFlag1.Ctrl_curr=1;
								CTRL=1;
								break;
			case(Alt):			KFlag2.LAlt_curr=1;
								KFlag1.Alt_curr=1;
								ALT=1;
								break;
        	case(0xE0):			outportb(0x20,0x20);
    							de_kbd();
    							KFlag3.E0=1;
        						SpecialKeyScanCode_E0_();
        						break;
        	case(0xE1):			outportb(0x20,0x20);
    							de_kbd();
    							KFlag3.E1=1;
        						//SpecialKeyScanCode_E1_();
        						break;
			default:
			{
			}

		}
    }


	if(make)	sca_ascii=SCA_2_ASCII(scancode);
	if((((unsigned char)sca_ascii)>=32 && ((unsigned char)sca_ascii<=126)) || ((unsigned char)sca_ascii)==0x08||((unsigned char )sca_ascii)==0x0D||((unsigned char )sca_ascii)==0x0A)
	{
		put_in_kb_buf(sca_ascii);
		putch((unsigned char)(sca_ascii & 0x00ff));
	}

	if(scancode==0x1c && ((unsigned char )sca_ascii==0x0d ||((unsigned char )sca_ascii)==0x0A))
	{
		get_line_kb_buf();
		puts(line_kb_buf);
		putch('\n');
		commands(line_kb_buf);
		new_prompt();
	}
    outportb(0x20,0x20);
    de_kbd();
}


void chk_cmd_buf_empty()
{
	unsigned char temp=inportb(0x64);
	printf("<0x64=%x>",(unsigned int)temp);
	temp=temp & 0x02;
	while(temp!=0)//wait before writing new command
	{
		temp=inportb(0x64);
		printf("<0x64=%x>",(unsigned int)temp);
		temp=temp & 0x02;
	}
}

void kbd_BAT()
{
	unsigned char temp=0;
	wait_kbd();
	outportb(KEYB_CTRL,KEYB_DO_BAT);
}
/* Installs the keyboard handler into IRQ1 */
void keyboard_install()
{
unsigned char temp=0;

/*When you write to the 8042's output buffer (via port 0x60),
*the controller sets the OBF ("Output Buffer Full") flag and processes the data.
*The 8042 will send this data to the keyboard and wait for a response.
*If no errors occur, the response byte is placed in the input buffer,
*the IBF ("Input Buffer Full") flag is set, and IRQ 1 is activated,
*signaling the keyboard driver. */

/*Commands are sent to the keyboard controller by writing to port 0x64.
*Command parameters are written to port 0x60 after then command is sent.
*Results are returned on port 0x60.  Always test the OBF ("Output Buffer Full")(port#0x64,bit#0)
*flag before writing commands or parameters to the 8042.*/


	//check_kbd();
	KFlag4.Always_Zero=0;
	//wait_kbd();
	//chk_cmd_buf_empty();
	//outportb(0x60,0xfa);//auto repeat & generate both up & down scan codes
	update_LED();
	buf_tail=buf_head=0;
    irq_install_handler(1, keyboard_handler);
}


