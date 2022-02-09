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
#include <string.h>

#include "USART.h"


/*

   Aldagai globalak

*/
char nirebuff = '\0';
char tmp_buff = '\0';
int transmit = 0;
int comm_length = 0;
int kont = 0;
int response_ok = 0;
char response [5];
int resp_index = 0;

void init_port(){
    //LED-a hasieratu;
    DDRB |= (1 << PORTB5); 
    PORTB &=~ (1 << PORTB5);

    DDRB |= (1 << PORTB4);
    PORTB &=~ (1 << PORTB4);
}

int main(){
    int i;
    
    init_USART(115200);
    sei();
    init_port();
    _delay_ms(100);
    USART_string("AT\r\n");
    _delay_ms(100);
    if(response_ok == 1){
        PORTB |= (1 << PORTB4); //LED berdea piztu
        PORTB &=~ (1 << PORTB5); //LED gorria itzali
    }else{
        PORTB |= (1 << PORTB5); //LED gorria piztu
        PORTB &=~ (1 << PORTB4); //LED berdea itzali
    }

    while(1){}
}

//Eten zerbitzu errutina
ISR(USART_RX_vect){
    tmp_buff = UDR0;
    
    //ESP-01 moduluak bidaltzen dituen karaktereak response bufferrean jaso
    response[resp_index] = tmp_buff;
    resp_index++;
    
    //LED berdea pizteko komandoa bidali
    if(resp_index == 5){
	resp_index = 0;
	if(strstr(response, "OK") != NULL)
	    response_ok = 1;
    }
}