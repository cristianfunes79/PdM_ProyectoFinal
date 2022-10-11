/*
 * API_delayUs.h
 *
 *  Created on: Oct 11, 2022
 *      Author: cfunes
 */

#ifndef API_INC_API_DELAYUS_H_
#define API_INC_API_DELAYUS_H_

/*
 * @brief	Inicializa el timer por hardware que sera utilizado como
 * 			base de tiempo para el delay.
 * @retval	None
 */
void delay_us_init(void);

/*
 * @brief	Realiza una espera bloqueante en microsegundos.
 * @param 	delay es el retardo en microsegundos.
 * @retval	None
 */
void delay_us(uint16_t delay);

#endif /* API_INC_API_DELAYUS_H_ */
