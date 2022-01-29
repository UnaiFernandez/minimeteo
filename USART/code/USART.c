/*====================================================================
 *
 *  Filename: USART.c
 *
 *  Description: Fitxategi honen bidez Atmega328p mikroaren UART modulua 
 *               konfiguratu eta bere funtzio negusiak definitzen dira.
 *
 *  Version: 1.0
 *  Created: 2021-10-28
 *  Author: Unai Fernandez
 *
 ====================================================================*/

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "USART.h"

void init_USART(long int baud){
    init_buffer();
    
    //UCRS0C
    /*---- USART asinkrono moduan konfiguratu ----*/
    UCSR0C &=~ (1 << UMSEL00); 
    UCSR0C &=~ (1 << UMSEL01);
    /*---- Paritatea galarazi ----*/
    UCSR0C &=~ (1 << UPM00);
    UCSR0C &=~ (1 << UPM01);
    /*---- Stop bit bakarra ----*/
    UCSR0C &=~ (1 << USBS0);
    /*---- Datuen tamaina 8bitekoa ----*/
    UCSR0C |= (1 << UCSZ00);
    UCSR0C |= (1 << UCSZ01);
    UCSR0B &=~ (1 << UCSZ02);	//kasu honetan behar den azkeneko bita UCSR0B erregistroan dago kokatuta.

    //UCSR0B
    /*---- datuen transmisioa eta jasoketa gaitu ----*/
    UCSR0B |= (1 << TXEN0);
    UCSR0B |= (1 << RXEN0);

    /*---- BAUD rate zehaztu ----*/
    UCSR0A |= (1 << U2X0);
    //UBRR0 = 207;
    //UBRR0 = 16;
    UBRR0 = (F_CPU/baud/8)-1;

    /*---- Etenak gaitu datuak jasotzeko ----*/
    UCSR0B |= (1 << RXCIE0); 
}


void USART_tx(char d){
    UDR0 = d;
    while(!(UCSR0A & (1 << UDRE0)));
}

char USART_rx(){
    while(!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void USART_string(char * string){
    while(*string != 0x00){
	USART_tx(*string);
	string++;
    }
}


/*#############################################*/


void init_buffer(){
    wr = 0;
    rd = 0;
    length = 0;
}

void wr_buffer(char data){
    if(wr == BUFF_SIZE) //Change position of the wr pointer when it reaches BUFF_SIZE
	wr = 0;

    buff[wr] = data;

    wr++;
    length++;
}


char rd_buffer(){
    char rd_data;

    if(rd == BUFF_SIZE) //Change position of the wr pointer when it reaches BUFF_SIZE
	rd = 0;

    rd_data = buff[rd];

    rd++;
    length--;

    return rd_data;
}


