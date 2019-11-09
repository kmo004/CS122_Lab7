/*
 * lab7_part1_LCD.c
 *
 * Created: 11/6/2019 3:11:21 PM
 * Author : Jason Mendoza
 */ 

#include <avr/io.h>
#include "timer.h"
#include "lcd.h"
#include "SPI_ATmega1284.h"

int val;
unsigned char string[5];


int main(void)
{
    DDRD = 0xFF; PORTD = 0x00; 
	DDRC = 0xFF; PORTC = 0x00;
	
	LCD_init();
	SPI_SlaveInit();
	
	TimerSet(500);
	TimerOn();
	
    while (1) 
    {
		  val = (int)receivedData;
		 itoa(val,string,10);
		 LCD_DisplayString(1,string);
		 while(!TimerFlag){}
		 TimerFlag = 0;
    }
}

