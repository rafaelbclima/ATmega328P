#define F_CPU 16000000UL	//Frequência de trabalho da CPU
#define BAUD 9600			//Taxa da UART
#define MYUBRR F_CPU/16/BAUD-1
#include <avr/io.h>
#include <util/delay.h>

// ||Função para inicialização da USART||
void UART_Init(uint16_t ubrr)
{
	UBRR0H = (uint8_t)(ubrr>>8); //Ajusta a taxa de transmissão
	UBRR0L = (uint8_t)ubrr;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //Habilita o transmissor e o receptor
	UCSR0C = (1<<USBS0)|(3<<UCSZ00); //Ajusta o formato do frame: 8 bits de dados e 2 de parada
}

// ||Função para envio de um frame de 5 a 8bits||
void UART_Transmit(uint8_t data)
{
	while(!( UCSR0A & (1<<UDRE0)));//Espera a limpeza do registr. de transmissão
	UDR0 = data; //Coloca o dado no registrador e o envia
}

// ||Função para recepção de um frame de 5 a 8bits||
uint8_t UART_Receive(void)
{
	while(!(UCSR0A & (1<<RXC0))); //Espera o dado ser recebido
	return UDR0; //Lê o dado recebido e retorna
}

int main(void)
{
	UART_Init(MYUBRR);
	while(1)
	{
		UART_Transmit('u');
		_delay_ms(200);
		UART_Transmit('a');
		_delay_ms(200);
		UART_Transmit('r');
		_delay_ms(200);
		UART_Transmit('t');
		_delay_ms(200);
		UART_Transmit('\n');
		_delay_ms(200);
		/*UART_Transmit(UART_Receive());
		_delay_ms(200);*/
	}
	return 0;
}
