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

#ifndef TIMERS_H
#define TIMERS_H


/*FUNTZIOAK*/
//Timer0 hasieratu
void init_timer0();
//Timer0 gelditu
void stop_timer0();
//Timer1 hasieratu
void init_timer1();
//Timer1 gelditu
void stop_timer1();
//Timer2 hasieratu
void init_timer2();
//Timer2 gelditu
void stop_timer2();
void delay_ms(int time);

#endif //TIMERS_H
