/*
 * GPIO.c
 *
 * Created: 09/06/2025 23:40:00
 * Author : rafae
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC   =  0b11111111; //Habilita Porta C como saída
	//DDRD  &=  ~(1<<0);    //Habilita PD0 como entrada
	//PORTD |=  (1<<0);     //Habilita o resistor de pull-up de PD0
	DDRD = 0b00000000;
	
	/*uint8_t num = 0;
	uint8_t LUT[10] = {0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B};
	
	while (1)
	{
		if((PIND & (1<<0)) == 0)
		{
			num++;
			//while((PIND & (1<<0)) == 0);
		}
		if(num == 10)
			num = 0;
		_delay_ms(100);
		PORTC = LUT[num];
	}*/
	
	while(1)
		PORTC = PIND;
}


