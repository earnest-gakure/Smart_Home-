#include "TM4C123.h"                    // Device header
void delayMs(int n)
{  
	volatile int i,j;             //volatile is important for variables incremented in code
	for(i=0;i<n;i++)
		for(j=0;j<3180;j++)         //delay for 1 msec
		{}
}
void delayUs(int time)             
{
	int i;
	   //WE USE TIMER1
	  SYSCTL->RCGCTIMER |= ( 1U<<1 );
    TIMER1->CTL = 0 ;         //disable timer
	  TIMER1->CFG  = 0x04 ;     //16-bits mode
	  TIMER1->TAMR = 0x02 ;     //periodic time mode
    TIMER1->TAILR = 16000-1 ;    //COZ we are using microseconds
	  TIMER1->ICR = 0x1;        //interrupt clear register
	  TIMER1->CTL |= 0x01 ;     //ENABLE TIMER
	
	for (i = 0 ; i < time ; i++ ){ 
		
		while ((TIMER1->RIS & 0x1) == 0) ;      //POLLING
		TIMER1->ICR = 0x1;
	}

}