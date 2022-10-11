/*
 * app_fsm_task.c
 *
 *  Created on: Oct 11, 2022
 *      Author: cfunes
 */

#include <stdio.h>
#include <string.h>

#include "app_fsm_task.h"
#include "API_debounce.h"
#include "maxim_ds18b20_port.h"
#include "API_uart.h"

/* Private macros -------------------------------*/
#define DATA_BUFFER_SIZE	20
#define APP_INFORMATION_BUFFER_SIZE	256

/* Private definitions --------------------------*/
typedef enum
{
    WAIT_BUTTON,
    READ_TEMP_SENSOR,
    SEND_DATA,
	SEND_ERROR
} app_fsm_state_t;

typedef struct
{
	const char* default_state;
	const char app_version_major;
	const char app_version_minor;
} app_fsm_information_t;

static app_fsm_state_t app_fsm_state_current;
static app_fsm_information_t app_fsm_information = {.default_state = "WAIT_BUTTON", .app_version_major='1', .app_version_minor='0'};

/* Private functions -----------------------------*/

/*
 * @brief	Muestra informacion de la tarea a traves de la UART.
 * @retval 	None
 */
static void app_fsm_print_task_information(void)
{
	char app_information_buffer[APP_INFORMATION_BUFFER_SIZE];

	snprintf(app_information_buffer, APP_INFORMATION_BUFFER_SIZE,
			"+---------- APP FSM TASK ----------+\n"
			"  Task version: %c.%c \n"
			"  Default state: %s   \n"
			"+-----------------------------------------+\n\n", app_fsm_information.app_version_major, app_fsm_information.app_version_minor,  app_fsm_information.default_state);
	API_uart_send(app_information_buffer, strlen(app_information_buffer));
}

/* Public functions ------------------------------*/

/*
 * @brief	Inicializa la FSM de la aplicacion
 * @retval	None
 */
void app_fsm_task_init(void)
{
    app_fsm_state_current = WAIT_BUTTON;

    API_uart_init();
    MX_GPIO_Init();
    ds18b20_port_init(DS18B20_Port_GPIO_Port, DS18B20_Port_Pin);
    debounceFSM_init();

    app_fsm_print_task_information();
}

/*
 * @brief	Avanza al siguiente estado de la FSM
 * @retval	None
 */
void app_fsm_task_next_state(void)
{
	static float current_temperature=123.45;
	static char data_buffer[DATA_BUFFER_SIZE];

	debounceFSM_update();

	// La maquina de estados consiste de 4 estados posibles:
	// - [WAIT_BUTTON]: 	es el estado inicial, la MEF espera a que se presione
	//						el boton de usuario.
	// - [READ_TEMP_SENSOR]:	una vez pulsado el boton de usuario se realiza una
	//							lectura de temperatura del sensor ds18b20. Dicha lectura
	//							puede ser valida o arrojar un error. Dependiendo de ello,
	// 							se procedera a enviar la lectura o un mensaje de error.
	// - [SEND_DATA]:	en caso de realizar una lectura de temperatura exitosa, se envia la
	//					trama con la lectura por UART siguiendo el formato: >TTT.TT<
	// - [SEND_ERROR]:	en caso de realizar una lectura erronea, se procede a enviar por
	//					UART una trama del tipo: >SENSOR ERROR<
    switch(app_fsm_state_current)
    {
        case WAIT_BUTTON:
        	if (readKey()) app_fsm_state_current = READ_TEMP_SENSOR;
            break;
        case READ_TEMP_SENSOR:
        	if (ds18b20_port_get_temperature(&current_temperature) == TEMP_OK) app_fsm_state_current = SEND_DATA;
        	else app_fsm_state_current = SEND_ERROR;
            break;
        case SEND_DATA:
        	snprintf(data_buffer,DATA_BUFFER_SIZE,">%03.2f<\r\n",current_temperature);
        	API_uart_send(data_buffer,strlen(data_buffer));
        	app_fsm_state_current = WAIT_BUTTON;
            break;
        case SEND_ERROR:
			snprintf(data_buffer,DATA_BUFFER_SIZE,">SENSOR ERROR<\r\n");
			API_uart_send(data_buffer,strlen(data_buffer));
			app_fsm_state_current = WAIT_BUTTON;
			break;
        default:
            break;
    }
}

