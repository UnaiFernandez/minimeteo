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

    char mezua[3];
    int i = 0;

    while(1){
        //USART_string("Comunication:\n\r");

        TWI_master_start();
        //USART_string("  1.-START cond sent.\n\r");

        TWI_master_read_addr(0x06);
        //USART_string("  2.-SLA+R sent.\n\r");

        mezua[i] = TWI_master_read_data(0);
        //USART_string("  3.-Data read.\n\r");
        //USART_tx(mezua[i]);
        //USART_string("\n\r");

        TWI_master_stop();
        //USART_string("  4.-STOP cond sent.\n\r");

        i++;
        if(i > 3){
            USART_string("Wind speed ---->  ");
            USART_string(mezua);
            USART_string("m/s");
            USART_string("\n\r");
            i = 0;
        }
        _delay_ms(100);
        //toggle val
    }
}
