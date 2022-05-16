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

#include "i2c.h"


/*
 * Funtzio honen bidez, i2c modulua hasieratu egingo da.
 */
void init_i2c(){

    /*
    SCL = 16000000/(16+2(TWBR))
    */


    TWBR = 32;               // Bit Rate erregistroko balioa
    TWCR |= (1 << TWEN);    // Piztu TWI
}


/*
 * Funtzio honen bidez nagusiak esklabuari, START egoera bat bidaliko dio.
 *
 * Dena ondo badoa, funtzioak 1 balioa bueltatuko du.
 */
int i2c_Start(){
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT))); //Transmititu arte itxaron
    
    if((TWSR & 0xF8) == TW_START)
	    return 1;
    return 0;
}


/*
 * Funtzio honen bidez nagusiak esklabuari, RESTART egoera bat bidaltzen dio.
 *
 * Dena ondo baldin badoa funtzioak 1 balioa bueltatzen du.
 */
int i2c_RStart(){
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));  //Transmititu arte itxaron

    if((TWSR & 0xF8) == TW_RESTART)
	    return 1;
    return 0;
}


/*
 * Funtzio honen bidez, STOP egoera bat bidaltzen zaio esklabuari.
 */
void i2c_Stop(){
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

/*
 * Funtzio honen bidez, eskalbuari egin nahi den ekintza adieraziko zaio
 *
 * Parametroak:
 *  - addr: Esklabuaren helbidea
 *  - r_w: ekintza (read == 1 edo write == 0)
 *
 * Erantzuna zuzena bada, 1 bueltatuko du, bestela 0
 */
int i2c_addr(int addr, int r_w){
    int s_code = 0;

    addr = (addr << 1);

    if(r_w == 0){    //Write
        s_code = TW_SLAVE_W_ACK;
    }else if (r_w == 1){
        s_code = TW_SLAVE_R_ACK;
    }
    while(!(TWCR & (1 << TWINT))); //Transmititu arte itxaro
    if((TWSR & 0xF8) == s_code)
        return 1;
    return 0;
}


/*
 * Funtzio honekin i2c kanalean idatzi egingo da.
 *
 * Parametroak:
 *  - data: bidali nahi den datua.s
 */
int i2c_Write(unsigned char data){
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT))); //Transmititu arte itxaron

    if((TWCR & 0xF8) == TW_DATA_ACK)
        return 1;
    return 0;
}

int i2c_Read(int en_ACK){
    TWCR = (1 << TWINT) | (1 << TWEN) | (en_ACK << TWEA);
    while(!(TWCR & (1 << TWINT)));
    return TWDR;
}
