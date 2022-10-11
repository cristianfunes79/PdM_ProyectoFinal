/*
 * AIP_uart.h
 *
 *  Created on: Oct 11, 2022
 *      Author: cfunes
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include "usart.h"

typedef enum
{
	UART_OK = 0,
	UART_ERROR
}API_uart_status_t;

void API_uart_init(void);
API_uart_status_t API_uart_send(char* data, uint16_t len);

#endif /* API_INC_API_UART_H_ */
