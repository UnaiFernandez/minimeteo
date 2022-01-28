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

/*
Funtzio honen bidez, parametro moduan zehaztutako komandoak bidali egingo dira UART bidez
*/
void send_command(char * com){
    USART_string(com);
    //response ok bada led-a piztu
}


int main(){
    init_USART();
    sei();
    while(1){
    }
}

/*
Etenen bidez datuen jasoketa egiteko.
*/
ISR(USART_RX_vect){
    cli();
    nirebuff = UDR0;
    USART_tx(nirebuff);
}
