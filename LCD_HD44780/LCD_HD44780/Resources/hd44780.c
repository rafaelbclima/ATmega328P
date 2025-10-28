/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <joerg@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Joerg Wunsch
 * ----------------------------------------------------------------------------
 *
 * HD44780 LCD display driver
 *
 * The LCD controller is used in 4-bit mode
 *
 * $Id: hd44780.c 2002 2009-06-25 20:21:16Z joerg_wunsch $
 */

#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "hd44780.h"

/*
 * Send one nibble out to the LCD controller.
 */
static void
hd44780_outnibble(uint8_t n, uint8_t rs)
{
  CLR(PORT, HD44780_RW);
  if (rs)
    SET(PORT, HD44780_RS);
  else
    CLR(PORT, HD44780_RS);
  ASSIGN(PORT, HD44780_D4, n);
  SET(PORT, HD44780_E);
  _delay_us(0.5);
  CLR(PORT, HD44780_E);
}

/*
 * Send one byte to the LCD controller.  As we are in 4-bit mode, we
 * have to send two nibbles.
 */
void
hd44780_outbyte(uint8_t b, uint8_t rs)
{
  hd44780_outnibble(b >> 4, rs);
  hd44780_outnibble(b & 0xf, rs);
}


/*
 * Initialize the LCD controller.
 *
 * The initialization sequence has a mandatory timing so the
 * controller can safely recognize the type of interface desired.
 * This is the only area where timed waits are really needed as
 * the busy flag cannot be probed initially.
 */
void
hd44780_init(void)
{
  SET(DDR, HD44780_RS);
  SET(DDR, HD44780_RW);
  SET(DDR, HD44780_E);
  ASSIGN(DDR, HD44780_D4, 0x0F);

  _delay_ms(15);		/* 40 ms needed for Vcc = 2.7 V */
  hd44780_outnibble(HD44780_FNSET(1, 0, 0) >> 4, 0);
  _delay_ms(4.1);
  hd44780_outnibble(HD44780_FNSET(1, 0, 0) >> 4, 0);
  _delay_ms(0.1);
  hd44780_outnibble(HD44780_FNSET(1, 0, 0) >> 4, 0);
  _delay_us(37);
  hd44780_outnibble(HD44780_FNSET(0, 1, 0) >> 4, 0);
  _delay_us(37);
  hd44780_outcmd(HD44780_FNSET(0, 1, 0));
  _delay_us(37);
  hd44780_outcmd(HD44780_DISPCTL(0, 0, 0));
  _delay_us(37);
}

/*
 * Setup the LCD controller.  First, call the hardware initialization
 * function, then adjust the display attributes we want.
 */
void
lcd_init(void)
{
  hd44780_init();
  hd44780_outcmd(HD44780_CLR);//Clear the display.
  _delay_us(37);
  hd44780_outcmd(HD44780_ENTMODE(1, 0));//Entry mode: auto-increment address counter, no display shift in effect.
  _delay_us(37);
  hd44780_outcmd(HD44780_DISPCTL(1, 1, 0));//Enable display, activate non-blinking cursor.
  _delay_us(37);
}

/*
 * Send character c to the LCD display.  After a '\n' has been seen,
 * the next character will first clear the display.
 */
int
lcd_putchar(char c)
{
	 _delay_us(37);
	 hd44780_outdata(c);
	 return 0;
}
