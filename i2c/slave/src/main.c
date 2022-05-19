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

#include "i2c_slave.h"

char * msg = "kaixo";
int msg_len = sizeof(msg);
int msg_kont = 0;

int main(){
    init_i2c_slave();

    int i = 0;

    DDRB |= (1 << PORTB5);
    while(1){
        i2c_slave_transmit_match();
        i2c_slave_write(msg[i]);
        if(i < 5)
            i++;
        else
            i = 0;
    }

}


