/*====================================================================
 *
 *  Filename: USART.c
 *
 *  Description: Fitxategi honen bidez Atmega328p mikroaren UART modulua 
 *               konfiguratu eta bere funtzio negusiak definitzen dira.
 *
 *  Version: 1.0
 *  Created: 2021-02-09
 *  Author: Unai Fernandez
 *
 ====================================================================*/

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "USART.h"
#include "wifi.h"

int resp_index = 0;
int resp_first = 0;
char tmp_buff = '\0';
char response[BUFF_SIZE];

void init_USART(long int baud){
  
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


//Eten zerbitzu errutina
ISR(USART_RX_vect){
    tmp_buff = UDR0;

    //Jasotako mezuaren lehen letra 'O' edo 'E' bada, komando baten 
    //responsea dela esan nahi du. 
    if(tmp_buff == 'O' || tmp_buff == 'E' || resp_first == 1){

	//ESP-01 moduluak bidaltzen dituen karaktereak response bufferrean jaso
    	response[resp_index] = tmp_buff;
    	resp_index++;
	resp_first = 1;
    	
    	if(resp_index == BUFF_SIZE || tmp_buff == '\r'){
    	    resp_index = 0;
    	    resp_first = 0;
    	    //response_status=1;
    	}

    }
    
}
