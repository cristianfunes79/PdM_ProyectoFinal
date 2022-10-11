/*
 * API_delayUs.c
 *
 *  Created on: Oct 11, 2022
 *      Author: cfunes
 */
#include "tim.h"

/* Public functions -----------------------*/

/*
 * @brief	Inicializa el timer por hardware que sera utilizado como
 * 			base de tiempo para el delay.
 * @retval	None
 */
void delay_us_init(void)
{
	if (htim7.Instance == NULL)
	{
		MX_TIM7_Init();
	}
}

/*
 * @brief	Realiza una espera bloqueante en microsegundos.
 * @param 	delay es el retardo en microsegundos.
 * @retval	None
 */
void delay_us(uint32_t delay)
{
	  __HAL_TIM_SET_COUNTER(&htim7, 0);
	  while (__HAL_TIM_GET_COUNTER(&htim7) < delay);
}
