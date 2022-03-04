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

#include "USART.h"
#include "wifi.h"



void init_port(){
    //LED gorria
    DDRB |= (1 << PORTB5); 
    PORTB &=~ (1 << PORTB5);

    //LED berdea
    DDRB |= (1 << PORTB4);
    PORTB &=~ (1 << PORTB4);
}





int main(){
    //UART modulua hasieratu 115200 baud-etara
    init_USART(115200);
    //etenak gaitu
    sei();
    //LED-ak hasieratu;
    init_port();

    _delay_ms(100);
    
    int start = 1;
    //Wifi modulua hasieratu
    if(!hello_ESP())
	start = 0;
    //Operazio modua aukeratu
    start = ESP_mode(AP);
    if(!ESP_mode(AP))
	start = 0;
    //AP-aren konfigurazioa
    if(!AP_setup("MINIMETEO_v.2", "12345678", 1, 4))
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
        PORTB &=~ (1 << PORTB5); //LED gorria itzali
    }else{
        PORTB |= (1 << PORTB5); //LED gorria piztu
        PORTB &=~ (1 << PORTB4); //LED berdea itzali
    }

     

    while(1){
	_delay_ms(100);
	if(send_msg == 1){
	    TCP_response(get_command);
	    //char a [] = "que tal";
	    ////////char *a = "hola\n\r";
	    ////////TCP_send('0', "7", a); 
	    //TCP_send(0, "6", "que lal");
	    send_msg = 0;
	}

	
    }

}


