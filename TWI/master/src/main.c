#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#include "twi_master_receiver.h"
#include "USART.h"


int main(){
    _delay_ms(2000);
    init_USART(9600);
    init_TWI();
    _delay_ms(100);

    DDRB |= (1 << PORTB5);
    PORTB &=~ (1 << PORTB5);
    DDRB |= (1 << PORTB4);
    PORTB &=~ (1 << PORTB4);

    unsigned char val;

    while(1){
        USART_string("Comunication:\n\r");

        TWI_master_start();
        USART_string("  1.-START cond sent.\n\r");

        TWI_master_read_addr(0x06);
        USART_string("  2.-SLA+R sent.\n\r");

        val = TWI_master_read_data(0);
        USART_string("  3.-Data read.\n\r");

        TWI_master_stop();
        USART_string("  4.-STOP cond sent.\n\r");

        USART_string("Received value: ");
        USART_tx(val);
        USART_string("\n\r");
        _delay_ms(4000);
        //toggle val
    }
}

