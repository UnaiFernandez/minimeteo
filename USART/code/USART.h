/*====================================================================
 *
 *  Filename: USART.h
 *
 *  Description: this file is for adfjadkfljaslkjdfas
 *
 *  Version: 1.0
 *  Created: 2021-11-02
 *  Author: Unai Fernandez
 *
 ====================================================================*/



#define BAUD 9600


/*---- USART hasieratu ----*/
void init_USART(long int baud);

/*---- USART transmititu ----*/
void USART_tx(char d);

/*---- USART datua jaso ----*/
char USART_rx();

/*---- USART bidali string ----*/
void USART_string(char * string);
