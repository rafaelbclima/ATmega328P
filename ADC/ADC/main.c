#define F_CPU 16000000UL //Frequ�ncia de trabalho da CPU
#define BAUD 9600			//Taxa da UART
#define MYUBRR F_CPU/16/BAUD-1
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint16_t leitura_ADC = 0;

ISR(ADC_vect)
{
	leitura_ADC = ADC;
}

//Fun��o para envio de um frame de 5 a 8bits
void UART_Transmit(uint8_t data)
{
	while(!( UCSR0A & (1<<UDRE0)));//Espera a limpeza do registr. de transmiss�o
	UDR0 = data; //Coloca o dado no registrador e o envia
}

int main()
{
	//GPIO
	DDRC = 0x00; //Porta C como entrada
	PORTC = 0xFE; //Desabilita o pullup do PC0
	//Configura ADC
	ADMUX = 0b11000000; //Tens�o interna de ref (1.1V), canal 0
	ADCSRA = 0b11101111; //habilita o AD, habilita interrup��o, modo de convers�o cont�nua, prescaler = 128
	ADCSRB = 0x00; //modo de convers�o cont�nua
	DIDR0 = 0b00111110; //habilita pino PC0 como entrada do ADC0
	//Configura a UART
	UBRR0H = (uint8_t)(MYUBRR>>8); //Ajusta a taxa de transmiss�o
	UBRR0L = (uint8_t)MYUBRR;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //Habilita o transmissor e o receptor
	UCSR0C = (1<<USBS0)|(3<<UCSZ00); //Ajusta o formato do frame: 8 bits de dados e 2 de parada

	sei(); //Habilita interrup��es globais

	while(1)
	{
		UART_Transmit((uint8_t)(leitura_ADC>>8));//Envia 8bits mais significativos da leitura do ADC
		UART_Transmit((uint8_t)leitura_ADC);//Envia 8bits menos significativos da leitura do ADC
		_delay_ms(1000);
	}
}