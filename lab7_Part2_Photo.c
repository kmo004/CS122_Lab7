/*
 * CS122A_Lab7_Part1.c
 *
 * Created: 11/1/2019 1:56:21 PM
 * Author : Jason Mendoza
 */ 

#include <avr/io.h>
#include "timer.h"


void SPI_ServantInit(void){
	DDRB = 0x40; PORTB = 0xBF;
	SPCR |= (1 << SPE) | (1 << SPIE);
	SREG = 0x80;
}

unsigned char recievedData;
ISR(SPI_STC_vect){
	recievedData = SPDR;
}

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	
    ADC_init();
	SPI_ServantInit();
	
	TimerSet(500);
	TimerOn();
	
	unsigned short x_ADC;
	unsigned char x_char;
	
    while (1) 
    {
		
		x_ADC = ADC;
		x_char = (char)x_ADC;
		if(recievedData == 0x10){
			SPDR = x_char;
		}
		else{
			SPDR = 0xFF;
		}
		while(!TimerFlag){}
		TimerFlag = 0;
    }
}


