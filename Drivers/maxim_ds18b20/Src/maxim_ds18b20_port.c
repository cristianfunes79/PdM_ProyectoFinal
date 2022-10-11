/*
 * maxim_ds18b20_port.c
 *
 *  Created on: Oct 11, 2022
 *      Author: cfunes
 */
#include "maxim_ds18b20_port.h"
#include "API_delayUs.h"

/* Private definitions ------------------------*/

/*
 * @brief	Esta estructura se define para poder configurar el puerto oneWire.
 * 			Como se requiere cambiar la configuracion del gpio durante la lectura del sensor
 * 			de temperatura, es necesario pasar tanto el pin como el seteo del gpio a las
 * 			funciones de manejo del puerto.
 */
typedef struct
{
	GPIO_TypeDef* settings;
	uint16_t pin;
}GenericGPIO_t;

static GenericGPIO_t oneWirePort;
static oneWire_t oneWire;


/* Private functions ----------------------------------------------*/
/*
 * @brief	Seteo del gpio como salida en estado bajo.
 * @param	gpio es un puntero a la estructura de manejo de gpios.
 * @retval	None
 */
static void set_gpio_low(void* gpio)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	HAL_GPIO_WritePin(((GenericGPIO_t*)gpio)->settings, ((GenericGPIO_t*)gpio)->pin, GPIO_PIN_RESET);
	/*Configure GPIO pin : DS18B20_PORT1_Pin */
	GPIO_InitStruct.Pin = ((GenericGPIO_t*)gpio)->pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(((GenericGPIO_t*)gpio)->settings, &GPIO_InitStruct);
}

/*
 * @brief	Seteo del gpio como entrada. Se usa para poder hacer un release del puerto oneWire
 * 			y tambien para luego poder leer los valores seteados por el sensor.
 * @param	gpio es un puntero a la estructura de manejo de gpios.
 * @retval 	None
 */
static void set_gpio_input(void* gpio)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/*Configure GPIO pin : DS18B20_PORT1_Pin */
	GPIO_InitStruct.Pin = ((GenericGPIO_t*)gpio)->pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(((GenericGPIO_t*)gpio)->settings, &GPIO_InitStruct);
}

/*
 * @brief	Devuelve el estado de la entrada seleccionada.
 * @param	gpio es un puntero a la estructura de manejo de gpios.
 * @retval	true si el gpio esta en alto y false si esta en estado bajo.
 */
static bool read_gpio(void* gpio)
{
	return (HAL_GPIO_ReadPin(((GenericGPIO_t*)gpio)->settings,((GenericGPIO_t*)gpio)->pin) == GPIO_PIN_SET) ? true : false;
}

/* Public functions ---------------------------------------------------*/

/*
 * @brief	Inicializa el puerto oneWire.
 * @param	gpio_settings y gpio_pin indican el puerto que se desea configurar.
 * @retval	None
 */
void ds18b20_port_init(GPIO_TypeDef * gpio_settings, uint16_t gpio_pin)
{
	oneWirePort.settings = gpio_settings;
	oneWirePort.pin = gpio_pin;

	oneWire.one_wire_pulldown = set_gpio_low;
	oneWire.one_wire_read = read_gpio;
	oneWire.one_wire_release = set_gpio_input;
	oneWire.delay_us = delay_us;
	oneWire.port = &oneWirePort;

	delay_us_init();
}

/*
 * @brief	Indica si se encuentra conectado un sensor ds18b20 en el puerto inicializado
 * @retval	true si hay un sensor conectado y false en caso contrario.
 *
 */
bool ds18b20_port_is_present(void)
{
	return sensor_is_present(&oneWire);
}

/*
 * @brief	Inicializa la conversion de temperatura y devuelve el valor de la misma/
 * @retval	OK en caso de que la operacion sea exitosa y TEMP_ERROR de lo contrario
 */
temperature_status_t ds18b20_port_get_temperature(float* temperature)
{
	temperature_status_t status = TEMP_ERROR;

	if (get_temperature(&oneWire) == DS_OK)
	{
		*temperature = oneWire.temperature;
		status = TEMP_OK;
	}

	return status;
}
