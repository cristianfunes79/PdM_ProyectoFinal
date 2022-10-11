/*
 * app_fsm_task.h
 *
 *  Created on: Oct 11, 2022
 *      Author: cfunes
 */

#ifndef APP_INC_APP_FSM_TASK_H_
#define APP_INC_APP_FSM_TASK_H_

/*
 * @brief	Inicializa la FSM de la aplicacion
 * @retval	None
 */
void app_fsm_task_init(void);

/*
 * @brief	Avanza al siguiente estado de la FSM
 * @retval	None
 */
void app_fsm_task_next_state(void);

#endif /* APP_INC_APP_FSM_TASK_H_ */
