#ifndef __KB_H
#define __KB_H


#define KEYB_PORT               0x60    /* keyboard port */
#define KEYB_CTRL               0x64    /* keyboard controller port */

#define KCTRL_READ_CMD_BYTE		0x20	/* Read command byte from KEYB_CTRL */
#define KCTRL_ENABLE_AUX		0xA8	/* enable aux port (PS/2 mouse) */
#define KCTRL_WRITE_CMD_BYTE    0x60    /* write to command register */
#define KCTRL_WRITE_AUX			0xD4	/* write next byte at port 60 to aux port */

/* flags for KCTRL_WRITE_CMD_BYTE */
#define KCTRL_IRQ1              0x01
#define KCTRL_IRQ12             0x02
#define KCTRL_SYS               0x04
#define KCTRL_OVERRIDE_INHIBIT  0x08
#define KCTRL_DISABLE_KEYB      0x10
#define KCTRL_DISABLE_AUX       0x20
#define KCTRL_TRANSLATE_XT      0x40
#define KCTRL_SELF_TEST			0xAA	/* 0xAA (Controller self-test) - Returns 0x55 if okay */
#define KCTRL_SELF_TEST_PASS	0x55	/* controller returns this on self test pass */

/*
*Port 60h: Input & output*/

/* commands to keyboard */
#define KEYB_SET_LEDS			0xED
#define KEYB_ECHO_EE			0xEE
#define KEYB_SET_SCANCODE_SET   0xF0
#define KEYB_IDENTIFY           0xF2
#define KEYB_SET_TYPEMATIC_RATE 0xF3
#define KEYB_ENABLE             0xF4
#define KEYB_RESET_DISABLE      0xF5
#define KEYB_SET_DEFAULT_VAL	0xF6
#define KEYB_ALL_TYPM_MAKE_BRK  0xFA
#define KEYB_DO_BAT				0xFF
//#define KEYB_ACK				0xFA

/*Read: Scancodes and keyboarddata*/
#define KEYB_RESEND				0xFE


#define KEYB_BAT_PASS			0xAA
#define KEYB_BAT_FAIL			0xFC
#define KEYB_ACK                0xFA	/* default ACK from keyboard following command */

///////////////////////////////////////////////////////////////////////
struct _KbdFlags1{
	/*
	KbdFlags1:
	This byte maintains the current status of the modifier
	keys on the keyboard. The bits have the following
	meanings:
	bit 7: Insert mode toggle
	bit 6: Capslock toggle (1=capslock on)
	bit 5: Numlock toggle (1=numlock on)
	bit 4: Scroll lock toggle (1=scroll lock on)
	bit 3: Alt key (1=alt is down)
	bit 2: Ctrl key (1=ctrl is down)
	bit 1: Left shift key (1=left shift is down)
	bit 0: Right shift key (1=right shift is down)
	*/
	unsigned char Rshift_curr	:1;
	unsigned char Lshift_curr	:1;
	unsigned char Ctrl_curr		:1;
	unsigned char Alt_curr		:1;
	unsigned char SC_Lock_stat	:1;
	unsigned char N_Lock_stat	:1;
	unsigned char CP_Lock_stat	:1;
	unsigned char Ins_stat	:1;
};

struct _KbdFlags2{
	/*
	KbdFlags2:
	(Toggle keys down)
	40:18 Byte Specifies if a toggle key is currently down.
	bit 7: Insert key (currently down if 1)
	bit 6: Capslock key (currently down if 1)
	bit 5: Numlock key (currently down if 1)
	bit 4: Scroll lock key (currently down if 1)
	bit 3: Pause state locked (ctrl-Numlock) if one
	bit 2: SysReq key (currently down if 1)
	bit 1: Left alt key (currently down if 1)
	bit 0: Left ctrl key (currently down if 1)
	*/
	unsigned char LCtrl_curr	:1;
	unsigned char LAlt_curr		:1;
	unsigned char PrtScr_curr	:1;
	unsigned char Pause_curr	:1;
	unsigned char SC_Lock_curr	:1;
	unsigned char N_Lock_curr	:1;
	unsigned char CP_Lock_curr	:1;
	unsigned char Ins_curr		:1;
};

struct _KbdFlags3{
	/*
	KbdFlags3:
	Miscellaneous keyboard flags.
	bit 7: Read of keyboard ID in progress
	bit 6: Last char is first kbd ID character
	bit 5: Force numlock on reset
	bit 4: 1 if 101-key kbd, 0 if 83/84 key kbd.
	bit 3: Right alt key pressed if 1
	bit 2: Right ctrl key pressed if 1
	bit 1: Last scan code was E0h
	bit 0: Last scan code was E1h
	*/
	unsigned char E1				:1;
	unsigned char E0				:1;
	unsigned char RCtrl_curr		:1;
	unsigned char RAlt_curr			:1;
	unsigned char AT_XT				:1;
	unsigned char NLock_on_reset	:1;
	unsigned char First_KB_id		:1;
	unsigned char reading_KB_id		:1;
};

struct _KbdFlags4{
	/*
	KbdFlags4:
	More miscellaneous keyboard flags.
	bit 7: Keyboard transmit error
	bit 6: Mode indicator update
	bit 5: Resend receive flag
	bit 4: Acknowledge received
	bit 3: Must always be zero
	bit 2: Capslock LED (1=on)
	bit 1: Numlock LED (1=on)
	bit 0: Scroll lock LED (1=on)
	*/
	unsigned char SC_Lock_LED	:1;
	unsigned char N_Lock_LED		:1;
	unsigned char CP_Lock_LED	:1;
	unsigned char Always_Zero	:1;
	unsigned char Got_Ack		:1;
	unsigned char Resend		:1;
	unsigned char Mode			:1;
	unsigned char Error			:1;
};
//////////////////////////////////////////////////////////////////////////

#endif


