/*====================================================================
 *
 *  Filename: timers.c
 *
 *  Description: Fitxategi honen bidez Atmega328p mikroaren timerrak 
 *               konfiguratuko dira.
 *
 *  Version: 1.0
 *  Created: 2022-03-18
 *  Author: Unai Fernandez
 *
 ====================================================================*/


#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>


#include "timers.h"


volatile int dht_timeout = 0;
int en = 0;

/*
 * Funtzio hau timer0 timerra konfiguratzeko balio du. Timerra CTC moduan 
 * konfiguratuko da, eta 10us-ro eten bat egingo du.
 */
void init_timer0(){
    //CTC moduan konfiguratu
    TCCR0A &=~ (1 << WGM00);
    TCCR0A |= (1 << WGM01);
    TCCR0B &=~ (1 << WGM02);


    //OCR0A erregistroa 10us-tan etena egiteko
    OCR0A = 99;


    //Etenak gaitu
    TIMSK0 |= (1 << OCIE0A);

    //Prescalerra konfiguratu (1)
    TCCR0B |= (1 << CS01);
}


/*
 * Funtzio hau erabilita prescalerra zehaztu daiteke.
 *
 * Parametroak:
 *  -prescaler: Erabili nahi den preskalerrari dagokion zenbakia
 *
 *
 * +-----------+----------+------+------+------+
 * | Prescaler | Zenbakia | CS02 | CS01 | CS00 |
 * +-----------+----------+------+------+------+
 * |         1 |        0 |    0 |    0 |    1 |
 * |         8 |        1 |    0 |    1 |    0 |
 * |        64 |        2 |    0 |    1 |    1 |
 * |       256 |        3 |    1 |    0 |    0 |
 * |      1024 |        4 |    1 |    0 |    1 |
 * +-----------+----------+------+------+------+
 */
int set_prescaler(int prescaler){

    if(prescaler > 4)
	return 0;

    switch(prescaler){
	case 0:
	    TCCR0B |= (1 << CS00);
	    break;
	case 1:
	    TCCR0B |= (1 << CS01);
	    break;
	case 2:
	    TCCR0B |= (1 << CS00);
	    TCCR0B |= (1 << CS01);
	    break;
	case 3:
	    TCCR0B |= (1 << CS02);
	    break;
	case 4:
	    TCCR0B |= (1 << CS00);
	    TCCR0B |= (1 << CS02);
	    break;
    }

    return 1;
}

void delay_us(int us){
    int F;
    int prescaler;

    //CTC moduan konfiguratu
    TCCR0A &=~ (1 << WGM00);
    TCCR0A |= (1 << WGM01);
    TCCR0B &=~ (1 << WGM02);

    //Etenak desgaitu
    TIMSK0 &=~ (1 << OCIE0A);
    //zortiziko prescalerra erabili behar da us < 25 
    //64-ko bestela
    
    if(us < 25){
	set_prescaler(1);
	prescaler = 8;
    }else{
	set_prescaler(2);
	prescaler = 64;
    }
   
    //Kontagailuaren balioa hasieratu
    TCNT0 = 0;

    //Konparazio balio kalkulatu
    F = 1/(us/100000); 
    OCR0A = (F_CPU/2/prescaler/F)-1;

    //Timerraren flag-aren egoera aldatu arte itxaron
    while(!(TIFR0 & (1 << OCF0A)))
	_NOP();

    //Flag-a hasieratu
    TIFR0 |= (1 << OCF0A);
}

void delay_ms(int ms){
    int F;
    int prescaler;

    //CTC moduan konfiguratu
    TCCR0A &=~ (1 << WGM00);
    TCCR0A |= (1 << WGM01);
    TCCR0B &=~ (1 << WGM02);

    //Etenak desgaitu
    TIMSK0 &=~ (1 << OCIE0A);

    //zortiziko prescalerra erabili behar da us < 25 
    //64-ko bestela
    
    set_prescaler(4); 
    prescaler = 1024;
    //Kontagailuaren balioa hasieratu
    TCNT0 = 0;

    //Konparazio balio kalkulatu
    F = 1/(ms/1000); 
    OCR0A = (F_CPU/2/prescaler/F)-1;

    //Timerraren flag-aren egoera aldatu arte itxaron
    while(!(TIFR0 & (1 << OCF0A)))
	_NOP();

    //Flag-a hasieratu
    TIFR0 |= (1 << OCF0A); 
}

ISR(TIMER0_COMPA_vect){
    if(en == 1)
	dht_timeout+=10;
    //if(dht_timeout > 100)
	//PORTB |= (1 << PORTB3);
}
