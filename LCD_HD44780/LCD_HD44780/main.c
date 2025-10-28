/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <joerg@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Joerg Wunsch
 * ----------------------------------------------------------------------------
 *
 * Stdio demo
 *
 * $Id: stdiodemo.c 1008 2005-12-28 21:38:59Z joerg_wunsch $
 */

//#define F_CPU 16000000UL
#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "Resources\hd44780.h"

int main(void)
{
  lcd_init();
  lcd_putchar('H');
  lcd_putchar('E');
  lcd_putchar('L');
  lcd_putchar('L');
  lcd_putchar('O');
  _delay_ms(1000);

  return 0;
}

/*int main(void)
{
	// {X, RS, E, RW, D7, D6, D5, D4}
	DDRD  = 0b11111111; //Porta B como saída
	_delay_ms(500);
	PORTD = 0b00100010;	//Seta modo para 4-bit
	_delay_ms(20);
	PORTD = 0b00100010;	//1 line display 5x8
	_delay_ms(20);
	PORTD = 0b00100010;	//1 line display 5x8
	_delay_ms(20);
	PORTD = 0b00100000;	//Display on
	_delay_ms(20);
	PORTD = 0b00101110;	//Display on
	_delay_ms(20);
	PORTD = 0b00100000;	//Entry mode set
	_delay_ms(20);
	PORTD = 0b00100110;	//Entry mode set
	_delay_ms(20);
	PORTD = 0b01100100;	//Escrever H
	_delay_ms(20);
	PORTD = 0b01101000;	//Escrever H
	_delay_ms(20);
	
}*/