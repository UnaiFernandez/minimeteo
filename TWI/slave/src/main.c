#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#include "twi_slave_transmitter.h"


int main(){

    DDRB |= (1 << PORTB5);
    PORTB &=~ (1 << PORTB5);
    init_TWI_slave();
    while(1){
        TWI_slave_write_match();
        TWI_slabe_write_data('a');
    }
}

