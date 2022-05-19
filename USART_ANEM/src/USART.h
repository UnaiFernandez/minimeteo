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

#define BUFF_SIZE 8
#define BUFF_SIZE2 19
extern uint8_t tmp_buff;
extern uint8_t response [BUFF_SIZE];
extern uint8_t get_command [BUFF_SIZE];
extern int resp_index;
extern int send_msg;


/*---- USART hasieratu ----*/
void init_USART(long int baud);

/*---- USART transmititu ----*/
void USART_tx( uint8_t d);

/*---- USART datua jaso ----*/
uint8_t USART_rx();

/*---- USART bidali string ----*/
void USART_request( uint8_t * req, int tam);

void USART_flush();

#endif //USART_H
