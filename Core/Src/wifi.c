#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "main.h"
#include "defines.h"


int send_command(UART_HandleTypeDef *uart, uint8_t * command){
    //Send command
    HAL_UART_Transmit(uart, command, sizeof(command), 10);

    //Receive command
    HAL_UART_Receive(uart, rx_buff, sizeof(rx_buff), 10);
    //sprintf(buff, "AT h: %d", at_h);
    //HAL_UART_Transmit(uart2, "MINIMETEO\n\r", 11, 10);
    //HAL_UART_Transmit(uart2, (uint8_t*) rx_buff, 20, 10);
    
    if(strstr(rx_buff, "OK") == NULL)
        return 1;
    
    return 0;
}



int AT_hello(UART_HandleTypeDef *uart){
    int r = 0;
    r = send_command(uart, (uint8_t *) "ATE0\r\n");
    r += send_command(uart, (uint8_t *) "AT\r\n");
    return r;
}
