/*====================================================================
 *
 *  Filename: twi_master_receiver.c
 *
 *  Description: Fitxategi honen bidez Atmega328p mikroaren TWI modulua
 *               konfiguratu eta bere funtzio negusiak definitzen dira,
 *               esklabutik mezu bat jasotzeko.
 *
 *  Version: 1.0
 *  Created: 2022-05-20
 *  Author: Unai Fernandez
 *
 ====================================================================*/

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#include "twi_master_receiver.h"
#include "USART.h"

int kont = 0;

void init_TWI(){
    TWBR = 72;
    TWCR |= (1 << TWEN);
}

void TWI_master_start(){
    /*
     *
     * TWINT garbitu
     * TWSTA, start egoera bidaltzeko
     * TWEN, TWI gaitzeko
     *
     */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    //Transmititu arte itxaron
    while(!(TWCR & (1 << TWINT)));
    //Jasotako erantzuna egiaztatu
    while((TWSR & 0xF8) != 0x08);
}


void TWI_master_stop(){
    /*
     *
     * TWINT flag-a garbitu
     * TWSTO, stop egoera bidaltzeko
     * TWEN, TWI gaitzeko
     *
     */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}


void TWI_master_read_addr(unsigned char addr){
    //Helbidea eta read instrukzioa TWDR erregistroan jarri
    int read_addr = 1;
    read_addr |= addr << 1;
    TWDR = read_addr;
    /*
     *
     * TWINT garbitu
     * TWEN, TWI gaitzeko
     *
     */
    TWCR = (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
    while((TWSR & 0xF8) != TW_MR_SLA_ACK);
}


unsigned char TWI_master_read_data(int ack){
    unsigned char data;
    /*
     *
     * TWINT garbitu
     * TWEN, TWI gaitzeko
     *
     */
    if(ack == 0){
        TWCR = (1 << TWINT) | (1 << TWEN) | (0 << TWEA);
        while(!(TWCR & (1 << TWINT)));
    }else{
        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
        while(!(TWCR & (1 << TWINT)));
    }
    data = TWDR;
    return data;
}
/*---------------------------------------------------------------------*/
