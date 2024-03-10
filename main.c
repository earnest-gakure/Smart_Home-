#include "TM4C123.h"                    // Device header
#include "LCD.h"
#include "delay.h"
#include "sensors.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//pit interrupt handler
void GPIOA_Handler(void)
{
    state = 1;
    GPIOA->ICR = 0x04; // Clear interrupt flag
}
int main ()
{ 
	//interrupt disable
	__disable_irq(); // disable interrupts
	
	
	
	char* str1 = "SMART HOME";    //Write any string you want to display on LCD
	char* str2 = "BY : EARNEST";
	LCD4bits_Init();									//Initialization of LCD
	LCD4bits_Cmd(0x01);								//Clear the display
	LCD4bits_Cmd(0x80);               //Force the cursor to beginning of 1st line
	delayMs(500);											//delay 500 ms for LCD (MCU is faster than LCD)
	LCD_WriteString(str1);							//Write the string on LCD
	LCD4bits_Cmd(0xC0);
	LCD_WriteString(str2);							//Write the string on LCD
	delayMs(3000);	
	
	
	timer0_init(); 
	 pir_init();
	while(1)
	{

		time = measure_distance();
		distance_in_cm = _16MHZ_1clock * (double) MULTIPLIER * (double) time ;
			
			if(distance_in_cm < 15 )
			{
				
				LCD4bits_Cmd(0x01);
				LCD4bits_Cmd(0x80);
				LCD_WriteString("  DOOR OPENNED ");
				LCD4bits_Cmd(0xC0);
				LCD_WriteString("    WELCOME ");
				LCD4bits_Cmd(0x0C);//cursor off
			
				GPIOE->DATA |= LED_U;
         delayMs(1000);
        GPIOE->DATA &=(~(LED_U));
				LCD4bits_Cmd(0x01);
				LCD4bits_Cmd(0x80);
				LCD_WriteString("  DOOR CLOSED ");
				LCD4bits_Cmd(0x0C);//cursor off
				
			}else if(distance_in_cm > 15){
				
				GPIOE->DATA &=(~(LED_U));
				 
				LCD4bits_Cmd(0x01);
				LCD4bits_Cmd(0x80);
				LCD_WriteString("  DOOR CLOSED ");
				LCD4bits_Cmd(0x0C);//cursor off
				delayMs(2000);
				
			}
		if (state == 1)
        {
					LCD4bits_Cmd(0x01);
				LCD4bits_Cmd(0x80);
				LCD_WriteString("  LIGHTS ON ");
				LCD4bits_Cmd(0x0C);//cursor off
				delayMs(2000);
				
            GPIOA->DATA |= 0x08; // Use |= instead of = for setting the LED
            delayMs(3000);
            state = 0;
        }
        else
        {
            GPIOA->DATA &= ~(0x08);
        }
		
	}
	
	
	
}
