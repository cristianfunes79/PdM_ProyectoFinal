/*
 * maxim_ds18b20.h
 *
 *  Created on: Sep 29, 2022
 *      Author: cfunes
 */

#ifndef MAXIM_DS18B20_INC_MAXIM_DS18B20_H_
#define MAXIM_DS18B20_INC_MAXIM_DS18B20_H_

#include <stdint.h>
#include <stdbool.h>

/*
 * @brief	Estado de la operacion con el sensor.
 */
typedef enum
{
    DS_OK,
    DS_NACK,
    DS_CRC_ERROR
} oneWire_status_t; //result returned in read temp

/*
 * @brief	Esta estructura se usa como interfaz para poder portar el driver a distintas arquitecturas
 */
typedef struct
{
	void (*one_wire_pulldown) (void*);  // Setea el puerto como salida en estado bajo
	bool (*one_wire_read) (void*);      // Lee el estado del puerto
	void (*one_wire_release) (void*);   // Setea el puerto como entrada para liberar el bus
	void (*delay_us) (uint16_t);		// Retardo en microsegundos

	void * port; 						// Puntero a la estructura de datos correspondiente para manejar gpios

    float temperature;					// Guarda el valor leido de temperatura para el puerto especificado
} oneWire_t;

/*
 * @brief	Realiza la conversion y lectura de temperatura del sensor oneWire.
 * @param	port es el puerto donde se conecta el sensor oneWire.
 * @retval	DS_OK en caso de que se realice una operacion exitosa y ERROR en caso contrario.
 */
oneWire_status_t get_temperature(oneWire_t* port);

/*
 * @brief	Checkea si se encuentra conectado un sensor en el puerto oneWire.
 * @param	port es el puerto donde se conecta el sensor oneWire.
 * @retval	true si se encuentra un sensor y false de lo contrario.
 */
bool sensor_is_present(oneWire_t* port);

#endif /* MAXIM_DS18B20_INC_MAXIM_DS18B20_H_ */
