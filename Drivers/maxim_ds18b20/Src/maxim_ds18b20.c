/*
 * maxim_ds18b20.c
 *
 *  Created on: Sep 29, 2022
 *      Author: cfunes
 */

#include "maxim_ds18b20.h"

#define static

static bool one_wire_reset(oneWire_t* port)
{
	bool ack = false;

	//port->set_output(port->port);
	port->one_wire_pulldown(port->port);
	port->delay_us(480);
	port->one_wire_release(port->port);
	port->delay_us(210);

	ack = port->one_wire_read(port->port);

	if (ack)
	{
		port->delay_us(500);
	}

	return ack;
}

static void write_lsb(oneWire_t* port, uint8_t data)
{
	if ( data & 0x1)
	{
		//port->set_output(port->port);
		port->one_wire_pulldown(port->port);
		port->delay_us(6);
		port->one_wire_release(port->port);
		port->delay_us(64);
	}
    else
	{
    	//port->set_output(port->port);
		port->one_wire_pulldown(port->port);
		port->delay_us(60);
		port->one_wire_release(port->port);
		port->delay_us(10);
	}
}

static uint8_t read_lsb(oneWire_t* port)
{
    uint8_t lsb = 0;

    //port->set_output(port->port);
    port->one_wire_pulldown(port->port);
    port->delay_us(6);
    port->one_wire_release(port->port);
    port->delay_us(9);
    
    lsb = port->one_wire_read(port->port);

    port->delay_us(55);

    return lsb;
}

static void write_byte(oneWire_t* port, uint8_t data)
{
    for (uint8_t i=0; i<8; ++i)
    {
        write_lsb(port, data>>i);
    }
}

static uint8_t read_byte(oneWire_t* port)
{
    uint8_t rbyte = 0x00;

    for (uint8_t i=0; i<8; ++i)
    {
        rbyte >>= 1;
        if (read_lsb(port)) rbyte |= 0x80;
    }

    return rbyte;
}



oneWire_status_t get_temperature(oneWire_t* port)
{
    oneWire_status_t status = NACK;
    uint8_t scratchpad_mem[9];

    if (one_wire_reset(port))
    {
        write_byte(port, 0xCC);
        write_byte(port, 0x44);
        while(!port->one_wire_read(port));
        if (one_wire_reset(port))
        {
            write_byte(port, 0xCC);
            write_byte(port, 0xBE);
            for(uint8_t i=0; i<9; ++i) scratchpad_mem[i] = read_byte(port);
            uint16_t LSB = scratchpad_mem[0];
            uint16_t MSB = scratchpad_mem[1];
            one_wire_reset(port);

            port->temperature = (MSB<<8) | LSB;
            //TODO: check crc
            port->temperature /= 16.0;
            status = OK;
        }
    }

    return status;
}

