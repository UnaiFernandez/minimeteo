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

    //
    DDRB |= (1 << PORTB1); //Irteera moduan jarri
}

int main(){
    init_USART(9600);
    init_LED();

    sei();
    _delay_ms(100);

    while(1){
        PORTB |= (1 << PORTB1); //HIGH egoeran jarri
        //_delay_ms(100);

        uint8_t Anemometer_request[] = { 0x02, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x39 };
        //uint8_t Anemometer_request[] = { 0x4B, 0x41, 0x49, 0x58, 0x4F, 0x4F, 0x4F, 0x0D };
        USART_request(Anemometer_request, sizeof(Anemometer_request));
        //USART_flush();
        //_delay_ms(100);
        PORTB &=~ (1 << PORTB1); //LOW jarri mezua jasotzeko
        //_delay_ms(100); // 10ms itxaron mezua jaso arte

        //uint8_t nirechar = USART_rx();
        //int abiadura = get_command[4] - '0';
        //int abiadura = get_command[0] - '0';

        /*if(abiadura == 0x00){
            PORTB |= (1 << PORTB5);
            PORTB &=~ (1 << PORTB4);
        }else{
            PORTB |= (1 << PORTB4);
            PORTB &=~ (1 << PORTB5);
        }*/
        PORTB ^= (1 << PORTB4);
        _delay_ms(1000);
    }

}
