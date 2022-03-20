/*====================================================================
 *
 *  Filename: DHT11.c
 *
 *  Description: Fitxategi honen bidez Atmega328p mikroaren eta DHT11 
 *               sentsorearen artean komunikazioa egon dadin beharrezkoak
 *               diren funtzioak sortuko dira.
 *
 *  Version: 1.0
 *  Created: 2022-03-18
 *  Author: Unai Fernandez
 *
 ====================================================================*/



#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "timers.h"

void dht_timeout_error(){
    DDRB |= (1 << PORTB1); //Irteera moduan konfiguratu
    PORTB &=~ (1 << PORTB1); //HIGH egoeran jarri
    PORTB |= (1 << PORTB0); //DHT11-ren LED gorria piztu
}

void dht_init(){
    DDRB |= (1 << PORTB1); //Pin-a irteera moduan konfiguratu
    PORTB |= (1 << PORTB1); //LOW egoeran jarri
    
    //LED-aren konfigurazioa
    DDRB |= (1 << PORTB0);
    PORTB &=~ (1 << PORTB0);
}

void dht_start(){
    //2 LOW egoeran jarri Pin-a
    PORTB &=~ (1 << PORTB1);
    //3 itxaron 18ms
    _delay_ms(18);
    //4 Pin-a HIGH jarri
    PORTB |= (1 << PORTB1);
}

void dht_response(){

    dht_timeout = 0;
    int error = 0;
    en = 1;
    //6 Pin-a sarrera moduan konfiguratu
    DDRB &=~ (1 << PORTB1);
    PORTB |= (1 << PORTB1);
    // DHT11-ren erantzuna itxaron
    while(PINB & (1 << PINB1)){
	//delay_us(2);
	//dht_timeout+=2;
	if(dht_timeout >= 50){
	    dht_timeout_error();
	    error++;
	    en = 0;
	    break;
	}
    }
    
    dht_timeout = 0;

    //DHT11-k LOW seinalearekin erantzungo du 80us bitartean
    while(!(PINB & (1 << PINB1))){
	//delay_us(2);
	//dht_timeout+=2;
	if(dht_timeout >= 100){
	    dht_timeout_error();
	    error++;
	    en = 0;
	    break;
	}
    }

    dht_timeout = 0;
    //DHT11-k seinalea HIGH egoerara pasako du 80us-z
    while(PINB & (1 << PINB1)){
	//delay_us(2);
	//dht_timeout+=2;
	if(dht_timeout >= 100){
	    dht_timeout_error();
	    error++;
	    en = 0;
	    break;
	}
    }
    en = 0;

    if(error == 0)
	PORTB &=~ (1 << PORTB0);
}


int dht_data(){
    int data = 0, i;

    for(i = 0; i < 8; i++){
	while((PINB & (1 << PINB1)) == 0);
	_delay_us(35);
	if(PINB & (1 << PINB1)){
	    data = data << 1;
	    data |= 1;
	}else{
	    data = data << 1;
	}
	while(PINB & (1 << PINB1));
	//while(PINB & (1 << PINB1));
    }
    //DDRB |= (1 << PORTB1);

    return data;
}


int dht_checksum(int h_osoa, int h_hamar, int t_osoa, int t_hamar, int checksum){
    if(h_osoa + h_hamar + t_osoa + t_hamar != checksum){
	PORTB |= (1 << PORTB0); // LED gorri txikia piztu
	return 0;
    }
    return 1;
}
