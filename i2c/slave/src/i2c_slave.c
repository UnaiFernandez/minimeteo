#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "i2c_slave.h"

#define TW_STATUS (TWSR & 0xF8)



char * msg = "kaixo";
int msg_len = sizeof(msg);
int msg_kont = 0;


void init_i2c_slave(int addr){
    TWAR = addr << 1;
    TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT) | (1 << TWEA);
}


void i2c_slave_transmit(unsigned char data){
    TWDR = data;
}


ISR(TWI_vect){
    switch (TW_STATUS)
        {
        case TW_ST_SLA_ACK:     // SLA+R jaso da, eta ACK bidali
            i2c_slave_transmit(msg[msg_kont]);
            TWCR = (0 << TWSTO) | (1 << TWINT) | (1 << TWEA);
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
}
