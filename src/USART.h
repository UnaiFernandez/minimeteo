/*====================================================================
 *
 *  Filename: USART.h
 *
 *  Description: USART.c-rako beharrezkoak diren aldagai eta funtzioen
 *		 definizioak.
 *
 *  Version: 1.0
 *  Created: 2021-11-02
 *  Author: Unai Fernandez
 *
 ====================================================================*/

#ifndef USART_H
#define USART_H

#define BUFF_SIZE 5
extern char tmp_buff;
extern char response [BUFF_SIZE];
extern int resp_index;
extern int comm_index;
extern char get_command [5];


/*---- USART hasieratu ----*/
void init_USART(long int baud);

/*---- USART transmititu ----*/
void USART_tx(char d);

/*---- USART datua jaso ----*/
char USART_rx();

/*---- USART bidali string ----*/
void USART_string(char * string);

#endif //USART_H
