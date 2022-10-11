/*
 * app_fsm_task.c
 *
 *  Created on: Oct 11, 2022
 *      Author: cfunes
 */
#include "app_fsm_task.h"
#include "API_debounce.h"
#include "maxim_ds18b20_port.h"
#include "API_uart.h"
#include <stdio.h>
#include <string.h>

typedef enum
{
    WAIT_BUTTON,
    READ_TEMP_SENSOR,
    SEND_DATA,
} app_fsm_state_t;

static app_fsm_state_t app_fsm_state_current;

void app_fsm_task_init(void)
{
    app_fsm_state_current = WAIT_BUTTON;
    debounceFSM_init();
}

void app_fsm_task_next_state(void)
{
	static float temper=123.4;
	char data_buffer[100];

	debounceFSM_update();

    switch(app_fsm_state_current)
    {
        case WAIT_BUTTON:
        	if (readKey())
        		{
        		app_fsm_state_current = READ_TEMP_SENSOR;
        		API_uart_send((char*)"Reading Sensor2 \n",17);
        		}
            break;
        case READ_TEMP_SENSOR:
        	API_uart_send((char*)"Reading Sensor\n",15);
        	if (ds18b20_port_get_temperature(&temper) == TEMP_OK) app_fsm_state_current = SEND_DATA;
            break;
        case SEND_DATA:
        	snprintf(data_buffer,100,">%3.2f<",temper);
        	API_uart_send(data_buffer,strlen(data_buffer));
        	app_fsm_state_current = WAIT_BUTTON;
            break;
        default:
            break;
    }
}

