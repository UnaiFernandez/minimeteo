/*====================================================================
 *
 *  Filename: main.c
 *
 *  Description: Main file for USART
 *
 *  Version: 1.0
 *  Created: 2022-02-11
 *  Author: Unai Fernandez
 *
 ====================================================================*/

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include "USART.h"
#include "wifi.h"
#include "timers.h"
#include "DHT11.h"


void init_LED(){
    //LED gorria
    DDRB |= (1 << PORTB5); 
    PORTB &=~ (1 << PORTB5);

    //LED berdea
    DDRB |= (1 << PORTB4);
    PORTB &=~ (1 << PORTB4);

    //LED horia
    DDRB |= (1 << PORTB3);
    PORTB &=~ (1 << PORTB3);

    //DHT11 LED
    DDRB |= (1 << PORTB0);
    PORTB &=~ (1 << PORTB0);
}





int main(){
    //UART modulua hasieratu 115200 baud-etara
    init_USART(115200);
    //etenak gaitu
    sei();
    //LED-ak hasieratu;
    init_LED();

    _delay_ms(100);
    
    /*------------------- Wifiaren konfigurazioa ---------------------*/
    int start = 1;
    //Wifi modulua hasieratu
    if(!hello_ESP())
	start = 0;
    //Operazio modua aukeratu
    if(!ESP_mode(AP))
	start = 0;
    //AP-aren konfigurazioa
    if(!AP_setup("MINIMETEO_v.1", "12345678", 1, 4))
	start = 0;
    //Konexio anitzak gaitu
    if(!ESP_multiple_conn(1))
	start = 0;
    //Zerbitzaria hasieratu 4567 portuan
    if(!ESP_server(1,"4567"))
	start = 0;
    //Zerbitzariaren timeouta ezarri
    if(!ESP_server_timeout("120"))
	start = 0;

    if(start == 1){
        PORTB |= (1 << PORTB4); //LED berdea piztu
        //PORTB &=~ (1 << PORTB5); //LED gorria itzali
    }else{
        PORTB |= (1 << PORTB5); //LED gorria piztu
        //PORTB &=~ (1 << PORTB4); //LED berdea itzali
    }

    /*------------------------------------------------------------------*/ 
    

    init_timer0();

    int t = 0;
    while(1){
	//delay_ms(30);
	//t += 30;
	//if(t >= 1000){
	//    PORTB ^= (1 << PORTB4);
	//    t = 0;
	//}
	_delay_ms(2);
	if(send_msg == 1){
	    TCP_response(get_command);
	    send_msg = 0;
	}

	t+=2;
	if(t >= 2000){
	    get_dht_data();
	    //._delay_ms(2000);
	    t = 0;
	}
    }

}


