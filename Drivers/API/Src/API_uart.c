/*
 * API_uart.c
 *
 *  Created on: Oct 11, 2022
 *      Author: cfunes
 */
#include "API_uart.h"

void API_uart_init(void)
{
	MX_USART3_UART_Init();
}

API_uart_status_t API_uart_send(char* data, uint16_t len)
{
	HAL_UART_Transmit(&huart3, (uint8_t*)data, len, len);
}


