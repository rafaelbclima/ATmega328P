/*
 * Interrupcao_externa.c
 *
 * Created: 16/06/2025 20:47:31
 * Author : rafae
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT0_vect) //interrupção externa INT0, quando o botão é pressionado o LED troca de estado
{
	PORTC ^= 0b00000100; //Inverte o estado do pino PC2
}

int main(void)
{
	//GPIO
	DDRD =0x00; //Todos os pinos da porta D como entradas
	PORTD = 0xFF; //Todos os pull-ups da porta D habilitados
	DDRC =0b00000100; //somente pino do LED como saída PC2

	//Configuração das interrupções
	EICRA = 0b00000010;//interrupção externa INT0 na borda de descida
	EIMSK = 0b00000001;//habilita a interrupção externa INT0
	sei();//habilita interrupções globais, ativando o bit I do SREG

	uint8_t cont = 0;
	while (1)
	{  
		cont++;
	}
}

