#ifndef LCD_H_
#define LCD_H_


#define LCD GPIOB    		//LCD port with Tiva C 
#define RS 0x10  /*PA4*/
#define RW 0x20  /*PA5*/
#define EN 0x40  /*PA6*/

/*lcd pins -> PB0-PB4 */


void delayUs(int);   														   //Delay in Micro Seconds
void delayMs(int);   														   //Delay in Milli Seconds
void LCD4bits_Init(void);													 //Initialization of LCD Dispaly
void LCD_Write4bits(unsigned char, unsigned char); //Write data as (4 bits) on LCD
void LCD_WriteString(char*);											 //Write a string on LCD 
void LCD4bits_Cmd(unsigned char);									 //Write command 
void LCD4bits_Data(unsigned char);								 //Write a character


#endif