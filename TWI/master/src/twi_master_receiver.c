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
    //USART_string("start1\n\r");
    //Transmititu arte itxaron
    while(!(TWCR & (1 << TWINT)));
    //USART_string("start2\n\r");
    //Jasotako erantzuna egiaztatu
    while((TWSR & 0xF8) != 0x08);
    //USART_string("start3\n\r");
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
    //USART_string("Pusimos el addr:");
    //USART_tx(TWDR);
    //USART_string("\n\r");
    /*
     *
     * TWINT garbitu
     * TWEN, TWI gaitzeko
     *
     */
    //USART_string("read1\n\r");
    TWCR = (1 << TWINT) | (1 << TWEN);
    //USART_string("read2\n\r");
    while(!(TWCR & (1 << TWINT)));
    //USART_string("read3\n\r");
    while((TWSR & 0xF8) != TW_MR_SLA_ACK);
    //USART_string("read4\n\r");
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
    //while((TWSR & 0xF8) != TW_MR_DATA_ACK);
    //while((TWSR & 0xF8) != 0x58);
    data = TWDR;
    return data;
}
