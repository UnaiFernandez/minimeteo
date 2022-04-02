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
#include "defines.h"
#include "DHT11.h"


int hezetasuna[2];
int tenperatura[2];
int checksum;

/*--------------------- DHT11  oinarrizko funtzioak ---------------------*/

/*
 * Funtzio hau, DHT11 sentsoreak timeout errorea daukanean, LED gorri bat 
 * piztuko du eta datuak irakurtzeko pin-a berriro prestatuko du irteera 
 * moduan start seinalea bidaltzeko.  
 */
void dht_timeout_error(){
    DDRB |= (1 << PORTB1);	//Irteera moduan konfiguratu
    PORTB &=~ (1 << PORTB1);	//HIGH egoeran jarri
    PORTB |= (1 << PORTB0);	//DHT11-ren LED gorria piztu

    _delay_ms(100);
    get_dht_data();
}

/*
 * Funtzio honek LED gorria eta datuak jasotzeko pin-a prestatu egiten du
 * start seinalea bidaltzeko bidaltzeko.
 */
void dht_init(){
    DDRB |= (1 << PORTB1);	//Pin-a irteera moduan konfiguratu
    PORTB |= (1 << PORTB1);	//LOW egoeran jarri
    
    /*LED-aren konfigurazioa*/
    DDRB |= (1 << PORTB0);	//Irteera moduan konfiguratu pin-a
    PORTB &=~ (1 << PORTB0);	//LED-a itzali
}

/*
 * Funtzio honek start seinalea bidaltzen dio DHT11 sentsoreari
 */
void dht_start(){

    /*
     *    <----- Start seinalea ----->
     *				      |
     *                       <20-40us>| 
     * H  _______            _________| 
     *	         |          |         |
     * L         |__________|         | 
     *            <--18ms-->          | 
     *                                |
     *
     */

    PORTB &=~ (1 << PORTB1);	//1 LOW egoeran jarri Pin-a
    _delay_ms(18);		//2 itxaron 18ms
    PORTB |= (1 << PORTB1);	//3 Pin-a HIGH jarri
}


/*
 * Funtzio honek start seinalea bidali eta gero DHT11 sentsoreak ematen
 * duen erantzunari itxaroten dion. geroago datuak jasotzeko.
 */
void dht_response(){
    
    dht_timeout = 0;
    int error = 0;


    /*
     *    <--------- DHT11 erantzuna --------->
     *				                |
     *                       <--80us-->         | 
     * H  _______            __________         | 
     *	         |          |          |        |
     * L         |__________|          |________|
     *            <--80us-->            <datuak>| 
     *                                          |
     *
     */



    DDRB &=~ (1 << PORTB1);	//6 Pin-a sarrera moduan konfiguratu
    PORTB |= (1 << PORTB1);	//Pull-up erresistentzia ahalbidetu

    init_timer0();
    /*DHT11-ren erantzuna itxaron*/
    while(PINB & (1 << PINB1)){ //Sarrera 1 den bitartea itxaron
	//_delay_us(2);
	//dht_timeout+=2;
	//
	//
	//TODO: timerra itzali
	if(dht_timeout >= 50){ //50us baino gehiago pasatzen badira, komunikazioan arazoren bat dago
	    dht_timeout_error();
	    error++;
	    break;
	}
    }
    
    dht_timeout = 0;

    /*DHT11-k LOW seinalearekin erantzungo du 80us bitartean*/
    while(!(PINB & (1 << PINB1))){ //Sarrera LOW den bitartean itxaron
	//_delay_us(2);
	//dht_timeout+=2;
	if(dht_timeout >= 100){//100us baino gehiago pasatzen bada timeout errorea emango du.
	    dht_timeout_error();
	    error++;
	    break;
	}
    }

    dht_timeout = 0;
    //DHT11-k seinalea HIGH egoerara pasako du 80us-z
    while(PINB & (1 << PINB1)){ //Sarrera HIGH den bitartean itxaron.
	//_delay_us(2);
	//dht_timeout+=2;
	if(dht_timeout >= 100){//100us baino gehiago pasatzen bada timeout errorea emango du.
	    dht_timeout_error();
	    error++;
	    break;
	}
    }

    //Ez bada errorerik LED gorria itzalita mantenduko da.
    if(error == 0)
	PORTB &=~ (1 << PORTB0);
}

/*
 * Funtzio honek DHT11 sentsoreak bidaltzen duen seinaletik datuak aterako ditu.
 */
int dht_data(){

    /*
     *    <--------------- Datuen prozesamendua ---------------->
     *				                                    |
     *                      <28us>           <-- 70us -->           | 
     * H  _______            ____            ____________           | 
     *	         |          |    |          |            |          | 
     * L         |__________|    |__________|            |__________| 
     *            <--54us-->      <--54us-->              <--54us-->| 
     *                                                              |
     *                      (0)                  (1)
     */

    int data = 0, i;

    for(i = 0; i < 8; i++){
	while((PINB & (1 << PINB1)) == 0);  //Sarrera LOW den bitartean itxaron
	_delay_us(35);
	if(PINB & (1 << PINB1)){	    //35us pasa eta gero, sarrera HIGH bada oraindik, datua 1 dela esan nahi du.
	    data = data << 1;
	    data |= 1;
	}else{				    //35us pasa eta gero sarrera LOW badago datua 0 izango da.
	    data = data << 1;
	}
	while(PINB & (1 << PINB1));	    //Sarrera LOW jarri arte itxaron.
    }
    return data;
}


/*
 * Funtzio honen bidez, sentsoreak bidalitako datuak ondo jaso direla egiaztatuko da.
 */
int dht_checksum(int h_osoa, int h_hamar, int t_osoa, int t_hamar, int checksum){
    if(h_osoa + h_hamar + t_osoa + t_hamar != checksum){    //datu guztien batura = checksum den begiratu 
	PORTB |= (1 << PORTB0);				    // LED gorri txikia piztu
	return 0;
    }
    return 1;
}

/*---------------------------------------------------------------------*/



/*------------------------- Datuak eskuratu ---------------------------*/

/*
 * Funtzio hau aurreko oinarrizko funtzio guztiak elkartzen ditu, datuen jasotze prozesua osatzeko.
 */
void get_dht_data(){
    dht_init();
    dht_start();
    dht_response();

    hezetasuna[0] = dht_data();
    hezetasuna[1] = dht_data();
    tenperatura[0] = dht_data();
    tenperatura[1] = dht_data();
    checksum = dht_data();

    dht_checksum(hezetasuna[0], hezetasuna[1], tenperatura[0], tenperatura[1], checksum);

}

/*---------------------------------------------------------------------*/

