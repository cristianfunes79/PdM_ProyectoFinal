/*
 * API_uart.c
 *
 *  Created on: Oct 11, 2022
 *      Author: cfunes
 */
#include "API_uart.h"
#include "usart.h"

/*
 * @brief	Inicializa el periferico UART
 * @retval 	None
 */
void API_uart_init(void)
{
	MX_USART3_UART_Init();
}

/*
 * @brief	Envia una cadena de caracteres de largo len por UART.
 * @retval	UART_OK si la transmision fue exitosa, UART_ERROR en caso contrario.
 */
API_uart_status_t API_uart_send(char* data, uint16_t len)
{
	return (HAL_UART_Transmit(&huart3, (uint8_t*)data, len, len) == HAL_OK) ? UART_OK : UART_ERROR;
}


