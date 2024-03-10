#include "TM4C123.h"                    // Device header
#include "delay.h"
#include "sensors.h"

uint32_t measure_distance (void)
 {
	
	GPIOE->DATA &=(~(TRIGGER));                       /*disable trigger*/
	 delayUs(10);
	GPIOE->DATA |= TRIGGER    ;                       /*enable triggger*/
	 delayUs(10);
	GPIOE->DATA &=(~(TRIGGER));                       /*disable trigger*/
	while(1)
	{
    TIMER0->ICR = 4;            /* clear timer0A capture flag */
    while((TIMER0->RIS & 4) == 0) ;    /* wait till captured */
	  if(GPIOB->DATA & (1<<6)) /*check if rising edge occurs */
		{
    highEdge = TIMER0->TAR;     /* save the timestamp */
		/* detect falling edge */
    TIMER0->ICR = 4;            /* clear timer0A capture flag */
    while((TIMER0->RIS & 4) == 0) ;    /* wait till captured */
    lowEdge = TIMER0->TAR;     /* save the timestamp */
		return (lowEdge - highEdge ); /* return the time difference */
		}
	}
}

void timer0_init(void)
{ /*using timer 0 in edge time mode */
	/* Timer0A is used to measure distance by measuring pulse duration of Echo output signal */
    SYSCTL->RCGCTIMER |= 1;     /* enable clock to Timer Block 0 */
    SYSCTL->RCGCGPIO |= 2;      /* enable clock to PORTB */
    SYSCTL->RCGCGPIO |= 0x10;   /*clock for PE*/
	
    GPIOB->DIR &= ~0x40;        /* make PB6 an input pin */
    GPIOB->DEN |= 0x40;         /* make PB6 as digital pin */
    GPIOB->AFSEL |= 0x40;       /* use PB6 alternate function */
    GPIOB->PCTL &= ~0x0F000000;  /* configure PB6 for T0CCP0 */
    GPIOB->PCTL |= 0x07000000;
	
	  GPIOE->DIR |= 0x06;                       	/* TRIGG & LED_u OUTPUT select*/
	  GPIOE->DEN |= 0x06;                         /* TRIG & LED_U digital enable */
	
	 TIMER0->CTL &= ~1;          /* disable timer0A during setup */
    TIMER0->CFG = 4;            /* 16-bit timer mode */
    TIMER0->TAMR = 0x17;        /* up-count, edge-time, capture mode */
    TIMER0->CTL |=0x0C;        /* capture the rising edge */
    TIMER0->CTL |= (1<<0);           /* enable timer0A */
	
	}

	//pir
	void pir_init(void)
{

    SYSCTL->RCGCGPIO |= 0x01; // Enable clock for GPIOA

    GPIOA->DIR &= ~(0x04); // PIR data input
    GPIOA->DIR |= 0x08;    // LED
    GPIOA->DEN |= 0x0C;

    // PIR interrupt configuration
    GPIOA->IS &= ~(0x04); // Level sensitive
    GPIOA->IBE &= ~(0x04); // Single edge interrupt
    GPIOA->IEV |= 0x04;    // Rising edge interrupt select
    GPIOA->IM |= 0x04;     // Unmasking interrupt, i.e., it is sent to controller
    GPIOA->ICR = 0x04;     // Clearing interrupts

    NVIC->ISER[0] = (1 << 0); // Enable GPIOA interrupt in NVIC
    __enable_irq(); // Enable interrupts
}

