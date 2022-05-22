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

#include "twi_slave_transmitter.h"

void init_TWI_slave(){
    TWAR = 0x06 << 1;
    TWCR  |= (1 << TWEN);
}

void TWI_slave_write_match(){
    while((TWSR & 0xF8) != TW_ST_SLA_ACK){
        PORTB |= (1 << PORTB5);
        TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT);
        while(!(TWCR & (1 << TWINT)));
    }
}


void TWI_slabe_write_data(unsigned char data){
    TWDR = 'a';
    TWCR = (1 << TWEN) | (1 << TWINT);
    while((TWSR & 0xF8) != TW_ST_DATA_ACK);
}

