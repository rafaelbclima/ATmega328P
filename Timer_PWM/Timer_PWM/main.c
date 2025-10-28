#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	//GPIO
	DDRD =0xFF; //Todos os pinos da porta D como saídas

	//Fast PWM, TOP = 0xFF, OC0A e OC0B habilitados
	TCCR0A = 0b10100011; //PWM não invertido nos pinos OC0A e OC0B
	TCCR0B = 0b00000011; //liga TC0, prescaler = 64, fpwm = f0sc/(256*prescaler) = 16MHz/(256*64) = 976Hz
	OCR0A = 192; //controle do ciclo ativo do PWM 0C0A (PD6) =>>> Duty = 192/256 = 75%
	OCR0B = 64; //controle do ciclo ativo do PWM OC0B (PD5)  =>>> Duty =  64/256 = 25%
	
	while (1)
	{
		//OCR0B += 10;
		//_delay_ms(3000);
	}
}
