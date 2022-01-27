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
}

int main(){
    int i;
    
    init_USART();
    sei();
    init_port();
    
    while(1){
	_delay_ms(500);
	if(transmit == 1){
	    for(i = 0; i <= comm_length; i++){
		USART_tx(rd_buffer());
	    }
	    USART_string("\n\r");
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
