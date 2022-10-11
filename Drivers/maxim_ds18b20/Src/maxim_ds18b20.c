/*
 * maxim_ds18b20.c
 *
 *  Created on: Sep 29, 2022
 *      Author: cfunes
 */

#include "maxim_ds18b20.h"

typedef enum
{
	SEARCH_ROM = 0,
	READ_ROM,
    MATCH_ROM,
    SKIP_ROM,
    ALARM_SEARCH,
    CONVERT_T,
    WRITE_SCRATCHPAD,
    READ_SCRATCHPAD,
    COPY_SCRATCHPAD,
    RECALL_EE,
    READ_POWER_SUPPLY,
    COMMAND_LAST
} oneWire_command_t;

static uint8_t commands[COMMAND_LAST] = { 	0xF0, /* SEARCH_ROM 		*/
								            0x33, /* READ_ROM 			*/
								            0x55, /* MATCH_ROM 			*/
								            0xCC, /* SKIP_ROM 			*/
								            0xEC, /* ALARM_SEARCH		*/
								            0x44, /* CONVERT_T			*/
								            0x4E, /* WRITE_SCRATCHPAD	*/
								            0xBE, /* READ_SCRATCHPAD	*/
								            0x48, /* COPY_SCRATCHPAD	*/
								            0xB8, /* RECALL_EE			*/
								            0xB4, /* READ_POWER_SUPPLY	*/
							            };

static bool one_wire_reset(oneWire_t* port)
{
	bool ack = false;

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
		port->one_wire_pulldown(port->port);
		port->delay_us(6);
		port->one_wire_release(port->port);
		port->delay_us(64);
	}
    else
	{
		port->one_wire_pulldown(port->port);
		port->delay_us(60);
		port->one_wire_release(port->port);
		port->delay_us(10);
	}
}

static uint8_t read_lsb(oneWire_t* port)
{
    uint8_t lsb = 0;

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

static void send_command(oneWire_t* port, oneWire_command_t command)
{
    write_byte(port, commands[command]);
}



bool sensor_is_present(oneWire_t* port)
{
    return one_wire_reset(port);
}

oneWire_status_t get_temperature(oneWire_t* port)
{
    oneWire_status_t status = NACK;
    uint8_t scratchpad_mem[9];

    if (one_wire_reset(port))
    {
        send_command(port, SKIP_ROM);
        send_command(port, CONVERT_T);
        while(!port->one_wire_read(port));
        if (one_wire_reset(port))
        {
            send_command(port, SKIP_ROM);
            send_command(port, READ_SCRATCHPAD);
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

