/*====================================================================
 *
 *  Filename: timers.h
 *
 *  Description: timers.c-rako beharrezkoak diren aldagai eta funtzioen
 *		 definizioak.
 *
 *  Version: 1.0
 *  Created: 2022-03-19
 *  Author: Unai Fernandez
 *
 ====================================================================*/

extern volatile int dht_timeout;
extern int en;

void init_timer0();
int set_prescaler(int prescaler);
void delay_us(int us);
void delay_ms(int ms);
