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
char urx = '\0';
int transmit = 0;
int comm_length = 0;

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
    _delay_ms(3000);
    USART_string("AT\r");
    
    while(1){
	_delay_ms(500);
	if(transmit == 1){
	    char response[comm_length+1];
	    for(i = 0; i <= comm_length; i++){
		response[i] = rd_buffer();
		//USART_tx(rd_buffer());
	    }
	    
	    if(!strcmp(response, "")){
	    //if(strstr("eoeoeOKaaa", "OK") != NULL){
		PORTB |= (1 << PORTB4); //LED berdea piztu
		PORTB &=~ (1 << PORTB5); //LED gorria itzali
	    }else{
		PORTB |= (1 << PORTB5); //LED gorria piztu
		PORTB &=~ (1 << PORTB4); //LED berdea itzali
		USART_string(response);
	    }
	    //USART_string(response);
	    //USART_string("\n\r");
	    
	    comm_length = 0;
	    transmit = 0;
	}
    }
}

//Eten zerbitzu errutina
ISR(USART_RX_vect){
    urx = UDR0;
    
    if(urx == '\r'){ //End of a command
	transmit = 1;
	comm_length = length + 1;
    }
    
    wr_buffer(UDR0);
}
