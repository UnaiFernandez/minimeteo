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
    while((TWSR & 0xF8) != TW_START);
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
    addr = (addr << 1);
    addr |= 1;
    TWDR = addr;
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


unsigned char TWI_master_read_data(){
    unsigned char data;
    /*
     *
     * TWINT garbitu
     * TWEN, TWI gaitzeko
     *
     */
    //USART_string("data1\n\r");
    TWCR = (1 << TWINT) | (1 << TWEN);
    //USART_string("data2\n\r");
    while(!(TWCR & (1 << TWINT)));
    //USART_string("data3\n\r");
    //while((TWSR & 0xF8) != TW_MR_DATA_ACK);
    while((TWSR & 0xF8) != 0x58);
    //USART_string("data4\n\r");
    data = TWDR;
    //USART_string("data5\n\r");
    return data;
}

