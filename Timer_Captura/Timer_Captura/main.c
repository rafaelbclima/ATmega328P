#define F_CPU 16000000UL
#define BAUD 9600//Taxa da UART
#define MYUBRR F_CPU/16/BAUD-1
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//Variáveis globais
uint32_t tempo_borda_subida, tempo_delta;

ISR(TIMER1_CAPT_vect) //interrupção por captura do valor do TC1
{
	if(TCCR1B & (1<<ICES1))//lê o valor de contagem do TC1 na borda de subida do sinal
		tempo_borda_subida = ICR1;//salva a primeira contagem para determinar a largura do pulso
	else//lê o valor de contagem do TC1 na borda de descida do sinal
		tempo_delta = (ICR1 - tempo_borda_subida)*16; //cada incremento do TC1 corresponde a 16us
	TCCR1B ^= (1<<ICES1); //inverte a borda de captura
}

//Função para envio de um frame de 5 a 8bits
void UART_Transmit(uint8_t data)
{
	while(!( UCSR0A & (1<<UDRE0)));//Espera a limpeza do registr. de transmissão
	UDR0 = data; //Coloca o dado no registrador e o envia
}

int main(void)
{
	//Configura GPIO
	DDRB  &= 0b11111110;// Entrada no pino PB0 (Captura no PB0 (ICP1))
	PORTB |= 0b00000001;// Pullups PB0 ativo
	//Configura a UART
	UBRR0H = (uint8_t)(MYUBRR>>8); //Ajusta a taxa de transmissão
	UBRR0L = (uint8_t)MYUBRR;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //Habilita o transmissor e o receptor
	UCSR0C = (1<<USBS0)|(3<<UCSZ00); //Ajusta o formato do frame: 8 bits de dados e 2 de parada
	//Configura Timer
	TCCR1B = (1<<ICES1)|(1<<CS12);//Captura na borda de subida, TC1 com prescaler = 256. Estouro a cada 256*(2^16)/16MHz = (2^16)*16us = 1,04s
	TIMSK1 = 1<<ICIE1;//habilita a interrupção por captura
	sei(); //Habilita o flag de interrupções globais

	while (1)
	{	
		UART_Transmit((uint8_t)(tempo_delta>>24));	
		UART_Transmit((uint8_t)(tempo_delta>>16));	
		UART_Transmit((uint8_t)(tempo_delta>>8));	 
		UART_Transmit((uint8_t)tempo_delta);		
		_delay_ms(1000);

	}
}
