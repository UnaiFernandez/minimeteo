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
#include <string.h>

#include "USART.h"


void init_LED(){
    //LED gorria
    DDRB |= (1 << PORTB5);
    PORTB &=~ (1 << PORTB5);

    //LED berdea
    DDRB |= (1 << PORTB4);
    PORTB &=~ (1 << PORTB4);
}

int main(){
    cli();
    init_USART(9600);
    sei();

    DDRB |= (1 << PORTB3); //Irteera moduan jarri
    PORTB |= (1 << PORTB3); //HIGH egoeran jarri

    unsigned char Anemometer_request[] = { 0x02, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x39 };
    USART_request(Anemometer_request, sizeof(Anemometer_request));

    PORTB &=~ (1 << PORTB3); //LOW jarri mezua jasotzeko
    _delay_ms(100); // 10ms itxaron mezua jaso arte

    int abiadura = get_command[4] - '0';
    //int abiadura = get_command[5] - '0';

    if(abiadura < 10){
        PORTB |= (1 << PORTB5);
        PORTB &=~ (1 << PORTB4);
    }else{
        PORTB |= (1 << PORTB4);
        PORTB &=~ (1 << PORTB5);
    }
    while(1){

    }

}


