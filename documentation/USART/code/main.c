/*====================================================================
 *
 *  Filename: main.c
 *
 *  Description: this file is for adfjadkfljaslkjdfas
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

char nirebuff = '\0';

void init_port(){
    //LED-a hasieratu;
    DDRB |= (1 << PORTB5); 
    PORTB &=~ (1 << PORTB5);
}

int main(){
    
    init_USART();
    init_port();
    while(1){
	//char c = USART_rx();
//	if(nirebuff == 'h'){
//	    USART_string("bidalitako karakterea: ");
//	    USART_tx(nirebuff);
//	    USART_string("\n\r");
//	}
    }

   /* int a = 234;
    int ehun = '0' + (a/100);
    int hamar = '0' + ((a/10)%10);
    int bateko = '0' + (a%10);
    printf("%c%c%c\n", ehun, hamar, bateko);*/
}

ISR(USART_RX_vect){
    nirebuff = UDR0;

    USART_string("tekla: ");
    USART_tx(nirebuff);
    USART_string(" ---> ");
    
    if(nirebuff == '1'){
	PORTB |= (1 << PORTB5);
	USART_string("LED on!\n\r");
    }

    if(nirebuff == '2'){
	PORTB &=~ (1 << PORTB5);
	USART_string("LED off!\n\r");
    }
}
