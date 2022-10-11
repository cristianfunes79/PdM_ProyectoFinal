/*
 * maxim_ds18b20_port.c
 *
 *  Created on: Oct 11, 2022
 *      Author: cfunes
 */
#include "maxim_ds18b20_port.h"
#include "API_delayUs.h"

typedef struct
{
	GPIO_TypeDef* settings;
	uint16_t pin;
}GenericGPIO_t;

static GenericGPIO_t oneWirePort;
static oneWire_t oneWire;



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

static bool read_gpio(void* gpio)
{
	return (HAL_GPIO_ReadPin(((GenericGPIO_t*)gpio)->settings,((GenericGPIO_t*)gpio)->pin) == GPIO_PIN_SET) ? true : false;
}


void ds18b20_port_init(GPIO_TypeDef * gpio_settings, uint16_t gpio_pin)
{
	oneWirePort.settings = gpio_settings;
	oneWirePort.pin = gpio_pin;

	oneWire.one_wire_pulldown = set_gpio_low;
	oneWire.one_wire_read = read_gpio;
	oneWire.one_wire_release = set_gpio_input;
	oneWire.delay_us = delay_us;
	oneWire.port = &oneWirePort;
}

bool ds18b20_port_is_present(void)
{
	return sensor_is_present(&oneWire);
}

temperature_status_t ds18b20_port_get_temperature(float* temperature)
{
	temperature_status_t status = TEMP_ERROR;

	if (get_temperature(&oneWire) == OK)
	{
		*temperature = oneWire.temperature;
		status = TEMP_OK;
	}

	return status;
}
