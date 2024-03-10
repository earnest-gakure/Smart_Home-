#ifndef SENSORS_H_
#define SENSORS_H_
#include <stdint.h>
#define ECHO     (1<<0)  //PB6
#define TRIGGER  (1<<1)  //PE1
#define LED_U    (1<<2)  //PE2


static const double _16MHZ_1clock = 62.5e-9;   /*value of 1clock cycle in nanoseconds*/
static const uint32_t MULTIPLIER = 5882;       /*Constant derived from the speed of sound*/


static uint32_t highEdge;           /** Variable to hold time-stamp of high-edge detection*/
static uint32_t lowEdge;            /** Variable to hold time-stamp of low-edge detection */
static uint32_t distance_in_cm ;
static uint32_t time;


void timer0_init(void);
uint32_t measure_distance (void);


//pir
/*
PIR->PA2
LED ->PA3

*/
static int state = 0;
void pir_init(void);


#endif