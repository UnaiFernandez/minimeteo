#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "twi_slave_transmitter.h"


int main(){
    char msg[3] = "2A";
    int i = 0;
    int val = 90;
    DDRB |= (1 << PORTB5);
    PORTB &=~ (1 << PORTB5);
    init_TWI_slave();
    while(1){
        //sprintf(msg, "%dm/s", val);
        TWI_slave_write_match();
        TWI_slabe_write_data(msg[i]);
        if(i < 3){
            i++;
        }else{
            i = 0;
            val++;
        }
        _delay_ms(100);
    }
}
