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
    
    //Wifi modulua hasieratu
    int start = hello_ESP();
    //Operazio modua aukeratu
    ESP_mode(AP);
    //AP-aren konfigurazioa
    AP_setup("MINIMETEO_v.1", "12345678", '1', '4');
    if(start == 1){
        PORTB |= (1 << PORTB4); //LED berdea piztu
        PORTB &=~ (1 << PORTB5); //LED gorria itzali
    }else{
        PORTB |= (1 << PORTB5); //LED gorria piztu
        PORTB &=~ (1 << PORTB4); //LED berdea itzali
    }

    while(1){}
}


