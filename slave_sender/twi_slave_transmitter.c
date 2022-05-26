/*====================================================================
 *
 *  Filename: twi_slave_transmitter.c
 *
 *  Description: Fitxategi honen bidez Atmega328p mikroaren TWI modulua
 *               konfiguratu eta bere funtzio negusiak definitzen dira,
 *               nagusira mezu bat bidaltzeko.
 *
 *  Version: 1.0
 *  Created: 2022-05-20
 *  Author: Unai Fernandez
 *
 ====================================================================*/

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "twi_slave_transmitter.h"

int ind = 0;
extern char msg[6];

void init_TWI_slave(){
    DDRC &=~ (1 << PORTC5);
    DDRC &=~ (1 << PORTC4);
    PORTC = (1 << PORTC4) | (1 << PORTC5);
    TWBR = 72;
    TWCR  = (1 << TWEN) | (1 << TWEA);
    TWAR = 0x06 << 1;
}


void TWI_slave_write_match(){
    TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT);
    while(!(TWCR & (1 << TWINT)));
    while((TWSR & 0xF8) != TW_ST_SLA_ACK);
}


void TWI_slabe_write_data(unsigned char data){
    TWDR = data;

    if((TWSR & 0xF8) == TW_ST_DATA_NACK){
        TWCR = (1 << TWEN) | (1 << TWINT);
    }else{
        TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    }
}
