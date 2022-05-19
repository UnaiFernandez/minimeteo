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
#include "USART.h"


/*
 * Funtzio honen bidez, i2c modulua hasieratu egingo da.
 */
void init_i2c_master(){

    /*
    SCL = 16000000/(16+2(TWBR))
    */

    TWBR = 72;// Bit Rate erregistroko balioa
    //TWSR = (1 << TWPS1) | (1 << TWPS0);
    //TWCR |= (1 << TWEN);    // Piztu TWI
}


/*
 * Funtzio honen bidez nagusiak esklabuari, START egoera bat bidaliko dio.
 *
 * Dena ondo badoa, funtzioak 1 balioa bueltatuko du.
 */
void i2c_Start(){
    USART_string("Start hasiera\n\r");
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    USART_string("Start bitak eta gero\n\r");
    while(!(TWCR & (1 << TWINT))); //Transmititu arte itxaron
    USART_string("Transmititu eta gero\n\r");
    while(!((TWSR & 0xF8) == TW_START));
    //if((TWSR & 0xF8) == TW_START)
	//    return 1;
    //return 0;
    //return 1;
}


/*
 * Funtzio honen bidez nagusiak esklabuari, RESTART egoera bat bidaltzen dio.
 *
 * Dena ondo baldin badoa funtzioak 1 balioa bueltatzen du.
 */
void i2c_RStart(){
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));  //Transmititu arte itxaron

    while(!((TWSR & 0xF8) == TW_RESTART));
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
void i2c_slave_addr(int addr, int r_w){
    int s_code = 0;

    addr = (addr << 1);

    if(r_w == 0){    //Write
        addr &=~ 1;
        s_code = TW_MT_SLA_ACK;
    }else if (r_w == 1){
        addr |= 1;
        s_code = TW_MR_SLA_ACK;
    }
    TWDR=addr;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT))); //Transmititu arte itxaro
    while(!((TWSR & 0xF8) == s_code));
}


/*
 * Funtzio honekin i2c kanalean idatzi egingo da.
 *
 * Parametroak:
 *  - data: bidali nahi den datua.s
 */
void i2c_master_transmit(unsigned char data){
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT))); //Transmititu arte itxaron

    while(!((TWCR & 0xF8) == TW_MT_DATA_ACK));
}


/*
 * Funtzio honen bidez nagusiak esklabuak bidaltzen dituen mezuak jasoko ditu
 *
 * Parametroak:
 *  - en_ACK: Nagusiak mezua jasotzean ACK bidaltzen badu, beste mezu bat
 *            jasotzeko prestatuta dagoela esan nahi du. NACK bidaltzean
 *            komunikazioa bukatu egingo da.
 *
 * Funtzioak jasotako mezua buektatuko du.
 */
char i2c_master_receive(int en_ACK){
    TWCR = (1 << TWINT) | (1 << TWEN) | (en_ACK << TWEA);
    while(!(TWCR & (1 << TWINT)));
    return TWDR;
}
