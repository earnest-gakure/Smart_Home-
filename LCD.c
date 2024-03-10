#include "TM4C123.h"                    // Device header
#include "LCD.h"
#include "delay.h"
void LCD4bits_Init(void)
{
	SYSCTL->RCGCGPIO |= 0x02;    //enable clock for PORTB
	SYSCTL->RCGCGPIO |= 0x01;
	delayMs(10);                 //delay 10 ms for enable the clock of PORTB
  LCD->DIR = 0x0F;             //let PORTB as output pins
	LCD->DEN = 0x0F;             //enable PORTB digital IO pins
	GPIOA->DIR |=0xF0;
	GPIOA->DEN |=0xF0;
	LCD4bits_Cmd(0x28);          //2 lines and 5x7 character (4-bit data, D4 to D7)
	LCD4bits_Cmd(0x06);          //Automatic Increment cursor (shift cursor to right)
	LCD4bits_Cmd(0x01);					 //Clear display screen
	LCD4bits_Cmd(0x0F);          //Display on, cursor blinking
}


void LCD_Write4bits(unsigned char data, unsigned char control)
{

	GPIOA->DATA |= control;         
	LCD->DATA = data ;    
	GPIOA->DATA |= EN;
	delayUs(0);													//delay for pulsing EN
	GPIOA->DATA = 0;                      //Clear the Data 
}

void LCD_WriteString(char * str)
{  
	volatile int i = 0;          //volatile is important 
	
	while(*(str+i) != '\0')       //until the end of the string
	{
		LCD4bits_Data(*(str+i));    //Write each character of string
		i++;                        //increment for next character
	}
}

void LCD4bits_Cmd(unsigned char command)
{
	LCD_Write4bits(command >> 4 , 0);			 //then upper nibble
	LCD_Write4bits(command & 0x0F , 0);    //lower nible 
	
	
	if(command < 4)
		delayMs(2);       //commands 1 and 2 need up to 1.64ms
	else
		delayUs(40);      //all others 40 us
}

void LCD4bits_Data(unsigned char data)
{
	LCD_Write4bits(data >> 4 , RS);     //then upper nibble
	LCD_Write4bits(data & 0x0F , RS);   //lower nibble first
	
	delayUs(40);	
											//delay for LCD (MCU is faster than LCD)
}
