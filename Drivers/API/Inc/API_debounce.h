/*
 * API_debounce.h
 *
 *  Created on: Sep 13, 2022
 *      Author: Cristian Funes
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include "API_delay.h"

/*
 * @brief Inicializa la maquina de estados
 * @params None
 * @retval None
 */
void debounceFSM_init(void);

/*
 * @brief Actualiza la maquina de estados al estado siguiente
 * @params None
 * @retval None
 */
void debounceFSM_update(void);

/*
 * @brief 	Lee una variable interna del modulo API_debounce y
 * 			retorna el valor de la misma
 * @params 	None
 * @retval	true or false, dependiendo el valor de la variable leida
 */
bool_t readKey(void);

#endif /* API_INC_API_DEBOUNCE_H_ */
