int send_command(UART_HandleTypeDef *uart, uint8_t * command);
int send_command_debug(UART_HandleTypeDef *uart, UART_HandleTypeDef *uart2, uint8_t * command);
int AT_hello(UART_HandleTypeDef *uart);
