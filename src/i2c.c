/*====================================================================
 *
 *  Filename: i2c.c
 *
 *  Description: Fitxategi honen bidez bi Atmega328p mikroen artean 
 *		 komunikazioa i2c-ren bidez egon dadin beharrezkoak 
 *		 diren funtzioak sortuko dira. 
 *
 *  Version: 1.0
 *  Created: 2022-05-03
 *  Author: Unai Fernandez
 *
 ====================================================================*/
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

void init_i2c(){
    TWBR = //bit rate 16MHz / (16+2*TWBR*1) 
    TWCR |= (1 << TWEN);
}

void i2c_Start(){
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while(!(TWCR0 & (1 << TWINT)));
}

void i2c_Stop(){
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}
void i2c_Write(unsigned char data){
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
}

int i2c_ACK(){
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while(!(TWCR & (1 << TWINT)));
    return TWDR;
}

int i2c_NACK(){
    TWCR = (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWEN)));
    return TWDR;
}
