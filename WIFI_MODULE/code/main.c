/*====================================================================
 *
 *  Filename: main.c
 *
 *  Description: Main file for USART
 *
 *  Version: 1.0
 *  Created: 2021-11-02
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
    //LED-a hasieratu;
    DDRB |= (1 << PORTB5); 
    PORTB &=~ (1 << PORTB5);

    DDRB |= (1 << PORTB4);
    PORTB &=~ (1 << PORTB4);
}





int main(){
    init_USART(115200);
    sei();
    init_port();
    _delay_ms(100);
    int start = send_command("AT", "OK");
    if(start == RESPONSE_OK){
        PORTB |= (1 << PORTB4); //LED berdea piztu
        PORTB &=~ (1 << PORTB5); //LED gorria itzali
    }else{
        PORTB |= (1 << PORTB5); //LED gorria piztu
        PORTB &=~ (1 << PORTB4); //LED berdea itzali
    }

    while(1){}
}


