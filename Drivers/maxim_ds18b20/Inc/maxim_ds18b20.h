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

typedef enum
{
    OK,
    NACK,
    CRC_ERROR
} oneWire_status_t; //result returned in read temp

typedef struct
{
	void (*one_wire_pulldown) (void*);  // pulls to 0
	bool (*one_wire_read) (void*);      // reads
	void (*one_wire_release) (void*);   // releases bus, set as input
	void (*delay_us) (uint16_t);

	void * port; // pointer to gpio

    float temperature;
} oneWire_t;

oneWire_status_t get_temperature(oneWire_t* port);
bool sensor_is_present(oneWire_t* port);

#endif /* MAXIM_DS18B20_INC_MAXIM_DS18B20_H_ */
