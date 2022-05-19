/*====================================================================
 *
 *  Filename: main.c
 *
 *  Description: Main file for USART
 *
 *  Version: 1.0
 *  Created: 2022-02-11
 *  Author: Unai Fernandez
 *
 ====================================================================*/

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include "USART.h"
#include "i2c.h"
#include "defines.h"

char msg[MSG_SIZE];
int get_data = 0;
char a;

int main(){
    _delay_ms(2000);
    //UART modulua hasieratu 115200 baud-etara
    init_USART(9600);
    init_i2c_master();
    //etenak gaitu
    DDRD |= (1 << PORTB5);
    DDRD |= (1 << PORTB4);
    sei();

    _delay_ms(100);

    while(1){
    /*------------------------ I2C receive data ------------------------*/

    // Proba ondo joan dela jakiteko, "kaixo" mezua agertu beharko da
    // pantailaratuta.

    USART_string("Lets go...\n\r");
    i2c_Start();
    USART_string("Start\r\n");
    i2c_slave_addr(0x05, 0);
    USART_string("SLA+R\r\n");
    //for(int i = 0; i < MSG_SIZE-1; i++){
    //    msg[i] = i2c_master_receive(1);
    //}
    //msg[4] = i2c_master_receive(0);
    a = i2c_master_receive(0);
    USART_string("MSG\r\n");
    i2c_Stop();
    USART_string("STOP\r\n");

    _delay_ms(1000);

    USART_string("DONE!\r\n");
    USART_string("msg = ");
    /*------------------------- USART send data ------------------------*/
    USART_string(msg);


    _delay_ms(1000);


    }

}


