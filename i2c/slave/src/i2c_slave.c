#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "i2c_slave.h"




//char * msg = "kaixo";
//int msg_len = sizeof(msg);
//int msg_kont = 0;


void init_i2c_slave(){
    TWAR = 0x05;
}


void i2c_slave_transmit_match(){
    while((TWSR & 0xF8) != TW_ST_SLA_ACK){
        PORTB |= (1 << PORT5);
        TWCR = (1 << TWEN)| (1 << TWINT) | (1 << TWEA);
        while(!(TWCR & (1 << TWINT)));
    }
}

void i2c_slave_write(char data){
    TWDR = data;
    TWCR = (1 << TWEN) | (1 << TWINT);
    while(!((TWSR & 0xF8) == TW_ST_DATA_ACK));
}


/*ISR(TWI_vect){
    switch (TW_STATUS)
        {
        case TW_ST_SLA_ACK:     // SLA+R jaso da, eta ACK bidali
            i2c_slave_transmit(msg[msg_kont]);
            TWCR = (0 << TWSTO) | (1 << TWINT) | (1 << TWEA);
            DDRB |= (1 << PORTB3);
            PORTB |= (1 << PORTB3);
            break;
        case TW_ST_DATA_ACK:    // transmitituta eta ACK jasota
            i2c_slave_transmit(msg[msg_kont]);
            if(msg_kont == msg_len-1){
                TWCR = (0 << TWSTO) | (1 << TWINT) | (1 << TWEA);
            }else{
                msg_kont++;
                TWCR = (0 << TWSTO) | (1 << TWINT) | (0 << TWEA);
            }

            break;
        }
}*/
