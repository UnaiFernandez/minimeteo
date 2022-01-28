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


/*

   Aldagai globalak

*/
char nirebuff = '\0';


void init_port(){
    //LED-a hasieratu;
    DDRB |= (1 << PORTB5); 
    PORTB &=~ (1 << PORTB5);
}

int main(){
    int i;

    init_USART(115200);
    sei();
    init_port();
    while(1){}

}

// ISR(USART_RX_vect){
//     cli();
//     nirebuff = UDR0;
//     USART_tx(nirebuff);
// }

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
