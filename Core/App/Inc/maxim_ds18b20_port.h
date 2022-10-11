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

/*
 * @brief	Inicializa el puerto oneWire.
 * @param	gpio_settings y gpio_pin indican el puerto que se desea configurar.
 * @retval	None
 */
void ds18b20_port_init(GPIO_TypeDef * gpio_settings, uint16_t gpio_pin);

/*
 * @brief	Indica si se encuentra conectado un sensor ds18b20 en el puerto inicializado
 * @retval	true si hay un sensor conectado y false en caso contrario.
 *
 */
bool ds18b20_port_is_present(void);

/*
 * @brief	Inicializa la conversion de temperatura y devuelve el valor de la misma/
 * @retval	OK en caso de que la operacion sea exitosa y TEMP_ERROR de lo contrario
 */
temperature_status_t ds18b20_port_get_temperature(float* temperature);


#endif /* MAXIM_DS18B20_INC_MAXIM_DS18B20_PORT_H_ */
