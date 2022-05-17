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

int main(){
    //UART modulua hasieratu 115200 baud-etara
    init_USART(9600);
    init_i2c_master();
    //etenak gaitu
    sei();

    _delay_ms(100);

    /*------------------------ I2C receive data ------------------------*/

    // Proba ondo joan dela jakiteko, "kaixo" mezua agertu beharko da
    // pantailaratuta.


    while(!i2c_Start());
    while(!i2c_slave_addr(0x01, 0));
    for(int i = 0; i < MSG_SIZE-1; i++){
        msg[i] = i2c_master_receive(1);
    }
    msg[4] = i2c_master_receive(0);
    i2c_Stop();

    /*------------------------- USART send data ------------------------*/
    USART_string(msg);




    while(1){

    }

}


