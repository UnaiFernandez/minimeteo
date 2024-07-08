#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"


int send_command(UART_HandleTypeDef *uart, uint8_t * command){
    char ack [10] = "";

    //Send command
    HAL_UART_Transmit(uart, command, sizeof(command), 10);

    //Receive command
    HAL_UART_Receive(uart, ack, sizeof(ack), 10);

    if(strstr(ack, "OK") == NULL)
        return 1;
    
    return 0;
}



int AT_hello(){
    int r = 0;
    r = send_command("ATE0", "OK");
    r += send_command("AT", "OK");
    return r;
}
