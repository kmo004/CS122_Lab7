
#ifndef SPI_ATMEGA1284_H
#define SPI_ATMEGA1284_H

void SPI_MasterInit(void) {
	DDRB = 0xBF; PORTB = 0x40;
	
	SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR0);
	
	SREG = 0x80;
}

void SPI_MasterTransmit(char cData){
	
	PORTB = SetBit(PORTB,4,0);
	
	SPDR = cData;
	
	while(!(SPSR & (1<<SPIF)));
	
	PORTB = SetBit(PORTB,4,1);
}


void SPI_SlaveInit(void){
	
	/* Enable SPI */
	SPCR |= (1<<SPE) | (1 << SPIE);
	SREG = 0x80;
}

unsigned char receivedData = 0x00;
unsigned char curflag = 0x00;
unsigned char avgflag = 0x00;
int val;
char string[5];
ISR(SPI_STC_vect){
	receivedData = SPDR;
	val = (int)receivedData;
	
	if(curflag){
		itoa(val,string,10);
		LCD_DisplayString(5,string);
		curflag = 0x00;
	}
	if(avgflag){
		itoa(val,string,10);
		LCD_DisplayString(21,string);
		avgflag = 0x00;
	}
	
	if(val == 32){
		avgflag = 0x01;
	}
	else if (val == 64){
		curflag = 0x01;
	}
}
#endif SPI_ATMEGA1284_H


