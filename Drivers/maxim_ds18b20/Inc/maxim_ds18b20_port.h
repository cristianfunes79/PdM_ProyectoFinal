/*
 * maxim_ds18b20_port.h
 *
 *  Created on: Oct 11, 2022
 *      Author: cfunes
 */

#ifndef MAXIM_DS18B20_INC_MAXIM_DS18B20_PORT_H_
#define MAXIM_DS18B20_INC_MAXIM_DS18B20_PORT_H_

#include "gpio.h"
#include "maxim_ds18b20.h"

typedef enum
{
	TEMP_OK=0,
	TEMP_ERROR
} temperature_status_t;

void ds18b20_port_init(GPIO_TypeDef * gpio_settings, uint16_t gpio_pin);
bool ds18b20_port_is_present(void);
temperature_status_t ds18b20_port_get_temperature(float* temperature);


#endif /* MAXIM_DS18B20_INC_MAXIM_DS18B20_PORT_H_ */
