/* bkerndev - Bran's Kernel Development Tutorial
*  By:   Brandon F. (friesenb@gmail.com)
*  Desc: Timer driver
*
*  Notes: No warranty expressed or implied. Use at own risk. */
#include <system.h>

/* This will keep track of how many ticks that the system
*  has been running for */
int timer_ticks = 0;
struct time clock;
/* Handles the timer. In this case, it's very simple: We
*  increment the 'timer_ticks' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */
void timer_handler(struct regs *r)
{
    /* Increment our 'tick count' */
    timer_ticks++;
    /* Every 18 clocks (approximately 1 second), we will
    *  display a message on the screen */
    if (timer_ticks % 18 == 0)
    {
		clock.sec++;
		if(clock.sec%60==0){clock.sec=0;clock.min++;}
		if(clock.min%60==0){clock.min=0;clock.hr++;}
		if(clock.hr%24==0){clock.hr=0;}

		//show_time(clock);
	}
}

/* This will continuously loop until the given time has
*  been reached */
void delay_seconds(unsigned int secs)
{
    unsigned long new_secs;

	new_secs=timer_ticks+(secs);
    //eticks = timer_ticks + secs;
    puts("\nwait [on]");
    while(timer_ticks<new_secs);
	puts("\nwait [off]");

}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void timer_install()
{
	clock.sec=clock.min=clock.hr=0;
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, timer_handler);


}
