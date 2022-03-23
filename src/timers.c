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
#include <avr/cpufunc.h>
#include <avr/interrupt.h>


#include "timers.h"
#include "DHT11.h"
#include "defines.h"


volatile int dht_timeout = 0;
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
    //OCR0A = 250;

    //Etenak gaitu
    TIMSK0 |= (1 << OCIE0A);

    //Prescalerra konfiguratu (1)
    TCCR0B |= (1 << CS01);
    //TCCR0B |= (1 << CS00);
    //TCCR0B |= (1 << CS02);
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

ISR(TIMER0_COMPA_vect){
    //if(timeout_en == 1){
    //    dht_timeout+=10;
    //}
    //if(timeout_init == 1){
    //    dht_timeout = 0;
    //    timeout_init = 0;
    //}
    if(en == 1)
	dht_timeout+=10;
    //if(dht_timeout > 1000)
    //    PORTB |= (1 << PORTB4);
    //if(dht_timeout == 0)
	//PORTB &=~ (1 << PORTB4);
}

/*-------------------- Timer 1 ----------------------*/

void init_timer1(){
    //CTC moduan hasieratu
    TCCR1B &=~ (1 << WGM13);
    TCCR1B |= (1 << WGM12);
    TCCR1A &=~ (1 << WGM11);
    TCCR1A &=~ (1 << WGM10);

    //2 segunduro egingo du etena
    OCR1A = 65535;

    //Etenak gaitu
    TIMSK1 |= (1 << OCIE1A);

    //Prescalerra
    TCCR1B |= (1 << CS12);
    TCCR1B &=~ (1 << CS11);
    TCCR1B &=~ (1 << CS10);
    
}

ISR(TIMER1_COMPA_vect){
    get_dht_data();
    //PORTB ^= (1 << PORTB5);
}
