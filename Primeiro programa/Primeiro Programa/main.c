/*
 * Primeiro Programa.c
 *
 * Created: 09/06/2025 21:58:02
 * Author : rafae
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	DDRB = 0b00100000; //Habilita o pino PB5 como saída
    while (1) 
    {
		PORTB = 0b00100000; //Pino PB5 em nível alto
		_delay_ms(500);
		PORTB = 0b00000000; //Pino PB5 em nível baixo
		_delay_ms(500);
    }
}

