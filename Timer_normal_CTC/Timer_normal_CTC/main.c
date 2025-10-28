#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER0_OVF_vect) //interrupção do TC0
{
	PORTB ^= 0b00100000; //Inverte o estado do PB5
}
int main()
{
	DDRB   |= 0b00100000;//habilita PB5 como saída e demais pinos como entrada
	PORTB  &= 0b11011111;//apaga PB5
	TCCR0A = 0b00000000;//TC0 em operação normal
	TCCR0B = 0b00000001;//TC0 sem prescaler. Overflow a cada 16us = 256/16MHz
	TIMSK0 = 0b00000001;//habilita a interrupção por estouro do TC0
	sei(); //habilita a chave de interrupção global
	while(1)
	{
		//a cada estouro do TC0 o programa desvia para ISR(TIMER0_OVF_vect)
	}
}

/*#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER0_COMPA_vect) //interrupção do TC0 a cada 1ms = (64*(249+1))/16MHz
{
	PORTB ^= 0b00100000; //Inverte o estado do PB5
}
int main(void)
{
	DDRB   |= 0b00100000;//habilita PB5 como saída 
	PORTB  &= 0b11011111;//apaga PB5 

	TCCR0A = 0b00000010; //habilita modo CTC do TC0
	TCCR0B = 0b00000011; //liga TC0 com prescaler = 64
	OCR0A = 249; //ajusta o comparador para o TC0 contar até 249
	TIMSK0 = 0b00000010; //habilita a interrupção na igualdade de comparação com OCR0A. A interrupção ocorre a cada 1ms = (64*(249+1))/16MHz
	sei();
	while(1)
	{
	}
}*/
