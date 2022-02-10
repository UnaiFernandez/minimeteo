#define F_CPU 16000000
#include <util/delay.h>
#include <string.h>

#include "wifi.h"
#include "USART.h"


int send_command(char * command, char * resp){
    
    //Bidali komandoa
    USART_string(command);
    USART_string("\r\n");
    response_status = RESPONSE_WAITING;
    _delay_ms(1);  //mezua jasotzeko 1ms itxaron

    //LED berdea pizteko komandoa bidali
    //if(response_status == 1){
    if(strstr(response, resp) != NULL)
	response_status = RESPONSE_OK;
    else
	response_status = RESPONSE_ERROR;
    //}
    return response_status;
}
