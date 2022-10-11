/*
 * AIP_uart.h
 *
 *  Created on: Oct 11, 2022
 *      Author: cfunes
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include <stdint.h>

/*
 * @brief	Retorna el estado de la transmision
 */
typedef enum
{
	UART_OK = 0,
	UART_ERROR
}API_uart_status_t;

/*
 * @brief	Inicializa el periferico UART
 * @retval 	None
 */
void API_uart_init(void);

/*
 * @brief	Envia una cadena de caracteres de largo len por UART.
 * @retval	UART_OK si la transmision fue exitosa, UART_ERROR en caso contrario.
 */
API_uart_status_t API_uart_send(char* data, uint16_t len);

#endif /* API_INC_API_UART_H_ */
